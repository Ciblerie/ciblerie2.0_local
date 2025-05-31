import 'package:flutter/material.dart';
import 'dart:convert';
import 'package:flutter/scheduler.dart';
import 'package:provider/provider.dart';
import '../services/score_history_service.dart';
import '../services/websocket_service.dart';

class StatsScreen extends StatefulWidget {
  const StatsScreen({super.key});

  @override
  State<StatsScreen> createState() => _StatsScreenState();
}

class _StatsScreenState extends State<StatsScreen> with SingleTickerProviderStateMixin {
  late AnimationController _controller;
  late Animation<double> _fadeAnimation;
  late Animation<double> _scaleAnimation;

  final List<Color> greenGradient = [
    const Color(0xFFA8E6A3),
    const Color(0xFF8CD58B),
    const Color(0xFF6ACD72),
    const Color(0xFF4AB25A),
  ];

  final List<Map<String, dynamic>> _playerStats = List.generate(4, (index) => {
    'score': 0,
    'total': 0,
    'best': 0,
    'games': 0,
    'group': '-',
    'frequencies': {
      0: 0,
      5: 0,
      10: 0,
      15: 0,
      25: 0,
      50: 0,
      100: 0,
      150: 0,
      200: 0,
      250: 0,
    },
    'history': <Map<String, dynamic>>[],
  });

  @override
  void initState() {
    super.initState();
    _controller = AnimationController(duration: const Duration(milliseconds: 500), vsync: this);
    _fadeAnimation = Tween<double>(begin: 0, end: 1).animate(_controller);
    _scaleAnimation = Tween<double>(begin: 0.95, end: 1).animate(_controller);
    SchedulerBinding.instance.addPostFrameCallback((_) => _controller.forward());

    _loadStats();
  }

  Future<void> _loadStats() async {
    final stored = await ScoreHistoryService.loadScores();
    if (stored.isNotEmpty) {
      setState(() {
        for (int i = 0; i < 4; i++) {
          String key = 'J${i + 1}';
          final entries = stored[key];
          if (entries != null && entries.isNotEmpty) {
            final scores = entries.map<int>((e) => (e['score'] ?? 0) as int).toList();
            final int total = scores.fold(0, (a, b) => a + b);
            final int best = scores.reduce((a, b) => a > b ? a : b);
            final int latest = scores.last;

            final freq = {0: 0, 5: 0, 10: 0, 15: 0, 25: 0, 50: 0, 100: 0, 150: 0, 200: 0, 250: 0};
            for (var s in scores) {
              if (freq.containsKey(s)) freq[s] = freq[s]! + 1;
            }

            final group = entries.last['group'] ?? '-';

            _playerStats[i]['score'] = latest;
            _playerStats[i]['total'] = total;
            _playerStats[i]['best'] = best;
            _playerStats[i]['games'] = scores.length;
            _playerStats[i]['group'] = group;
            _playerStats[i]['frequencies'] = freq;
            _playerStats[i]['history'] = entries;

            // Envoi des messages "Jx", "scores", "points", et "pointBonus"
            final ws = Provider.of<WebSocketService>(context, listen: false);
            final jsonMessage = {
              'Jx': i + 1,
              'scores': latest,
              'points': scores.last,
              'pointBonus': freq[scores.last] ?? 0,
            };
            ws.sendMessage(json.encode(jsonMessage));
          }
        }
      });
    }
  }

  void _resetPlayerStats(int index) {
    final ws = Provider.of<WebSocketService>(context, listen: false);

    setState(() {
      _playerStats[index] = {
        'score': 0,
        'total': 0,
        'best': 0,
        'games': 0,
        'group': '-',
        'frequencies': {0: 0, 5: 0, 10: 0, 15: 0, 25: 0, 50: 0, 100: 0, 150: 0, 200: 0, 250: 0},
        'history': <Map<String, dynamic>>[],
      };
    });

    final updatedScores = Map<int, int>.from(ws.scoresNotifier.value);
    updatedScores[index] = 0;
    ws.scoresNotifier.value = updatedScores;

    final updatedFreqs = Map<int, Map<int, int>>.from(ws.frequenciesNotifier.value);
    updatedFreqs[index] = {0: 0, 5: 0, 10: 0, 15: 0, 25: 0, 50: 0, 100: 0, 150: 0, 200: 0, 250: 0};
    ws.frequenciesNotifier.value = updatedFreqs;
  }

  @override
  void dispose() {
    _controller.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    final ws = Provider.of<WebSocketService>(context);
    final pseudos = ws.pseudonymsNotifier.value;

    return LayoutBuilder(
      builder: (context, constraints) {
        final double spacing = constraints.maxWidth * 0.02;

        return Scaffold(
          appBar: AppBar(
            title: const Row(
              children: [
                Icon(Icons.show_chart),
                SizedBox(width: 8),
                Text('Statistiques'),
              ],
            ),
          ),
          body: Padding(
            padding: EdgeInsets.all(spacing),
            child: FadeTransition(
              opacity: _fadeAnimation,
              child: ScaleTransition(
                scale: _scaleAnimation,
                child: ValueListenableBuilder<Map<int, int>>(
                  valueListenable: ws.scoresNotifier,
                  builder: (context, liveScores, _) {
                    if (liveScores.values.every((score) => score == 0)) {
                      for (int i = 0; i < 4; i++) {
                        if (_playerStats[i]['group'] != '-') {
                          _playerStats[i]['group'] = '-';
                        }
                      }
                    }

                    return ValueListenableBuilder<Map<int, Map<int, int>>>(
                      valueListenable: ws.frequenciesNotifier,
                      builder: (context, frequencies, _) {
                        return Row(
                          crossAxisAlignment: CrossAxisAlignment.start,
                          children: List.generate(4, (index) {
                            final player = _playerStats[index];
                            final List<Map<String, dynamic>> history =
                            List<Map<String, dynamic>>.from(player['history']);

                            final int currentScore = liveScores[index] ?? 0;
                            final int totalWithLive = history.fold<int>(
                              0,
                                  (sum, entry) => sum + ((entry['score'] ?? 0) as int),
                            ) + currentScore;

                            final Map<int, int> liveFreq = frequencies[index] ?? {
                              0: 0,
                              5: 0,
                              10: 0,
                              15: 0,
                              25: 0,
                              50: 0,
                              100: 0,
                              150: 0,
                              200: 0,
                              250: 0,
                            };

                            final String groupToDisplay = currentScore > 0
                                ? ws.groupNotifier.value
                                : (player['group'] ?? '-');

                            return Expanded(
                              child: Container(
                                margin: EdgeInsets.symmetric(horizontal: spacing / 2),
                                padding: const EdgeInsets.all(16),
                                decoration: BoxDecoration(
                                  color: greenGradient[index % greenGradient.length],
                                  borderRadius: BorderRadius.circular(16),
                                ),
                                child: Column(
                                  crossAxisAlignment: CrossAxisAlignment.start,
                                  children: [
                                    Row(
                                      children: [
                                        Expanded(
                                          child: Text(
                                            pseudos[index] ?? 'J${index + 1}',
                                            style: const TextStyle(
                                              fontSize: 20,
                                              fontWeight: FontWeight.bold,
                                              color: Colors.black,
                                            ),
                                          ),
                                        ),
                                        ElevatedButton.icon(
                                          onPressed: () => _resetPlayerStats(index),
                                          style: ElevatedButton.styleFrom(
                                            backgroundColor: Colors.red,
                                            shape: RoundedRectangleBorder(
                                              borderRadius: BorderRadius.circular(12),
                                            ),
                                          ),
                                          icon: const Icon(Icons.refresh, color: Colors.black, size: 18),
                                          label: const Text(
                                            'Reset',
                                            style: TextStyle(
                                              color: Colors.black,
                                              fontWeight: FontWeight.bold,
                                            ),
                                          ),
                                        ),
                                      ],
                                    ),
                                    const SizedBox(height: 12),
                                    Text('Parties jouées : ${player['games']}', style: const TextStyle(fontSize: 14, color: Colors.black)),
                                    Text('Groupe : $groupToDisplay', style: const TextStyle(fontSize: 14, color: Colors.black)),
                                    Text('Score : $currentScore', style: const TextStyle(fontSize: 14, color: Colors.black)),
                                    Text('Totalisé : $totalWithLive', style: const TextStyle(fontSize: 14, color: Colors.black)),
                                    Text('Meilleur score : ${player['best']}', style: const TextStyle(fontSize: 14, color: Colors.black)),
                                    const SizedBox(height: 12),
                                    const Text('Tableau des fréquences :', style: TextStyle(fontWeight: FontWeight.bold, color: Colors.black)),
                                    const SizedBox(height: 6),
                                    ...[0, 5, 10, 15, 25, 50, 100, 150, 200, 250].map((pt) => Text(
                                      '$pt points : ${liveFreq[pt] ?? 0}',
                                      style: const TextStyle(color: Colors.black),
                                    )),
                                    const SizedBox(height: 12),
                                    const Text('Scores enregistrés :', style: TextStyle(fontWeight: FontWeight.bold, color: Colors.black)),
                                    const SizedBox(height: 6),
                                    if (history.isEmpty)
                                      const Text("Aucune donnée enregistrée."),
                                    ...history.map((entry) {
                                      final g = entry['group'] ?? player['group'] ?? '-';
                                      final s = entry['score'] ?? 0;
                                      return Text('Groupe $g : $s', style: const TextStyle(color: Colors.black));
                                    }),
                                  ],
                                ),
                              ),
                            );
                          }),
                        );
                      },
                    );
                  },
                ),
              ),
            ),
          ),
        );
      },
    );
  }
}
