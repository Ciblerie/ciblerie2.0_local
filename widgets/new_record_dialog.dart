import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:flutter_secure_storage/flutter_secure_storage.dart';
import '../screens/classement_general_screen.dart';

class NewRecordDialog extends StatefulWidget {
  final int score;
  final String playerId;

  const NewRecordDialog({
    super.key,
    required this.score,
    required this.playerId,
  });

  @override
  State<NewRecordDialog> createState() => _NewRecordDialogState();
}

class _NewRecordDialogState extends State<NewRecordDialog> {
  final _controller = TextEditingController();
  String? _error;

  @override
  void initState() {
    super.initState();
    _controller.text = widget.playerId;
  }

  Future<void> _validateAndSave() async {
    final pseudo = _controller.text.trim();
    if (pseudo.isEmpty) return;

    final storage = const FlutterSecureStorage();
    final raw = await storage.read(key: 'player_scores');
    Map<String, dynamic> allScores = {};

    if (raw != null) {
      allScores = jsonDecode(raw);
    }

    final existingEntries = allScores[pseudo];
    int? bestExisting;

    if (existingEntries != null) {
      final parsed = (existingEntries as List)
          .map((e) => Map<String, dynamic>.from(e))
          .toList();

      bestExisting = parsed
          .map((e) => e['score'] is int ? e['score'] as int : 0)
          .fold<int>(0, (int a, int b) => a > b ? a : b);
    }

    if (bestExisting != null && widget.score <= bestExisting) {
      setState(() {
        _error = 'Record à battre pour ce pseudo : $bestExisting';
      });
      return;
    }

    final entry = {'score': widget.score, 'group': '-'};

    if (existingEntries != null) {
      allScores[pseudo].add(entry);
    } else {
      allScores[pseudo] = [entry];
    }

    await storage.write(key: 'player_scores', value: jsonEncode(allScores));

    if (mounted) {
      // ✅ Ferme le dialogue proprement
      Navigator.of(context, rootNavigator: true).pop();
      // ✅ Redirige immédiatement vers le classement
      Navigator.of(context).pushReplacement(
        MaterialPageRoute(builder: (_) => const ClassementGeneralScreen()),
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    return AlertDialog(
      title: const Text('🎯 Nouveau record !'),
      content: Column(
        mainAxisSize: MainAxisSize.min,
        children: [
          Text('Meilleur score : ${widget.score}', style: const TextStyle(fontSize: 18)),
          const SizedBox(height: 12),
          TextField(
            controller: _controller,
            decoration: const InputDecoration(labelText: 'Nom du joueur'),
          ),
          if (_error != null)
            Padding(
              padding: const EdgeInsets.only(top: 10),
              child: Text(_error!, style: const TextStyle(color: Colors.red)),
            ),
        ],
      ),
      actions: [
        TextButton(
          onPressed: _validateAndSave,
          child: const Text('Valider'),
        ),
        TextButton(
          onPressed: () => Navigator.of(context, rootNavigator: true).pop(),
          child: const Text('Annuler'),
        ),
      ],
    );
  }
}
