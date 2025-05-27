import 'dart:convert';
import 'package:flutter/services.dart';
import '../models/grade.dart';

class GradeService {
  static final GradeService _instance = GradeService._internal();
  factory GradeService() => _instance;
  GradeService._internal();

  List<Grade> _grades = [];

  Future<void> loadGrades() async {
    final String jsonString = await rootBundle.loadString('assets/grades.json');
    final List<dynamic> jsonData = json.decode(jsonString);
    _grades = jsonData.map((grade) => Grade.fromJson(grade)).toList();
  }

  List<Grade> get grades => _grades;

  Grade? getGradeById(int id) {
    try {
      return _grades.firstWhere((grade) => grade.id == id);
    } catch (_) {
      return null;
    }
  }

  Grade? getNextGrade(Grade grade) {
    if (grade.promotionTo == null) return null;
    return getGradeById(grade.promotionTo!);
  }

  Grade? getPreviousGrade(Grade grade) {
    if (grade.demotionTo == null) return null;
    return getGradeById(grade.demotionTo!);
  }

  Grade getInitialGrade() {
    return _grades.firstWhere((grade) => grade.id == 1);
  }

  /// Avance d'une étoile. Si maxStars atteint, retourne le grade suivant
  Grade progress(Grade currentGrade) {
    if (currentGrade.stars < currentGrade.maxStars) {
      return currentGrade; // Incrément de l’étoile géré ailleurs
    } else {
      return getNextGrade(currentGrade) ?? currentGrade;
    }
  }

  /// Recul d'une étoile ou rétrograde si 0
  Grade regress(Grade currentGrade) {
    if (currentGrade.stars > 1) {
      return currentGrade; // Décrément de l’étoile géré ailleurs
    } else {
      return getPreviousGrade(currentGrade) ?? currentGrade;
    }
  }
}
