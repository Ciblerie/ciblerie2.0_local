import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../services/websocket_service.dart';

class PseudoConfigScreen extends StatefulWidget {
  @override
  _PseudoConfigScreenState createState() => _PseudoConfigScreenState();
}

class _PseudoConfigScreenState extends State<PseudoConfigScreen> {
  final List<TextEditingController> _controllers = List.generate(4, (_) => TextEditingController());

  @override
  void initState() {
    super.initState();
    final ws = Provider.of<WebSocketService>(context, listen: false);
    _controllers[0].text = ws.pseudonymsNotifier.value[0] ?? 'J1';
    _controllers[1].text = ws.pseudonymsNotifier.value[1] ?? 'J2';
    _controllers[2].text = ws.pseudonymsNotifier.value[2] ?? 'J3';
    _controllers[3].text = ws.pseudonymsNotifier.value[3] ?? 'J4';
  }

  @override
  Widget build(BuildContext context) {
    final ws = Provider.of<WebSocketService>(context);

    return Scaffold(
      appBar: AppBar(title: Text('Configuration des Pseudos')),
      body: Padding(
        padding: EdgeInsets.all(20),
        child: Column(
          children: [
            for (int i = 0; i < 4; i++)
              Padding(
                padding: EdgeInsets.only(bottom: 15),
                child: TextField(
                  controller: _controllers[i],
                  decoration: InputDecoration(
                    labelText: 'Joueur ${i+1}',
                    border: OutlineInputBorder(),
                  ),
                ),
              ),
            ElevatedButton(
              style: ElevatedButton.styleFrom(
                minimumSize: Size(double.infinity, 50),
              ),
              onPressed: () {
                final pseudos = {
                  0: _controllers[0].text.isNotEmpty ? _controllers[0].text : 'J1',
                  1: _controllers[1].text.isNotEmpty ? _controllers[1].text : 'J2',
                  2: _controllers[2].text.isNotEmpty ? _controllers[2].text : 'J3',
                  3: _controllers[3].text.isNotEmpty ? _controllers[3].text : 'J4',
                };
                ws.setPseudonyms(pseudos);
                ws.startGame();
                Navigator.pop(context);
              },
              child: Text('Démarrer la Partie', style: TextStyle(fontSize: 18)),
            ),
          ],
        ),
      ),
    );
  }

  @override
  void dispose() {
    for (var controller in _controllers) {
      controller.dispose();
    }
    super.dispose();
  }
}
