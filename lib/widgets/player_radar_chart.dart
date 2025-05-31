import 'package:flutter/material.dart';
import 'package:fl_chart/fl_chart.dart';

class PlayerRadarChart extends StatelessWidget {
  const PlayerRadarChart({super.key});

  @override
  Widget build(BuildContext context) {
    return FittedBox(
      fit: BoxFit.contain,
      child: SizedBox(
        width: 300,
        height: 300,
      child: RadarChart(
        RadarChartData(
          radarShape: RadarShape.polygon,
          radarBorderData: const BorderSide(color: Colors.white),
          radarBackgroundColor: Colors.transparent,
          tickCount: 5,
          ticksTextStyle: const TextStyle(
            color: Colors.grey,
            fontSize: 10,
          ),
          tickBorderData: const BorderSide(color: Colors.grey),
          gridBorderData: const BorderSide(color: Colors.white30),
          titleTextStyle: const TextStyle(
            color: Colors.white,
            fontSize: 12,
          ),
          // ✅ Supprimé getTitle : plus d’erreur
          dataSets: [
            RadarDataSet(
              dataEntries: const [
                RadarEntry(value: 3),
                RadarEntry(value: 4.5),
                RadarEntry(value: 4),
                RadarEntry(value: 2),
                RadarEntry(value: 5),
              ],
              fillColor: Colors.blue.withOpacity(0.4),
              borderColor: Colors.blueAccent,
              entryRadius: 3,
              borderWidth: 2,
            ),
          ],
        ),
       ),
      ),
    );
  }
}
