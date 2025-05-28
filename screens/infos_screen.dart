import 'package:flutter/material.dart';
import '../models/grade.dart';
import '../services/grade_service.dart';
import '../widgets/grade_viewer.dart';
import '../widgets/player_radar_chart.dart';
import '../widgets/player_pie_chart.dart';
import '../utils/responsive_builder.dart';

class InfosScreen extends StatefulWidget {
  const InfosScreen({Key? key}) : super(key: key);

  @override
  State<InfosScreen> createState() => _InfosScreenState();
}

class _InfosScreenState extends State<InfosScreen> {
  late Future<void> _initGrades;
  late Grade _currentGrade;
  int _currentStars = 1;

  @override
  void initState() {
    super.initState();
    _initGrades = _loadGradeData();
  }

  Future<void> _loadGradeData() async {
    await GradeService().loadGrades();
    _currentGrade = GradeService().getInitialGrade();
  }

  void _progress() {
    setState(() {
      if (_currentStars < _currentGrade.maxStars) {
        _currentStars++;
      } else {
        final next = GradeService().getNextGrade(_currentGrade);
        if (next != null) {
          _currentGrade = next;
          _currentStars = 1;
        }
      }
    });
  }

  void _regress() {
    setState(() {
      if (_currentStars > 1) {
        _currentStars--;
      } else {
        final prev = GradeService().getPreviousGrade(_currentGrade);
        if (prev != null) {
          _currentGrade = prev;
          _currentStars = prev.maxStars;
        }
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    return FutureBuilder<void>(
      future: _initGrades,
      builder: (context, snapshot) {
        if (snapshot.connectionState == ConnectionState.waiting) {
          return const Scaffold(
            backgroundColor: Colors.black,
            body: Center(child: CircularProgressIndicator()),
          );
        } else if (snapshot.hasError) {
          return Scaffold(
            backgroundColor: Colors.red[900],
            body: Center(
              child: Text(
                'Erreur : ${snapshot.error}',
                style: const TextStyle(color: Colors.white),
              ),
            ),
          );
        }

        return Scaffold(
          appBar: AppBar(title: const Text("Mode Compétition")),
          backgroundColor: Colors.grey[900],
          body: Padding(
            padding: EdgeInsets.all(getPaddingResponsive(context)),
            child: LayoutBuilder(
              builder: (context, constraints) {
                final isSmallScreen = constraints.maxWidth < 700;

                if (isSmallScreen) {
                  // Mobile fallback (empile en colonne)
                  return Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      GradeViewer(
                        grade: _currentGrade,
                        currentStars: _currentStars,
                        size: getGradeIconSize(context),
                      ),
                      const SizedBox(height: 24),
                      Row(
                        mainAxisAlignment: MainAxisAlignment.center,
                        children: [
                          ElevatedButton.icon(
                            onPressed: _regress,
                            icon: const Icon(Icons.arrow_downward),
                            label: const Text("Rétrograder"),
                          ),
                          const SizedBox(width: 16),
                          ElevatedButton.icon(
                            onPressed: _progress,
                            icon: const Icon(Icons.arrow_upward),
                            label: const Text("Monter"),
                          ),
                        ],
                      ),
                      const SizedBox(height: 32),
                      const PlayerRadarChart(),
                      const SizedBox(height: 32),
                      const PlayerPieChart(),
                    ],
                  );
                }

                // Grand écran : deux colonnes côte à côte
                return Row(
                  children: [
                    // Colonne de gauche : Grade
                    Expanded(
                      flex: 1,
                      child: Column(
                        mainAxisAlignment: MainAxisAlignment.center,
                        children: [
                          GradeViewer(
                            grade: _currentGrade,
                            currentStars: _currentStars,
                            size: getGradeIconSize(context),
                          ),
                          const SizedBox(height: 24),
                          Row(
                            mainAxisAlignment: MainAxisAlignment.center,
                            children: [
                              SizedBox(
                                width: getButtonWidth(context),
                                child: ElevatedButton.icon(
                                  onPressed: _regress,
                                  icon: const Icon(Icons.arrow_downward),
                                  label: const Text("Rétrograder"),
                                ),
                              ),
                              const SizedBox(width: 12),
                              SizedBox(
                                width: getButtonWidth(context),
                                child: ElevatedButton.icon(
                                  onPressed: _progress,
                                  icon: const Icon(Icons.arrow_upward),
                                  label: const Text("Monter"),
                                ),
                              ),
                            ],
                          ),
                        ],
                      ),
                    ),

                    const SizedBox(width: 32),

                    // Colonne de droite : Stats
                    Expanded(
                      child: SingleChildScrollView(
                        child: Column(
                          mainAxisAlignment: MainAxisAlignment.center,
                          children: const [
                            PlayerRadarChart(),
                            SizedBox(height: 20),
                            PlayerPieChart(),
                        ],
                      ),
                     ),
                    ),
                  ],
                );
              },
            ),
          ),
        );
      },
    );
  }
}
