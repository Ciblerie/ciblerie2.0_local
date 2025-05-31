import 'package:flutter/material.dart';
import 'package:fl_chart/fl_chart.dart';

class PlayerPieChart extends StatelessWidget {
  const PlayerPieChart({super.key});

  @override
  Widget build(BuildContext context) {
    return FittedBox(
      fit: BoxFit.contain,
      child: SizedBox(
        width: 300,
        height: 300,
      child: PieChart(
        PieChartData(
          sections: [
            PieChartSectionData(
              value: 40,
              color: Colors.redAccent,
              title: 'Torse',
              radius: 60,
              titleStyle: const TextStyle(
                fontSize: 12,
                fontWeight: FontWeight.bold,
                color: Colors.white,
              ),
            ),
            PieChartSectionData(
              value: 30,
              color: Colors.amber,
              title: 'Head',
              radius: 60,
              titleStyle: const TextStyle(
                fontSize: 12,
                fontWeight: FontWeight.bold,
                color: Colors.black,
              ),
            ),
            PieChartSectionData(
              value: 30,
              color: Colors.blueAccent,
              title: 'Membres',
              radius: 60,
              titleStyle: const TextStyle(
                fontSize: 12,
                fontWeight: FontWeight.bold,
                color: Colors.white,
              ),
            ),
          ],
          sectionsSpace: 2,
          centerSpaceRadius: 32,
        ),
       ),
      ),
    );
  }
}
