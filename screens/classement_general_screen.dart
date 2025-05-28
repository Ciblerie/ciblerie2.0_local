import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';

class ClassementGeneralScreen extends StatefulWidget {
  const ClassementGeneralScreen({super.key});

  @override
  State<ClassementGeneralScreen> createState() => _ClassementGeneralScreenState();
}

class _ClassementGeneralScreenState extends State<ClassementGeneralScreen> with TickerProviderStateMixin {
  Map<String, int> _bestScores = {};

  final List<List<Color>> fixedGradients = [
    [Color(0xFF4A148C), Color(0xFF6A1B9A)], // 1er
    [Color(0xFF6A1B9A), Color(0xFF8E24AA)], // 2e
    [Color(0xFF8E24AA), Color(0xFFBA68C8)], // 3e
  ];
  final List<double> fixedFontSizes = [48, 40, 34];
  final List<Color> defaultGradient = [Color(0xFFBA68C8), Color(0xFFCE93D8)];
  final double defaultFontSize = 28;

  late AnimationController _controller;
  late Animation<double> _fadeAnimation;
  late Animation<double> _scaleAnimation;

  @override
  void initState() {
    super.initState();

    _loadBestScores();

    _controller = AnimationController(
      duration: const Duration(milliseconds: 1000),
      vsync: this,
    );
    _fadeAnimation = Tween<double>(begin: 0, end: 1).animate(_controller);
    _scaleAnimation = Tween<double>(begin: 0.5, end: 1).animate(_controller);

    _controller.forward();
  }

  @override
  void dispose() {
    _controller.dispose();
    super.dispose();
  }

  Future<void> _loadBestScores() async {
    const storage = FlutterSecureStorage();
    final raw = await storage.read(key: 'player_scores');
    if (raw == null) return;

    final decoded = jsonDecode(raw) as Map<String, dynamic>;
    Map<String, int> scores = {};

    decoded.forEach((player, entries) {
      final list = (entries as List).map((e) => Map<String, dynamic>.from(e)).toList();

      final best = list.fold<int>(0, (max, e) {
        final score = e['score'];
        if (score is int) {
          return score > max ? score : max;
        }
        return max;
      });

      scores[player] = best;
    });

    setState(() {
      _bestScores = scores;
    });
  }

  @override
  Widget build(BuildContext context) {
    final sortedEntries = _bestScores.entries.toList()
      ..sort((a, b) => b.value.compareTo(a.value));

    final totalPlayers = sortedEntries.length < 6 ? 6 : sortedEntries.length;

    return Scaffold(
      appBar: AppBar(
        title: const Text('Classement général'),
      ),
      body: SafeArea(
        child: FadeTransition(
          opacity: _fadeAnimation,
          child: ScaleTransition(
            scale: _scaleAnimation,
            child: ListView.builder(
              itemCount: totalPlayers,
              itemBuilder: (context, index) {
                final rank = index + 1;

                final label = sortedEntries.length > index
                    ? '$rank${_suffix(rank)} : ${sortedEntries[index].key} (${sortedEntries[index].value})'
                    : '$rank${_suffix(rank)} :';

                final gradient = index < 3 ? fixedGradients[index] : defaultGradient;
                final fontSize = index < 3 ? fixedFontSizes[index] : defaultFontSize;

                return GestureDetector(
                  onTap: () {
                    // Future onTap logic
                  },
                  child: Container(
                    height: 80,
                    margin: const EdgeInsets.symmetric(vertical: 6, horizontal: 16),
                    decoration: BoxDecoration(
                      gradient: LinearGradient(
                        colors: gradient,
                        begin: Alignment.centerLeft,
                        end: Alignment.centerRight,
                      ),
                      borderRadius: BorderRadius.circular(16),
                    ),
                    child: Center(
                      child: Text(
                        label,
                        style: TextStyle(
                          fontSize: fontSize,
                          fontWeight: FontWeight.bold,
                          color: Colors.black,
                        ),
                      ),
                    ),
                  ),
                );
              },
            ),
          ),
        ),
      ),
    );
  }

  String _suffix(int rank) => rank == 1 ? 'er' : 'e';
}
