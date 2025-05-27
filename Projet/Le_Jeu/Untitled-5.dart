import 'dart:async';
import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:flutter/scheduler.dart';
import 'package:provider/provider.dart';
import '../services/websocket_service.dart';
import 'classement_screen.dart';

class ScoresScreen extends StatefulWidget {
  const ScoresScreen({super.key});

  @override
  State<ScoresScreen> createState() => _ScoresScreenState();
}

class _ScoresScreenState extends State<ScoresScreen> with TickerProviderStateMixin {
  late AnimationController _controller;
  late AnimationController _overlayController;
  late Animation<double> _fadeAnimation;
  late Animation<double> _scaleAnimation;

  bool showFinGameOverlay = false;
  bool hasNavigatedToClassement = false;
  StreamSubscription<String>? _messageSubscription;

  @override
  void initState() {
    super.initState();
    _controller = AnimationController(duration: const Duration(milliseconds: 500), vsync: this);
    _fadeAnimation = Tween<double>(begin: 0, end: 1).animate(_controller);
    _scaleAnimation = Tween<double>(begin: 0.95, end: 1).animate(_controller);
    SchedulerBinding.instance.addPostFrameCallback((_) => _controller.forward());

    _overlayController = AnimationController(
      vsync: this,
      duration: const Duration(milliseconds: 500),
    );

    final webSocketService = Provider.of<WebSocketService>(context, listen: false);
    _messageSubscription = webSocketService.messages.listen(_handleWebSocketMessage);
  }

  void _handleWebSocketMessage(String message) {
    try {
      final data = json.decode(message);

      if (data is Map<String, dynamic>) {
        if (data['type'] == 'fin') {
          _showFinGameOverlay();
        } else if (data['type'] == 'start') {
          Provider.of<WebSocketService>(context, listen: false).resetAllScores();
        }
      }
    } catch (e) {
      debugPrint('Erreur WebSocket : $e');
    }
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

  @override
  void dispose() {
    _controller.dispose();
    _overlayController.dispose();
    _messageSubscription?.cancel();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    final ws = Provider.of<WebSocketService>(context);
    final theme = Theme.of(context);

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
}