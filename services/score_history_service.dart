import 'dart:convert';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';

class ScoreHistoryService {
  static final FlutterSecureStorage _storage = const FlutterSecureStorage();
  static const _key = 'score_history';

  /// Sauvegarde les scores avec le groupe courant
  static Future<void> saveScores(List<int> scores, {String group = "A"}) async {
    try {
      final existingData = await _storage.read(key: _key);
      final Map<String, dynamic> currentData =
      existingData != null ? jsonDecode(existingData) : {};

      final String now = DateTime.now().toIso8601String();

      for (int i = 0; i < scores.length; i++) {
        final playerKey = 'J${i + 1}';
        final entry = {
          'score': scores[i],
          'date': now,
          'group': group,
        };

        final List<Map<String, dynamic>> playerScores =
            (currentData[playerKey] as List?)?.cast<Map<String, dynamic>>() ?? [];
        playerScores.add(entry);
        currentData[playerKey] = playerScores;
      }

      await _storage.write(key: _key, value: jsonEncode(currentData));
    } catch (e) {
      print('Erreur dans saveScores : $e');
    }
  }

  /// Charge tous les scores de chaque joueur
  static Future<Map<String, List<Map<String, dynamic>>>> loadScores() async {
    try {
      final stored = await _storage.read(key: _key);
      if (stored == null) return {};

      final Map<String, dynamic> decoded = jsonDecode(stored);
      return decoded.map((key, value) {
        final entries = (value as List)
            .map<Map<String, dynamic>>((e) => Map<String, dynamic>.from(e))
            .toList();
        return MapEntry(key, entries);
      });
    } catch (e) {
      print('Erreur dans loadScores : $e');
      return {};
    }
  }

  /// Réinitialise complètement tous les scores
  static Future<void> clearScores() async {
    try {
      await _storage.delete(key: _key);
    } catch (e) {
      print('Erreur dans clearScores : $e');
    }
  }
}
