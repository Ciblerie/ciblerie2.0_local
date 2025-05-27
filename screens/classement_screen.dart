import 'package:flutter/material.dart';
import 'package:flutter/scheduler.dart';
import 'package:provider/provider.dart';
import '../services/score_history_service.dart';
import '../services/websocket_service.dart';
import 'stats_screen.dart';

class ClassementScreen extends StatefulWidget {
  final List<int>? finalScores;

  const ClassementScreen({super.key, this.finalScores});

  @override
  State<ClassementScreen> createState() => _ClassementScreenState();
}

class _ClassementScreenState extends State<ClassementScreen> with SingleTickerProviderStateMixin {
  late AnimationController _controller;
  late Animation<double> _fadeAnimation;
  late Animation<double> _scaleAnimation;

  final List<List<Color>> gradientColorsList = const [
    [Color(0xFFFFF3E0), Color(0xFFFFCC80)],
    [Color(0xFFFFE0B2), Color(0xFFFFB74D)],
    [Color(0xFFFFCC80), Color(0xFFFFA726)],
    [Color(0xFFFFB74D), Color(0xFFFF8A65)],
    [Color(0xFFFFA726), Color(0xFFFF7043)],
    [Color(0xFFFF8A65), Color(0xFFFF5722)],
  ];

  @override
  void initState() {
    super.initState();
    _controller = AnimationController(duration: const Duration(milliseconds: 500), vsync: this);
    _fadeAnimation = Tween<double>(begin: 0, end: 1).animate(_controller);
    _scaleAnimation = Tween<double>(begin: 0.95, end: 1).animate(_controller);
    SchedulerBinding.instance.addPostFrameCallback((_) => _controller.forward());

    if (widget.finalScores != null) {
      Provider.of<WebSocketService>(context, listen: false).lastFinalScores.value = widget.finalScores;
    }
  }

  @override
  void dispose() {
    _controller.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    final ws = Provider.of<WebSocketService>(context);

    return Scaffold(
      appBar: AppBar(
        title: const Row(
          children: [
            Icon(Icons.emoji_events),
            SizedBox(width: 8),
            Text('Classement'),
          ],
        ),
        actions: [
          ValueListenableBuilder<bool>(
            valueListenable: ws.showSaveButton,
            builder: (context, show, _) {
              if (!show) return const SizedBox.shrink();

              return Padding(
                padding: const EdgeInsets.only(right: 12.0),
                child: ElevatedButton(
                  onPressed: () async {
                    final scores = ws.lastFinalScores.value;
                    if (scores != null && scores.isNotEmpty) {
                      await ScoreHistoryService.saveScores(scores, group: ws.groupNotifier.value);
                      ws.resetAllScores();
                      ws.showSaveButton.value = false;

                      // Correction ici :
                      ws.setGameState(GameState.waitingGroup); // ← Changement

                      ScaffoldMessenger.of(context).showSnackBar(
                        const SnackBar(content: Text('Scores enregistrés avec succès!')),
                      );

                      Navigator.pushAndRemoveUntil(
                        context,
                        MaterialPageRoute(builder: (_) => const StatsScreen()),
                            (route) => route.isFirst,
                      );
                    }
                  },
                  style: ElevatedButton.styleFrom(
                    backgroundColor: Colors.teal,
                    shape: RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(20),
                    ),
                  ),
                  child: const Text('Enregistrer la partie'),
                ),
              );
            },
          ),
        ],
      ),
      body: ValueListenableBuilder<List<int>?>(
        valueListenable: ws.lastFinalScores,
        builder: (context, scores, _) {
          if (scores == null || scores.isEmpty) {
            return const Center(
              child: Text(
                'Aucun classement disponible.',
                style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold),
              ),
            );
          }

          final pseudos = ws.pseudonymsNotifier.value;
          final sortedPlayers = List.generate(scores.length, (index) => {
            'name': pseudos[index] ?? 'J${index + 1}',
            'score': scores[index],
          })..sort((a, b) => ((b['score'] as int).compareTo(a['score'] as int)));

          final int playerCount = sortedPlayers.length;

          return FadeTransition(
            opacity: _fadeAnimation,
            child: ScaleTransition(
              scale: _scaleAnimation,
              child: LayoutBuilder(
                builder: (context, constraints) {
                  double totalHeight = constraints.maxHeight;
                  double spacing = totalHeight * 0.02;
                  double availableHeight = totalHeight - spacing * (playerCount + 1);
                  double barHeight = availableHeight / (playerCount > 0 ? playerCount : 1);

                  return SingleChildScrollView(
                    child: Padding(
                      padding: EdgeInsets.symmetric(vertical: spacing, horizontal: spacing),
                      child: Column(
                        children: List.generate(playerCount, (index) {
                          final player = sortedPlayers[index];
                          final colors = gradientColorsList[index % gradientColorsList.length];
                          return Padding(
                            padding: EdgeInsets.only(bottom: spacing),
                            child: _buildScoreBar(
                              '${index + 1}: ${player['name']} : ${player['score']}',
                              constraints.maxWidth,
                              barHeight,
                              colors,
                            ),
                          );
                        }),
                      ),
                    ),
                  );
                },
              ),
            ),
          );
        },
      ),
    );
  }

  Widget _buildScoreBar(String text, double width, double height, List<Color> gradientColors) {
    return Container(
      width: width,
      height: height,
      decoration: BoxDecoration(
        gradient: LinearGradient(
          colors: gradientColors,
          begin: Alignment.centerLeft,
          end: Alignment.centerRight,
        ),
        borderRadius: BorderRadius.circular(16),
      ),
      alignment: Alignment.center,
      child: FittedBox(
        fit: BoxFit.scaleDown,
        child: Text(
          text,
          style: const TextStyle(
            fontSize: 100,
            fontWeight: FontWeight.bold,
            color: Colors.white,
          ),
        ),
      ),
    );
  }
}
