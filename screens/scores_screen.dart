import 'dart:async';
import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../services/websocket_service.dart';
import '../models/group_model.dart';
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

  // === ÉTAT ===
  bool showFinGameOverlay = false;
  bool hasNavigatedToClassement = false;

  // === NOUVEL ÉTAT POUR LE BOUTON "ATTENTE GROUPE" ===
  bool _isAttenteGroupeButtonEnabled = false;
  Color _attenteGroupeButtonColor = const Color(0xFF7DBFF8); // Bleu par défaut
  String _attenteGroupeButtonText = 'Partie en attente';
  bool _isAttenteGroupeButtonBlinking = false; // Ajout du booléen pour le clignotement

  // === GESTION DES BOUTONS ===
  String _nextPlayerButtonText = 'Joueur suivant';
  String _nextTurnButtonText = 'Tour suivant';

  Color _nextPlayerButtonColor = Colors.blue;
  Color _nextTurnButtonColor = Colors.blue;

  bool _isNextPlayerButtonBlinking = false;
  bool _isNextTurnButtonBlinking = false;

  bool _isNextPlayerButtonEnabled = false;
  bool _isNextTurnButtonEnabled = false;

  late AnimationController _blinkController;
  StreamSubscription<String>? _messageSubscription;

  @override
  void initState() {
    super.initState();

    // Initialisation des contrôleurs d'animation
    _controller = AnimationController(duration: const Duration(milliseconds: 500), vsync: this);
    _fadeAnimation = Tween<double>(begin: 0, end: 1).animate(_controller);
    _scaleAnimation = Tween<double>(begin: 0.95, end: 1).animate(_controller);

    _overlayController = AnimationController(
      vsync: this,
      duration: const Duration(milliseconds: 500),
    );

    _blinkController = AnimationController(
      duration: const Duration(seconds: 1), // Clignotement toutes les secondes
      vsync: this,
    );
    //_blinkController.repeat(reverse: true); // Suppression de l'appel à repeat ici

    // Lancer l'animation au démarrage
    _controller.forward();

    // Configuration de l'écouteur WebSocket
    _setupWebSocketListener();
  }

  void _setupWebSocketListener() {
    final ws = Provider.of<WebSocketService>(context, listen: false);
    _messageSubscription = ws.messages.listen((message) {
      final data = json.decode(message) as Map<String, dynamic>;
      final type = data['type'] as String?;
      if (type != null) {
        _handleWebSocketMessage(type, message); // Pass the message here
      }
    });
  }

  void _handleWebSocketMessage(String type, String message) { // Receive the message here
    if (!mounted) return;

    setState(() {
      switch (type) {
        case 'game_status':
          final data = json.decode(message) as Map<String, dynamic>;
          final wsMessage = data['message'] as String?;
          if (wsMessage == 'START') {
            print('Message "START" reçu'); // Ajout du print
            _updateButtonStates(
              nextPlayerColor: Colors.green,
              nextTurnColor: Colors.green,
              nextPlayerEnabled: false,
              nextTurnEnabled: false,
              nextPlayerBlinking: false,
              nextTurnBlinking: false,
            );
            _updateAttenteGroupeButtonState(
              color: Colors.orange,
              enabled: true,
              text: 'Partie en attente',
              blinking: true, // Activer le clignotement
            );
          } else if (wsMessage == 'CONFIRMED_GAME') { // Ajout de la condition pour CONFIRMED_GAME
            _updateButtonStates(
              nextPlayerColor: Colors.green,
              nextTurnColor: Colors.green,
              nextPlayerEnabled: false,
              nextTurnEnabled: false,
              nextPlayerBlinking: false,
              nextTurnBlinking: false,
            );
            _updateAttenteGroupeButtonState(
              color: Colors.green,
              enabled: false,
              text: 'Partie lancée',
              blinking: false, // Désactiver le clignotement
            );
          }
          break;
        case 'START_GAME_CONFIRMED': // Suppression car non utilisé
          break;
        case 'NEXT_PLAYER':
          _updateButtonStates(
            nextPlayerColor: Colors.orange,
            nextTurnColor: Colors.green,
            nextPlayerEnabled: true,
            nextTurnEnabled: false,
            nextPlayerBlinking: true,
            nextTurnBlinking: false,
          );
          break;
        case 'NEXT_TURN':
          _updateButtonStates(
            nextPlayerColor: Colors.orange,
            nextTurnColor: Colors.green,
            nextPlayerEnabled: false,
            nextTurnEnabled: true,
            nextPlayerBlinking: false,
            nextTurnBlinking: true,
          );
          break;
        case 'FIN_GAME':
          _showFinGameOverlay();
          _updateButtonStates(
            nextPlayerColor: Colors.blue,
            nextTurnColor: Colors.blue,
            nextPlayerEnabled: false,
            nextTurnEnabled: false,
            nextPlayerBlinking: false,
            nextTurnBlinking: false,
          );
          _updateAttenteGroupeButtonState(
            color: const Color(0xFF7DBFF8),
            enabled: false,
            text: 'Attente groupe',
            blinking: false, // Désactiver le clignotement
          );
          break;
      }
    });
  }

  // === NOUVELLE FONCTION POUR METTRE À JOUR L'ÉTAT DU BOUTON "ATTENTE GROUPE" ===
  void _updateAttenteGroupeButtonState({
    required Color color,
    required bool enabled,
    required String text,
    required bool blinking, // Ajout du paramètre blinking
  }) {
    print('Appel de _updateAttenteGroupeButtonState avec enabled = $enabled'); // Ajout du print
    _attenteGroupeButtonColor = color;
    _isAttenteGroupeButtonEnabled = enabled;
    _attenteGroupeButtonText = text;
    _isAttenteGroupeButtonBlinking = blinking; // Mettre à jour l'état du clignotement

    if (_isAttenteGroupeButtonBlinking) {
      _blinkController.repeat(reverse: true); // Démarrer l'animation de clignotement
    } else {
      _blinkController.stop(); // Arrêter l'animation de clignotement
    }
  }

  // Fonction pour envoyer le message "START_GAME"
  void _onStartGamePressed() {
    print('Fonction _onStartGamePressed appelée'); // Ajout du print
    final ws = Provider.of<WebSocketService>(context, listen: false);
    ws.sendMessage(json.encode({'type': 'game_status', 'message': 'START_GAME'}));
  }

  void _updateButtonStates({
    required Color nextPlayerColor,
    required Color nextTurnColor,
    required bool nextPlayerEnabled,
    required bool nextTurnEnabled,
    required bool nextPlayerBlinking,
    required bool nextTurnBlinking,
  }) {
    _nextPlayerButtonColor = nextPlayerColor;
    _nextTurnButtonColor = nextTurnColor;

    _isNextPlayerButtonEnabled = nextPlayerEnabled;
    _isNextTurnButtonEnabled = nextTurnEnabled;

    _isNextPlayerButtonBlinking = nextPlayerBlinking;
    _isNextTurnButtonBlinking = nextTurnBlinking;

    if (_isNextPlayerButtonBlinking || _isNextTurnButtonBlinking) {
      _blinkController.repeat(reverse: true);
    } else {
      _blinkController.stop();
    }
  }

  void _onNextPlayerPressed() {
    final ws = Provider.of<WebSocketService>(context, listen: false);
    ws.sendMessage(json.encode({'type': 'next_player', 'message': 'NEXT_PLAYER'}));
    _updateButtonStates(
      nextPlayerColor: Colors.green,
      nextTurnColor: Colors.green,
      nextPlayerEnabled: false,
      nextTurnEnabled: false,
      nextPlayerBlinking: false,
      nextTurnBlinking: false,
    );
  }

  void _onNextTurnPressed() {
    final ws = Provider.of<WebSocketService>(context, listen: false);
    ws.sendMessage(json.encode({'type': 'next_turn', 'message': 'NEXT_TURN'}));
    _updateButtonStates(
      nextPlayerColor: Colors.green,
      nextTurnColor: Colors.green,
      nextPlayerEnabled: false,
      nextTurnEnabled: false,
      nextPlayerBlinking: false,
      nextTurnBlinking: false,
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

      setState(() => showFinGameOverlay = false);

      Navigator.of(context).pushReplacement(
        MaterialPageRoute(
          builder: (_) => ClassementScreen(finalScores: finalScores),
        ),
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    final ws = Provider.of<WebSocketService>(context);
    final groupModel = Provider.of<GroupModel>(context);

    print('La valeur de _isAttenteGroupeButtonEnabled est : $_isAttenteGroupeButtonEnabled'); // Ajout du print

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
            padding: const EdgeInsets.symmetric(horizontal: 8.0),
            child: ElevatedButton(
              onPressed: null,
              style: ElevatedButton.styleFrom(
                backgroundColor: const Color(0xFF7DBFF8),
                disabledBackgroundColor: const Color(0xFF7DBFF8),
                elevation: 0,
                shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(20),
                ),
              ),
              child: Text(
                'Groupe ${groupModel.selectedGroup}',
                style: const TextStyle(
                  fontWeight: FontWeight.bold,
                  color: Colors.black,
                ),
              ),
            ),
          ),
          // Bouton "Partie en attente"
          Padding(
            padding: const EdgeInsets.symmetric(horizontal: 8.0),
            child: FadeTransition( // Ajouter FadeTransition pour le clignotement
              opacity: _isAttenteGroupeButtonBlinking ? Tween<double>(begin: 1.0, end: 0.0).animate(_blinkController) : const AlwaysStoppedAnimation(1.0), // Contrôler l'opacité avec l'animation de clignotement
              child: ElevatedButton(
                onPressed: _isAttenteGroupeButtonEnabled ? _onStartGamePressed : null,
                style: ElevatedButton.styleFrom(
                  backgroundColor: _attenteGroupeButtonColor,
                  disabledBackgroundColor: const Color(0xFF7DBFF8),
                  elevation: 0,
                  shape: RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(20),
                  ),
                ),
                child: Text(
                  _attenteGroupeButtonText,
                  style: const TextStyle(
                    fontWeight: FontWeight.bold,
                    color: Colors.black,
                  ),
                ),
              ),
            ),
          ),
          // Bouton "Joueur suivant"
          Padding(
            padding: const EdgeInsets.symmetric(horizontal: 8.0),
            child: ElevatedButton(
              onPressed: _isNextPlayerButtonEnabled ? _onNextPlayerPressed : null,
              style: ElevatedButton.styleFrom(
                backgroundColor: _nextPlayerButtonColor,
                disabledBackgroundColor: Colors.blue,
                elevation: 0,
                shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(20),
                ),
              ),
              child: Text(
                _nextPlayerButtonText,
                style: const TextStyle(
                  fontWeight: FontWeight.bold,
                  color: Colors.black,
                ),
              ),
            ),
          ),
          // Bouton "Tour suivant"
          Padding(
            padding: const EdgeInsets.symmetric(horizontal: 8.0),
            child: ElevatedButton(
              onPressed: _isNextTurnButtonEnabled ? _onNextTurnPressed : null,
              style: ElevatedButton.styleFrom(
                backgroundColor: _nextTurnButtonColor,
                disabledBackgroundColor: Colors.blue,
                elevation: 0,
                shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(20),
                ),
              ),
              child: Text(
                _nextTurnButtonText,
                style: const TextStyle(
                  fontWeight: FontWeight.bold,
                  color: Colors.black,
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
                  ],
                ),
              ),
            );
          },
        ),
      ),
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
    _controller.dispose();
    _overlayController.dispose();
    _blinkController.dispose();
    _messageSubscription?.cancel();
    super.dispose();
  }
}
