import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import '../screens/classement_general_screen.dart';

class NewRecordDialog extends StatefulWidget {
  final int playerId;
  final int score;
  final String pseudo;

  const NewRecordDialog({super.key, required this.playerId, required this.score, required this.pseudo});

  @override
  State<NewRecordDialog> createState() => _NewRecordDialogState();
}

class _NewRecordDialogState extends State<NewRecordDialog> {
  final _storage = const FlutterSecureStorage();
  String? _errorMessage;

  @override
  Widget build(BuildContext context) {
    return AlertDialog(
      title: const Text('🎯 Nouveau Record !'),
      content: Column(
        mainAxisSize: MainAxisSize.min,
        children: [
          Text('Pseudo: ${widget.pseudo}'),
          Text('Score: ${widget.score}'),
          if (_errorMessage != null)
            Text(
              _errorMessage!,
              style: const TextStyle(color: Colors.red),
            ),
        ],
      ),
      actions: [
        Center(
          child: ElevatedButton(
            onPressed: () async {
              final playerScores = await _loadPlayerScores();
              String pseudo = widget.pseudo;
              if (playerScores.containsKey(pseudo)) {
                List<dynamic> scores = playerScores[pseudo];
                if (widget.score <= (scores.isNotEmpty ? scores.cast<int>().reduce((a, b) => a > b ? a : b) : 0)) {
                  setState(() {
                    _errorMessage = 'Votre nouveau score n\'est pas un record pour ce pseudo.';
                  });
                  return;
                }
                scores.add(widget.score);
                playerScores[pseudo] = scores;
              } else {
                playerScores[pseudo] = [widget.score];
              }
              await _savePlayerScores(playerScores);
              if (!mounted) return;
              Navigator.pushReplacement(
                context,
                MaterialPageRoute(builder: (context) => const ClassementGeneralScreen()),
              );
            },
            child: const Text('Valider'),
          ),
        ),
      ],
    );
  }

  Future<Map<String, dynamic>> _loadPlayerScores() async {
    final json = await _storage.read(key: 'player_scores');
    if (json == null) {
      return {};
    }
    return Map<String, dynamic>.from(jsonDecode(json));
  }

  Future<void> _savePlayerScores(Map<String, dynamic> playerScores) async {
    final json = jsonEncode(playerScores);
    await _storage.write(key: 'player_scores', value: json);
  }
}
