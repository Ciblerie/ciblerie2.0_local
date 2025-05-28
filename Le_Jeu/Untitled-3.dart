import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../services/websocket_service.dart';
import '../services/theme_notifier.dart';
import 'classement_general_screen.dart';
import 'scores_screen.dart';
import 'stats_screen.dart';
import 'classement_screen.dart';
import 'pseudo_config_screen.dart'; // Nouvel écran ajouté

class HomeScreen extends StatefulWidget {
  const HomeScreen({super.key});

  @override
  State<HomeScreen> createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> with SingleTickerProviderStateMixin {
  late AnimationController _controller;
  late Animation<double> _fadeAnimation;
  late Animation<double> _scaleAnimation;

  @override
  void initState() {
    super.initState();
    _controller = AnimationController(
      vsync: this,
      duration: const Duration(milliseconds: 700),
    );

    _fadeAnimation = Tween<double>(begin: 0, end: 1).animate(
      CurvedAnimation(parent: _controller, curve: Curves.easeIn),
    );

    _scaleAnimation = Tween<double>(begin: 0.95, end: 1).animate(
      CurvedAnimation(parent: _controller, curve: Curves.easeOutBack),
    );

    _controller.forward();
  }

  @override
  void dispose() {
    _controller.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    final websocketService = Provider.of<WebSocketService>(context);
    final themeNotifier = Provider.of<ThemeNotifier>(context);
    final status = websocketService.status;

    Color wifiColor;
    IconData wifiIcon;
    String wifiLabel;

    switch (status) {
      case ConnectionStatus.connected:
        wifiColor = Colors.green;
        wifiIcon = Icons.wifi;
        wifiLabel = 'Connecté';
        break;
      case ConnectionStatus.connecting:
        wifiColor = Colors.blueGrey;
        wifiIcon = Icons.wifi_tethering;
        wifiLabel = 'Connexion...';
        break;
      case ConnectionStatus.disconnected:
      default:
        wifiColor = Colors.orange;
        wifiIcon = Icons.wifi_off;
        wifiLabel = 'Déconnecté';
        break;
    }

    return Scaffold(
      appBar: AppBar(
        title: const Row(
          children: [
            Icon(Icons.home),
            SizedBox(width: 8),
            Text('Accueil'),
          ],
        ),
        actions: [
          IconButton(
            icon: Icon(themeNotifier.isDarkMode ? Icons.dark_mode : Icons.light_mode),
            onPressed: () => themeNotifier.toggleTheme(),
          ),
        ],
      ),
      body: FadeTransition(
        opacity: _fadeAnimation,
        child: ScaleTransition(
          scale: _scaleAnimation,
          child: Padding(
            padding: const EdgeInsets.all(16.0),
            child: LayoutBuilder(
              builder: (context, constraints) {
                return Column(
                  children: [
                    Expanded(
                      child: Row(
                        children: [
                          _buildLargeButton(
                            context,
                            label: 'Scores',
                            icon: Icons.bar_chart,
                            gradient: const LinearGradient(
                              colors: [Colors.lightBlueAccent, Colors.blue],
                            ),
                            onTap: () {
                              Navigator.push(
                                context,
                                MaterialPageRoute(builder: (_) => const ScoresScreen()),
                              );
                            },
                          ),
                          const SizedBox(width: 16),
                          _buildLargeButton(
                            context,
                            label: 'Classement général',
                            icon: Icons.emoji_events,
                            gradient: const LinearGradient(
                              colors: [Colors.deepPurple, Colors.deepPurpleAccent],
                            ),
                            onTap: () {
                              Navigator.push(
                                context,
                                MaterialPageRoute(
                                  builder: (_) => const ClassementGeneralScreen(),
                                ),
                              );
                            },
                          ),
                        ],
                      ),
                    ),
                    const SizedBox(height: 16),
                    Expanded(
                      child: Row(
                        children: [
                          _buildLargeButton(
                            context,
                            label: 'Statistiques',
                            icon: Icons.show_chart,
                            gradient: const LinearGradient(
                              colors: [Colors.lightGreenAccent, Colors.green],
                            ),
                            onTap: () {
                              Navigator.push(
                                context,
                                MaterialPageRoute(builder: (_) => const StatsScreen()),
                              );
                            },
                          ),
                          const SizedBox(width: 16),
                          Expanded(
                            child: Column(
                              children: [
                                Expanded(
                                  child: Row(
                                    children: [
                                      _buildSmallButton(
                                        label: 'Classement',
                                        icon: Icons.emoji_events,
                                        gradient: const LinearGradient(
                                          colors: [Colors.orangeAccent, Colors.deepOrange],
                                        ),
                                        onTap: () {
                                          Navigator.push(
                                            context,
                                            MaterialPageRoute(
                                              builder: (_) => ClassementScreen(
                                                finalScores: [0, 0, 0, 0],
                                              ),
                                            ),
                                          );
                                        },
                                      ),
                                      const SizedBox(width: 8),
                                      _buildSmallButton(
                                        label: wifiLabel,
                                        icon: wifiIcon,
                                        gradient: LinearGradient(
                                          colors: [wifiColor.withOpacity(0.7), wifiColor],
                                        ),
                                        onTap: () {
                                          if (status == ConnectionStatus.connected) {
                                            websocketService.disconnect();
                                          } else {
                                            websocketService.connect();
                                          }
                                        },
                                      ),
                                    ],
                                  ),
                                ),
                                const SizedBox(height: 8),
                                Expanded(
                                  child: Row(
                                    children: [
                                      _buildSmallButton(
                                        label: 'Pseudos',
                                        icon: Icons.person,
                                        gradient: const LinearGradient(
                                          colors: [Colors.purpleAccent, Colors.deepPurple],
                                        ),
                                        onTap: () {
                                          Navigator.push(
                                            context,
                                            MaterialPageRoute(
                                              builder: (_) => PseudoConfigScreen(),
                                            ),
                                          );
                                        },
                                      ),
                                      const SizedBox(width: 8),
                                      _buildSmallButton(
                                        label: 'Configuration',
                                        icon: Icons.settings,
                                        gradient: const LinearGradient(
                                          colors: [Colors.grey, Colors.blueGrey],
                                        ),
                                        onTap: () {
                                          _showIPDialog(context, websocketService);
                                        },
                                      ),
                                    ],
                                  ),
                                ),
                              ],
                            ),
                          ),
                        ],
                      ),
                    ),
                  ],
                );
              },
            ),
          ),
        ),
      ),
    );
  }

  Widget _buildLargeButton(
    BuildContext context, {
    required String label,
    required IconData icon,
    required Gradient gradient,
    required VoidCallback onTap,
  }) {
    return Expanded(
      child: GestureDetector(
        onTap: onTap,
        child: Container(
          margin: const EdgeInsets.symmetric(vertical: 4),
          decoration: BoxDecoration(
            gradient: gradient,
            borderRadius: BorderRadius.circular(16),
            boxShadow: [
              BoxShadow(
                color: Colors.black.withOpacity(0.1),
                blurRadius: 6,
                offset: const Offset(0, 3),
              ),
            ],
          ),
          child: Center(
            child: Column(
              mainAxisSize: MainAxisSize.min,
              children: [
                Icon(icon, size: 36, color: Colors.white),
                const SizedBox(height: 8),
                Text(
                  label,
                  style: const TextStyle(
                    fontSize: 18,
                    fontWeight: FontWeight.bold,
                    color: Colors.white,
                  ),
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }

  Widget _buildSmallButton({
    required String label,
    required IconData icon,
    required Gradient gradient,
    required VoidCallback onTap,
  }) {
    return Expanded(
      child: GestureDetector(
        onTap: onTap,
        child: Container(
          decoration: BoxDecoration(
            gradient: gradient,
            borderRadius: BorderRadius.circular(12),
            boxShadow: [
              BoxShadow(
                color: Colors.black.withOpacity(0.1),
                blurRadius: 4,
                offset: const Offset(0, 2),
              ),
            ],
          ),
          child: Center(
            child: Column(
              mainAxisSize: MainAxisSize.min,
              children: [
                Icon(icon, size: 24, color: Colors.white),
                const SizedBox(height: 4),
                Text(
                  label,
                  style: const TextStyle(
                    fontWeight: FontWeight.bold,
                    color: Colors.white,
                  ),
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }

  void _showIPDialog(BuildContext context, WebSocketService websocketService) {
    final ipController = TextEditingController(text: websocketService.serverIp);

    showDialog(
      context: context,
      builder: (context) {
        return AlertDialog(
          title: const Text('Configuration IP'),
          content: TextField(
            controller: ipController,
            decoration: const InputDecoration(
              labelText: 'Adresse IP du serveur',
              hintText: '192.168.1.100:81',
              border: OutlineInputBorder(),
            ),
          ),
          actions: [
            TextButton(
              onPressed: () => Navigator.of(context).pop(),
              child: const Text('Annuler'),
            ),
            ElevatedButton(
              onPressed: () {
                websocketService.setServerIp(ipController.text);
                websocketService.connect();
                Navigator.of(context).pop();
              },
              child: const Text('Enregistrer'),
            ),
          ],
        );
      },
    );
  }
}