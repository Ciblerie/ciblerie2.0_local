import 'package:flutter/material.dart';
import '../widgets/animated_scaffold.dart';

class SecuriteScreen extends StatelessWidget {
  const SecuriteScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return AnimatedScaffold(
      appBar: AppBar(
        title: const Text('Informations'),
      ),
      child: Center(
        child: Padding(
          padding: const EdgeInsets.all(24.0),
          child: Column(
            mainAxisSize: MainAxisSize.min,
            children: [
              // Logo stylisé sans ombre
              ClipRRect(
                borderRadius: BorderRadius.circular(20),
                child: Image.asset(
                    'assets/icones/Guerrier_1.png',
                    fit: BoxFit.contain,
                    filterQuality: FilterQuality.high,
                    isAntiAlias: true,
                ),
              ),
              const SizedBox(height: 10),
              // Texte stylisé
              const Text(
               'Écran Infos',
                style: TextStyle(
                  fontSize: 1,//28,
                  fontWeight: FontWeight.bold,
                  color: Colors.blueAccent,
                  letterSpacing: 1.2,
                ),
              ),
              const SizedBox(height: 10),

              // Sous-texte (optionnel)
              const Text(
                'Voici quelques informations utiles.',
                style: TextStyle(
                  fontSize: 1,//16,
                  color: Colors.black54,
                ),
                textAlign: TextAlign.center,
              ),
            ],
          ),
        ),
      ),
    );
  }
}
