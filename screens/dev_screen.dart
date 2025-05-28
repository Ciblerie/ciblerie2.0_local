import 'dart:convert'; // Ajout pour json
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../services/websocket_service.dart';
import '../models/group_model.dart';
import 'package:ciblerie_local/screens/scores_screen.dart';

class DevScreen extends StatelessWidget {
  const DevScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Développement'),
        backgroundColor: Colors.black,
      ),
      body: Center(
        child: Container(
          constraints: const BoxConstraints(maxWidth: 850),
          padding: const EdgeInsets.all(24),
          margin: const EdgeInsets.all(16),
          decoration: BoxDecoration(
            color: Colors.white.withOpacity(0.93),
            borderRadius: BorderRadius.circular(16),
          ),
          child: SingleChildScrollView(
            child: Column(
              children: [
                buildGameSection(
                  context,
                  label: 'Jeu classic',
                  children: [
                    buildLevelRow('Facile', [
                      buildButton(context, 'Facile 1J', 'CF1'),
                      buildButton(context, 'Facile 2J', 'CF2'),
                      buildButton(context, 'Facile 3J', 'CF3'),
                      buildButton(context, 'Facile 4J', 'CF4'),
                    ]),
                    buildLevelRow('Semi-pro', [
                      buildButton(context, 'Semi-pro 1J', 'CSP1'),
                      buildButton(context, 'Semi-pro 2J', 'CSP2'),
                      buildButton(context, 'Semi-pro 3J', 'CSP3'),
                      buildButton(context, 'Semi-pro 4J', 'CSP4'),
                    ]),
                    buildLevelRow('Pro', [
                      buildButton(context, 'Pro 1J', 'CP1'),
                      buildButton(context, 'Pro 2J', 'CP2'),
                      buildButton(context, 'Pro 3J', 'CP3'),
                      buildButton(context, 'Pro 4J', 'CP4'),
                    ]),
                    buildLevelRow('Champion', [
                      buildButton(context, 'Champion 1J', 'CC1'),
                      buildButton(context, 'Champion 2J', 'CC2'),
                      buildButton(context, 'Champion 3J', 'CC3'),
                      buildButton(context, 'Champion 4J', 'CC4'),
                    ]),
                    buildLevelRow('Légende', [
                      buildButton(context, 'Légende 1J', 'CL1'),
                      buildButton(context, 'Légende 2J', 'CL2'),
                      buildButton(context, 'Légende 3J', 'CL3'),
                      buildButton(context, 'Légende 4J', 'CL4'),
                    ]),
                  ],
                ),
                buildGameSection(
                  context,
                  label: 'Le Jeu',
                  children: [
                    buildWrapButtons(context, ['LJ1', 'LJ2', 'LJ3', 'LJ4'], ['LJ1', 'LJ2', 'LJ3', 'LJ4']),
                  ],
                ),
                buildGameSection(
                  context,
                  label: 'Mode Survi',
                  children: [
                    buildWrapButtons(context, ['MS1', 'MS2', 'MS3', 'MS4'], ['MS1', 'MS2', 'MS3', 'MS4']),
                  ],
                ),
                buildGameSection(
                  context,
                  label: 'Compétition',
                  children: [
                    buildWrapButtons(context, ['CPT1'], ['CPT1']),
                  ],
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }

  Widget buildGameSection(BuildContext context, {
    required String label,
    required List<Widget> children,
  }) {
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 10),
      child: Flex(
        direction: Axis.horizontal,
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Container(
            padding: const EdgeInsets.symmetric(vertical: 12, horizontal: 16),
            margin: const EdgeInsets.only(right: 12),
            decoration: BoxDecoration(
              color: Colors.black87,
              borderRadius: BorderRadius.circular(12),
            ),
            child: Text(
              label,
              style: const TextStyle(
                color: Colors.white,
                fontWeight: FontWeight.bold,
              ),
            ),
          ),
          Expanded(
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: children,
            ),
          )
        ],
      ),
    );
  }

  Widget buildLevelRow(String title, List<Widget> levels) {
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 6),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Text(title, style: const TextStyle(color: Colors.purple, fontWeight: FontWeight.bold)),
          const SizedBox(height: 4),
          Wrap(
            spacing: 8,
            runSpacing: 8,
            children: levels,
          ),
        ],
      ),
    );
  }

  Widget buildButton(BuildContext context, String label, String group) {
    return ElevatedButton(
      onPressed: () => _startGame(context, group),
      style: ElevatedButton.styleFrom(
        backgroundColor: Colors.blue,
        foregroundColor: Colors.white,
        padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 12),
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(24),
        ),
      ),
      child: Text(label),
    );
  }

  void _startGame(BuildContext context, String group) async {
    final ws = Provider.of<WebSocketService>(context, listen: false);
    final groupModel = Provider.of<GroupModel>(context, listen: false);

    // 1. Envoi du groupe à l'Arduino via ESP32
    ws.sendMessage(json.encode({
      'type': 'group_game',
      'message': group // Ex: "CF1"
    }));

    // 2. Sauvegarde du groupe sélectionné
    groupModel.setSelectedGroup(group);

    // 3. Redirection immédiate vers ScoresScreen
    Navigator.pushReplacement(
      context,
      MaterialPageRoute(builder: (_) => ScoresScreen()),
    );

    // 4. Forcer l'état initial (optionnel)
    ws.setGameState(GameState.waitingGroup);
  }

  Widget buildWrapButtons(BuildContext context, List<String> labels, List<String> groups) {
    return Wrap(
      spacing: 8,
      runSpacing: 8,
      children: List.generate(labels.length, (index) {
        return ElevatedButton(
          onPressed: () => _startGame(context, groups[index]),
          style: ElevatedButton.styleFrom(
            backgroundColor: Colors.blue,
            foregroundColor: Colors.white,
            padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 12),
            shape: RoundedRectangleBorder(
              borderRadius: BorderRadius.circular(24),
            ),
          ),
          child: Text(labels[index]),
        );
      }).toList(),
    );
  }
}
