import 'package:flutter/material.dart';
import '../models/grade.dart';

class GradeViewer extends StatelessWidget {
  final Grade grade;
  final int currentStars;
  final double size;

  const GradeViewer({
    Key? key,
    required this.grade,
    required this.currentStars,
    this.size = 220,
  }) : super(key: key);

  @override
  Widget build(BuildContext context) {

    final screenWidth = MediaQuery.of(context).size.width;
    final imageSize = screenWidth * 0.25;

    return AnimatedSwitcher(
      duration: const Duration(milliseconds: 400),
      switchInCurve: Curves.easeIn,
      switchOutCurve: Curves.easeOut,
      transitionBuilder: (child, animation) {
        return FadeTransition(
          opacity: animation,
          child: ScaleTransition(scale: animation, child: child),
        );
      },
      child: Column(
        key: ValueKey<String>(grade.name),
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          // Icône en haute qualité avec anti-aliasing
          ClipRRect(
            borderRadius: BorderRadius.circular(16), // optionnel : coins doux
            child: SizedBox(
              width: imageSize,
              height: imageSize,
              child: Image.asset(
                grade.icon,
                fit: BoxFit.contain,
                filterQuality: FilterQuality.high,
                cacheWidth: 1024, // ou la vraie résolution
              ),
            ),
          ),

          const SizedBox(height: 16),

          Text(
            grade.name,
            style: const TextStyle(
              fontSize: 20,
              fontWeight: FontWeight.bold,
              color: Colors.white,
            ),
          ),

          const SizedBox(height: 8),

          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: List.generate(
              grade.maxStars,
                  (index) => Padding(
                padding: const EdgeInsets.symmetric(horizontal: 2),
                child: Icon(
                  index < currentStars ? Icons.star : Icons.star_border,
                  color: index < currentStars ? Colors.amber : Colors.grey,
                  size: 28,
                ),
              ),
            ),
          ),

          const SizedBox(height: 8),

          Text(
            'Rétrogradation : ${grade.demotionRule}',
            style: TextStyle(
              fontSize: 12,
              color: Colors.grey[400],
            ),
          ),
        ],
      ),
    );
  }
}
