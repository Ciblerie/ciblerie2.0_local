import 'dart:async';
import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:flutter/scheduler.dart';
import 'package:provider/provider.dart';
import 'package:shared_preferences/shared_preferences.dart';
import '../services/websocket_service.dart';
import '../models/group_model.dart';
import '../enums/game_phase.dart';
import 'classement_screen.dart';

class ScoresScreen extends StatefulWidget {
  const ScoresScreen({super.key});

  @override
  State<ScoresScreen> createState() => _ScoresScreenState();
}

class _ScoresScreenState extends State<ScoresScreen> with TickerProviderStateMixin {
  // === ANIMATIONS ===
  late AnimationController _controller;
  late AnimationController _overlayController;
  late Animation<double> _fadeAnimation;
  late Animation<double> _scaleAnimation;
  late AnimationController _blinkController;
  late Animation<double> _blinkAnimation;

  // === ÉTAT ===
  bool showFinGameOverlay = false;
  bool hasNavigatedToClassement = false;

  // === ÉTAT DU JEU ===
  GamePhase _gamePhase = GamePhase.waitingGroup;
  bool _showFinGameOverlay = false;
  bool _hasNavigatedToClassement = false;
  int _currentPlayerIndex = 0;
  int? _currentRound;
  StreamSubscription<String>? _messageSubscription;

  // === GESTION DU BOUTON ===
  String _buttonText = 'Attente groupe';
  Color _buttonColor = Colors.blue;
  bool _isButtonBlinking = false;
  bool _isButtonEnabled = false;

  StreamSubscription<String>? _messageSubscription;

  @override
  void initState() {
    super.initState();

    // Initialisation des contrôleurs d'animation
    _controller = AnimationController(
      duration: const Duration(milliseconds: 500),
      vsync: this,
    );

    _overlayController = AnimationController(
      duration: const Duration(milliseconds: 500),
      vsync: this,
    );

    _blinkController = AnimationController(
      duration: const Duration(milliseconds: 500),
      vsync: this,
    );

    // Initialisation des animations
    _fadeAnimation = Tween<double>(begin: 0, end: 1).animate(_controller);
    _scaleAnimation = Tween<double>(begin: 0.95, end: 1).animate(_controller);
    _blinkAnimation = Tween<double>(begin: 0.5, end: 1.0).animate(
      CurvedAnimation(
        parent: _blinkController,
        curve: Curves.easeInOut,
      ),
    );

    // Démarrage des animations
    _controller.forward();

    // Configuration de l'écouteur WebSocket
    _setupWebSocketListener();
    _checkInitialState();
  }

  Future<void> _checkInitialState() async {
    debugPrint('🔍 Vérification de l\'état initial');
    final prefs = await SharedPreferences.getInstance();
    final ws = Provider.of<WebSocketService>(context, listen: false);

    if (ws.isConnected && prefs.getString('selectedGroup') != null) {
      debugPrint('✅ Groupe déjà sélectionné, passage en mode readyToStart');
      if (mounted) {
        setState(() {
          _gamePhase = GamePhase.readyToStart;
        });
      }
    }
  }

  void _setupWebSocketListener() {
    final ws = Provider.of<WebSocketService>(context, listen: false);
    _messageSubscription = ws.messages.listen((message) {
      final data = json.decode(message) as Map<String, dynamic>;
      final type = data['type'] as String?;
      _handleWebSocketMessage(message);

      setState(() {
        if (type == 'start_game') {
          _gamePhase = GamePhase.starting;
          _blinkController.repeat(reverse: true);
        } else if (type == 'confirmed_game') {
          _gamePhase = GamePhase.inProgress;
          _blinkController.stop();
        } else if (type == 'fin_game') {
          _gamePhase = GamePhase.waitingGroup;
        }
      });
    });
  }

  void _handleWebSocketMessage(String message) {
    final data = json.decode(message) as Map<String, dynamic>;
    final type = data['type'] as String?;
    final status = data['status'] as String?;

    setState(() {
      switch (type) {
        case 'waiting_group':
          _gamePhase = GamePhase.waitingGroup;
          _blinkController.stop();
          break;
        case 'start_game':
          _gamePhase = GamePhase.starting;
          _blinkController.repeat(reverse: true);
          break;
        case 'confirmed_game':
          _gamePhase = GamePhase.inProgress;
          _blinkController.stop();
          break;
        case 'fin_game':
          _gamePhase = GamePhase.waitingGroup;
          break;
        case 'game_status':
          _handleGameStatus(status);
          break;
      }
    });
  }

  void _handleGameStatus(String? status) {
    if (!mounted) return;

    debugPrint('🔄 Traitement du statut: $status');

    setState(() {
      switch (status) {
        case 'starting':
          _gamePhase = GamePhase.inProgress;
          _blinkController.stop();
          break;
        case 'confirmed':
          if (_gamePhase == GamePhase.starting) {
            _gamePhase = GamePhase.inProgress;
          }
          break;
        case 'finished':
          _handleGameFinished();
          break;
        case 'waiting_group':
          _gamePhase = GamePhase.waitingGroup;
          break;
      }
    });
  }

  void _handleGameFinished() async {
    if (!mounted) return;
    debugPrint('🏁 Début du traitement de fin de jeu');

    setState(() {
      _gamePhase = GamePhase.finished;
      _showFinGameOverlay = true;
    });
    _overlayController.forward();

    await Future.delayed(const Duration(seconds: 5));
    if (!mounted) return;

    _overlayController.reverse();
    await Future.delayed(const Duration(milliseconds: 500));

    if (mounted && !_hasNavigatedToClassement) {
      debugPrint('➡️ Navigation vers l\'écran de classement');
      _hasNavigatedToClassement = true;
      final scores = Provider.of<WebSocketService>(context, listen: false).scoresNotifier.value;
      final finalScores = List.generate(4, (i) => scores[i] ?? 0);

      Navigator.of(context).pushReplacement(
        MaterialPageRoute(
          builder: (_) => ClassementScreen(finalScores: finalScores),
        ),
      );
    }
  }


  void _handleWebSocketMessage(String type) {
    if (!mounted) return;

    setState(() {
      switch (type) {
        case 'group_game': // CF1
          _updateButtonState('Attente groupe', Colors.blue, false, false);
          break;
        case 'start_game': // START_GAME
          _updateButtonState('Partie en attente', Colors.orange, true, true);
          break;
        case 'confirmed_game': // CONFIRMED_GAME
          _updateButtonState('Partie en cours', Colors.green, false, false);
          break;
        case 'fin_game': // FIN_GAME
          _updateButtonState('Attente groupe', Colors.blue, false, false);
          break;
      }
    });
  }

  void _updateButtonState(
      String text, Color color, bool isBlinking, bool isEnabled) {
    _buttonText = text;
    _buttonColor = color;
    _isButtonBlinking = isBlinking;
    _isButtonEnabled = isEnabled;

    if (_isButtonBlinking) {
      _blinkController.repeat(reverse: true);
    } else {
      _blinkController.stop();
    }
  }

  void _onButtonPressed() {
    final ws = Provider.of<WebSocketService>(context, listen: false);

    if (_buttonText == 'Partie en attente') {
      ws.sendMessage(json.encode({'type': 'start_game', 'message': 'START_GAME'}));
    }
  }

  void _nextPlayer() {
    debugPrint('🔄 Passage au joueur suivant');
    final ws = Provider.of<WebSocketService>(context, listen: false);
    ws.sendMessage(json.encode({
      'type': 'next_player',
      'message': 'NEXT_PLAYER',
    }));

    if (mounted) {
      setState(() {
        _currentPlayerIndex = (_currentPlayerIndex + 1) % 4;
      });
    }
  }

  void _nextTurn() async {
    debugPrint('🔄 Passage au tour suivant');
    final ws = Provider.of<WebSocketService>(context, listen: false);
    ws.sendMessage(json.encode({
      'type': 'next_turn',
      'message': 'NEXT_TURN',
    }));

    final prefs = await SharedPreferences.getInstance();
    if (mounted) {
      setState(() {
        if (_currentRound == null) {
          _currentRound = 1;
        } else if (_currentRound == 3) {
          _currentRound = null;
        } else {
          _currentRound = _currentRound! + 1;
        }
        _currentPlayerIndex = 0;
      });
      await prefs.setInt('currentRound', _currentRound ?? 0);
    }
  }

  @override
  Widget build(BuildContext context) {
    final ws = Provider.of<WebSocketService>(context);

    return Scaffold(
      appBar: AppBar(
        backgroundColor: Colors.black,
        title: const Row(
          children: [
            Icon(Icons.bar_chart, color: Colors.white),
            SizedBox(width: 8),
            Text('Scores', style: TextStyle(color: Colors.white)),
          ],
        ),
        actions: [
          Padding(
            padding: const EdgeInsets.symmetric(horizontal: 12.0),
            child: Consumer<WebSocketService>(
              builder: (context, ws, _) => ElevatedButton(
                onPressed: null,
                style: ElevatedButton.styleFrom(
                  backgroundColor: const Color(0xFF7DBFF8),
                  elevation: 0,
                  disabledBackgroundColor: const Color(0xFF7DBFF8),
                  shape: RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(20),
                  ),
                ),
                child: Text(
                  'Groupe ${ws.group}',
                  style: const TextStyle(
                    fontWeight: FontWeight.bold,
                    color: Colors.black,
                  ),
                ),
              ),
            ),
          ),
        ],
      ),
      body: SafeArea(
        child: LayoutBuilder(
          builder: (context, constraints) {
            final double spacing = constraints.maxWidth * 0.02;
            final double usableHeight = constraints.maxHeight - spacing * 3;
            final double cardHeight = (usableHeight / 2) - spacing;
            final double cardWidth = (constraints.maxWidth - spacing * 3) / 2;
            final double fontSize = cardHeight * 0.4;

            return FadeTransition(
              opacity: _fadeAnimation,
              child: ScaleTransition(
                scale: _scaleAnimation,
                child: Stack(
                  alignment: Alignment.center,
                  children: [
                    ValueListenableBuilder<Map<int, String>>(
                      valueListenable: ws.pseudonymsNotifier,
                      builder: (context, pseudos, _) {
                        return ValueListenableBuilder<Map<int, int>>(
                          valueListenable: ws.scoresNotifier,
                          builder: (context, scores, _) {
                            return Column(
                              mainAxisAlignment: MainAxisAlignment.center,
                              children: [
                                Row(
                                  mainAxisAlignment: MainAxisAlignment.center,
                                  children: [
                                    _buildScoreCard(
                                      '${pseudos[0] ?? "J1"} : ${scores[0] ?? 0}',
                                      cardWidth,
                                      cardHeight,
                                      fontSize,
                                      const LinearGradient(
                                        colors: [Color(0xFFAEDCFA), Color(0xFF91C9F9)],
                                      ),
                                    ),
                                    SizedBox(width: spacing),
                                    _buildScoreCard(
                                      '${pseudos[1] ?? "J2"} : ${scores[1] ?? 0}',
                                      cardWidth,
                                      cardHeight,
                                      fontSize,
                                      const LinearGradient(
                                        colors: [Color(0xFF91C9F9), Color(0xFF6AB8F7)],
                                      ),
                                    ),
                                  ],
                                ),
                                SizedBox(height: spacing),
                                Row(
                                  mainAxisAlignment: MainAxisAlignment.center,
                                  children: [
                                    _buildScoreCard(
                                      '${pseudos[2] ?? "J3"} : ${scores[2] ?? 0}',
                                      cardWidth,
                                      cardHeight,
                                      fontSize,
                                      const LinearGradient(
                                        colors: [Color(0xFF6AB8F7), Color(0xFF429CF2)],
                                      ),
                                    ),
                                    SizedBox(width: spacing),
                                    _buildScoreCard(
                                      '${pseudos[3] ?? "J4"} : ${scores[3] ?? 0}',
                                      cardWidth,
                                      cardHeight,
                                      fontSize,
                                      const LinearGradient(
                                        colors: [Color(0xFF429CF2), Color(0xFF1E88E5)],
                                      ),
                                    ),
                                  ],
                                ),
                              ],
                            );
                          },
                        );
                      },
                    ),
                    if (showFinGameOverlay)
                      FadeTransition(
                        opacity: _overlayController,
                        child: ScaleTransition(
                          scale: Tween<double>(begin: 0.9, end: 1.0).animate(
                            CurvedAnimation(parent: _overlayController, curve: Curves.easeOut),
                          ),
                          child: Container(
                            width: constraints.maxWidth * 0.75,
                            height: constraints.maxHeight * 0.75,
                            decoration: BoxDecoration(
                              gradient: const LinearGradient(
                                colors: [Color(0xFFFFE0B2), Color(0xFFFFB74D)],
                              ),
                              borderRadius: BorderRadius.circular(20),
                            ),
                            alignment: Alignment.center,
                            child: FittedBox(
                              fit: BoxFit.scaleDown,
                              child: Text(
                                'FIN GAME',
                                style: TextStyle(
                                  fontSize: constraints.maxHeight * 0.15,
                                  fontWeight: FontWeight.bold,
                                  color: Colors.black,
                                ),
                              ),
                            ),
                          ),
                        ),
                      ),
                  ],
                ),
              ),
            );
          },
        ),
      ),
    );
  }

  Widget _buildTourSuivantButton() {
    return ElevatedButton(
      onPressed: _nextTurn,
      style: ElevatedButton.styleFrom(
        backgroundColor:
            Colors.green ,
            const Color(0xFF7DBFF8),
        disabledBackgroundColor: Colors.green,
        elevation: 0,
        shape: RoundedRectangleBorder(
            borderRadius: BorderRadius.circular(20)),
      ),
      child: const Text(
        'Tour suivant',
        style: TextStyle(
            fontWeight: FontWeight.bold,
            color: Colors.black),
      ),
    );
  }

  void _showFinGameOverlay() async {
    if (!mounted) return;

    setState(() => showFinGameOverlay = true);
    _overlayController.forward();

    await Future.delayed(const Duration(seconds: 5));
    if (!mounted) return;
    _overlayController.reverse();
    await Future.delayed(const Duration(milliseconds: 500));

    if (mounted && !hasNavigatedToClassement) {
      hasNavigatedToClassement = true;

      final scoresMap = Provider.of<WebSocketService>(context, listen: false).scoresNotifier.value;
      final finalScores = List.generate(4, (i) => scoresMap[i] ?? 0);

      setState(() {
        showFinGameOverlay = false;
      });

      Navigator.of(context).pushReplacement(
        MaterialPageRoute(
          builder: (_) => ClassementScreen(finalScores: finalScores),
        ),
      );
    }
  }

  Widget _buildScoresGrid(Map<int, String> pseudos, Map<int, int> scores) {
    final spacing = MediaQuery.of(context).size.width * 0.02;
    final usableHeight = MediaQuery.of(context).size.height - spacing * 3;
    final cardHeight = (usableHeight / 2) - spacing;
    final cardWidth = (MediaQuery.of(context).size.width - spacing * 3) / 2;
    final fontSize = cardHeight * 0.4;

    return Column(
      mainAxisAlignment: MainAxisAlignment.center,
      children: [
        Row(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            _buildScoreCard(
                '${pseudos[0] ?? "J1"} : ${scores[0] ?? 0}',
                cardWidth,
                cardHeight,
                fontSize,
                const LinearGradient(colors: [
                  Color(0xFFAEDCFA),
                  Color(0xFF91C9F9)])),
            SizedBox(width: spacing),
            _buildScoreCard(
                '${pseudos[1] ?? "J2"} : ${scores[1] ?? 0}',
                cardWidth,
                cardHeight,
                fontSize,
                const LinearGradient(colors: [
                  Color(0xFF91C9F9),
                  Color(0xFF6AB8F7)])),
          ],
        ),
        SizedBox(height: spacing),
        Row(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            _buildScoreCard(
                '${pseudos[2] ?? "J3"} : ${scores[2] ?? 0}',
                cardWidth,
                cardHeight,
                fontSize,
                const LinearGradient(colors: [
                  Color(0xFF6AB8F7),
                  Color(0xFF429CF2)])),
            SizedBox(width: spacing),
            _buildScoreCard(
                '${pseudos[3] ?? "J4"} : ${scores[3] ?? 0}',
                cardWidth,
                cardHeight,
                fontSize,
                const LinearGradient(colors: [
                  Color(0xFF429CF2),
                  Color(0xFF1E88E5)])),
          ],
        ),
      ],
    );
  }

  Widget _buildScoreCard(String text, double width, double height, double fontSize, LinearGradient gradient) {
    return Container(
      width: width,
      height: height,
      decoration: BoxDecoration(
        gradient: gradient,
        borderRadius: BorderRadius.circular(16),
      ),
      alignment: Alignment.center,
      child: Text(
        text,
        style: TextStyle(
          fontSize: fontSize,
          fontWeight: FontWeight.bold,
          color: Colors.white,
        ),
        textAlign: TextAlign.center,
      ),
    );
  }

  @override
  void dispose() {
    debugPrint('♻️ Disposing ScoresScreen');
    _controller.dispose();
    _overlayController.dispose();
    _blinkController.dispose();
    _messageSubscription?.cancel();
    super.dispose();
  }
}
