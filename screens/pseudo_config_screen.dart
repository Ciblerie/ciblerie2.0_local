import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../services/websocket_service.dart';
import '../widgets/animated_scaffold.dart'; // import du widget reusable

class PseudoConfigScreen extends StatefulWidget {
  const PseudoConfigScreen({Key? key}) : super(key: key);

  @override
  _PseudoConfigScreenState createState() => _PseudoConfigScreenState();
}

class _PseudoConfigScreenState extends State<PseudoConfigScreen> with TickerProviderStateMixin {
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

    return AnimatedScaffold(
      appBar: AppBar(
        title: const Text('Configuration des Pseudos'),
        centerTitle: true,
      ),
      child: Padding(  // <-- ici 'child' au lieu de 'body'
        padding: const EdgeInsets.all(20.0),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.spaceBetween,
          children: [
            Expanded(
              child: ListView.builder(
                itemCount: 4,
                itemBuilder: (context, i) {
                  return Padding(
                    padding: const EdgeInsets.only(bottom: 15.0),
                    child: TextField(
                      controller: _controllers[i],
                      decoration: InputDecoration(
                        labelText: 'Joueur ${i + 1}',
                        border: const OutlineInputBorder(),
                      ),
                    ),
                  );
                },
              ),
            ),
            ElevatedButton(
              style: ElevatedButton.styleFrom(
                minimumSize: const Size(double.infinity, 50),
                backgroundColor: const Color(0xFF7DBFF8),
              ),
              onPressed: () {
                final pseudos = {
                  0: _controllers[0].text.isNotEmpty ? _controllers[0].text : 'J1',
                  1: _controllers[1].text.isNotEmpty ? _controllers[1].text : 'J2',
                  2: _controllers[2].text.isNotEmpty ? _controllers[2].text : 'J3',
                  3: _controllers[3].text.isNotEmpty ? _controllers[3].text : 'J4',
                };
                ws.setPseudonyms(pseudos);
                Navigator.pushReplacementNamed(context, '/scores');
              },
              child: const Text(
                'Valider les pseudos',
                style: TextStyle(fontWeight: FontWeight.bold, color: Colors.black),
              ),
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
