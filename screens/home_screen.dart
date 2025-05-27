import 'dart:html' as html; // Import spécifique pour le web
import 'package:flutter/foundation.dart'; // Import pour kIsWeb
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:provider/provider.dart';
import '../services/websocket_service.dart';
import '../services/theme_notifier.dart';
import 'classement_general_screen.dart';
import 'scores_screen.dart';
import 'stats_screen.dart';
import 'classement_screen.dart';
import 'pseudo_config_screen.dart';
import 'infos_screen.dart';
import 'securite_screen.dart';
import 'dev_screen.dart';
import 'package:shared_preferences/shared_preferences.dart';

class HomeScreen extends StatefulWidget {
  const HomeScreen({super.key});

  @override
  State<HomeScreen> createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen>
    with SingleTickerProviderStateMixin {
  late AnimationController _controller;
  late Animation<double> _fadeAnimation;
  late Animation<double> _scaleAnimation;
  bool _isFullscreen = false; // Etat du plein écran

  @override
  void initState() {
    super.initState();
    // Activer le mode plein écran initial sur mobile
    _setInitialFullscreen();

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

  // Gestion initiale du plein écran (mobile)
  void _setInitialFullscreen() {
    if (!kIsWeb) { // Utilisation de kIsWeb
      SystemChrome.setEnabledSystemUIMode(SystemUiMode.immersiveSticky);
      _isFullscreen = true;
    }
  }

  @override
  void dispose() {
    _controller.dispose();
    // Restaurer les barres système en quittant (mobile)
    if (!kIsWeb) { // Utilisation de kIsWeb
      SystemChrome.setEnabledSystemUIMode(SystemUiMode.edgeToEdge);
    }
    super.dispose();
  }

  // Fonction pour basculer le plein écran
  void _toggleFullscreen() {
    setState(() {
      _isFullscreen = !_isFullscreen;
    });

    if (kIsWeb) { // Utilisation de kIsWeb
      // Gérer le plein écran sur le web
      if (_isFullscreen) {
        html.document.documentElement?.requestFullscreen();
      } else {
        html.document.exitFullscreen();
      }
    } else {
      // Gérer le plein écran sur mobile (Android, iOS)
      if (_isFullscreen) {
        SystemChrome.setEnabledSystemUIMode(SystemUiMode.immersiveSticky);
      } else {
        SystemChrome.setEnabledSystemUIMode(SystemUiMode.edgeToEdge);
      }
    }
  }

  @override
  Widget build(BuildContext context) {
    final websocketService = Provider.of<WebSocketService>(context);
    final themeNotifier = Provider.of<ThemeNotifier>(context);
    final status = websocketService.status;

    // Configuration des icônes WiFi
    final wifiConfig = _getWifiConfig(status);

    return Scaffold(
      extendBodyBehindAppBar: true,
      appBar: AppBar(
        backgroundColor: Colors.transparent,
        elevation: 0,
        title: const Row(
          children: [
            Icon(Icons.home, color: Colors.white),
            SizedBox(width: 8),
            Text('Accueil', style: TextStyle(color: Colors.white)),
          ],
        ),
        actions: [
          IconButton(
            icon: Icon(
              themeNotifier.isDarkMode ? Icons.dark_mode : Icons.light_mode,
              color: Colors.white,
            ),
            onPressed: () => themeNotifier.toggleTheme(),
          ),
          // Bouton plein écran
          IconButton(
            icon: Icon(
              _isFullscreen ? Icons.fullscreen_exit : Icons.fullscreen,
              color: Colors.white,
            ),
            onPressed: _toggleFullscreen,
          ),
        ],
      ),
      body: Container(
        decoration: BoxDecoration(
          gradient: LinearGradient(
            begin: Alignment.topCenter,
            end: Alignment.bottomCenter,
            colors: [
              Theme.of(context).primaryColor,
              Theme.of(context).primaryColorDark,
            ],
          ),
        ),
        child: FadeTransition(
          opacity: _fadeAnimation,
          child: ScaleTransition(
            scale: _scaleAnimation,
            child: SafeArea(
              top: false,
              bottom: false,
              child: Padding(
                padding: const EdgeInsets.all(8.0),
                child: LayoutBuilder(
                  builder: (context, constraints) {
                    return Column(
                      children: [
                        // Première ligne de boutons (grands)
                        Expanded(
                          child: Row(
                            children: [
                              _buildLargeButton(
                                context,
                                label: 'Scores',
                                icon: Icons.bar_chart,
                                colors: [Colors.lightBlueAccent, Colors.blue],
                                onTap: () =>
                                    _navigateTo(context, const ScoresScreen()),
                              ),
                              const SizedBox(width: 8),
                              _buildLargeButton(
                                context,
                                label: 'Classement général',
                                icon: Icons.emoji_events,
                                colors: [
                                  Colors.deepPurple,
                                  Colors.deepPurpleAccent
                                ],
                                onTap: () =>
                                    _navigateTo(
                                        context, const ClassementGeneralScreen()),
                              ),
                            ],
                          ),
                        ),
                        const SizedBox(height: 8),
                        // Deuxième ligne de boutons (grands)
                        Expanded(
                          child: Row(
                            children: [
                              _buildLargeButton(
                                context,
                                label: 'Statistiques',
                                icon: Icons.show_chart,
                                colors: [Colors.lightGreenAccent, Colors.green],
                                onTap: () =>
                                    _navigateTo(context, const StatsScreen()),
                              ),
                              const SizedBox(width: 8),
                              // Colonne de petits boutons
                              Expanded(
                                child: Column(
                                  children: [
                                    // Première ligne de petits boutons
                                    Expanded(
                                      child: Row(
                                        children: [
                                          _buildSmallButton(
                                            label: 'Dev',
                                            icon: Icons.code,
                                            colors: [
                                              Colors.indigoAccent,
                                              Colors.indigo
                                            ],
                                            onTap: () =>
                                                _navigateTo(
                                                    context,
                                                    const DevScreen()),
                                          ),
                                          const SizedBox(width: 8),
                                          _buildSmallButton(
                                            label: 'Infos',
                                            icon: Icons.info,
                                            colors: [
                                              Colors.tealAccent,
                                              Colors.teal
                                            ],
                                            onTap: () =>
                                                _navigateTo(
                                                    context,
                                                    const InfosScreen()),
                                          ),
                                        ],
                                      ),
                                    ),
                                    const SizedBox(height: 8),
                                    // Deuxième ligne de petits boutons améliorée en 2x2
                                    Expanded(
                                      child: Row(
                                        children: [
                                          _buildSmallButton(
                                            label: 'Pseudos',
                                            icon: Icons.person,
                                            colors: [
                                              Colors.purpleAccent,
                                              Colors.deepPurple
                                            ],
                                            onTap: () =>
                                                _navigateTo(
                                                    context,
                                                    PseudoConfigScreen()),
                                          ),
                                          const SizedBox(width: 8),
                                          // Zone de 4 mini-tuiles (2x2)
                                          Expanded(
                                            child: Column(
                                              children: [
                                                Expanded(
                                                  child: Row(
                                                    children: [
                                                      _buildTinyButton(
                                                        label: 'Sécurité',
                                                        icon: Icons.lock,
                                                        colors: [
                                                          Colors.pinkAccent,
                                                          Colors.pink
                                                        ],
                                                        onTap: () =>
                                                            _navigateTo(
                                                                context,
                                                                const SecuriteScreen()),
                                                      ),
                                                      const SizedBox(width: 4),
                                                      // Utilisez _buildTinyButton pour le bouton de connexion
                                                      _buildTinyButton(
                                                        label: wifiConfig.label,
                                                        icon: wifiConfig.icon,
                                                        colors: [
                                                          wifiConfig.color.withOpacity(0.7),
                                                          wifiConfig.color
                                                        ],
                                                        onTap: () =>
                                                            _toggleConnection(
                                                                websocketService,
                                                                status),
                                                      ),
                                                    ],
                                                  ),
                                                ),
                                                const SizedBox(height: 4),
                                                Expanded(
                                                  child: Row(
                                                    children: [
                                                      _buildTinyButton(
                                                        label: 'Classement',
                                                        icon: Icons.emoji_events,
                                                        colors: [
                                                          Colors.orangeAccent,
                                                          Colors.deepOrange
                                                        ],
                                                        onTap: () =>
                                                            _navigateTo(
                                                              context,
                                                              ClassementScreen(
                                                                  finalScores: [
                                                                    0,
                                                                    0,
                                                                    0,
                                                                    0
                                                                  ]),
                                                            ),
                                                      ),
                                                      const SizedBox(width: 4),
                                                      _buildTinyButton(
                                                        label: 'Config',
                                                        icon: Icons.settings,
                                                        colors: [
                                                          Colors.grey,
                                                          Colors.blueGrey
                                                        ],
                                                        onTap: () =>
                                                            _showIPDialog(
                                                                context,
                                                                websocketService),
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
        ),
      ),
    );
  }

  _WifiConfig _getWifiConfig(ConnectionStatus status) {
    switch (status) {
      case ConnectionStatus.connected:
        return _WifiConfig(Colors.green, Icons.wifi, 'Déconnecter');
      case ConnectionStatus.connecting:
        return _WifiConfig(Colors.blueGrey, Icons.wifi_tethering, 'Connexion...');
      case ConnectionStatus.disconnected:
      default:
        return _WifiConfig(Colors.orange, Icons.wifi_off, 'Connecter');
    }
  }

  void _toggleConnection(WebSocketService service, ConnectionStatus status) async {
    if (status == ConnectionStatus.connected) {
      service.disconnect();
    } else {
      // Récupérer l'adresse IP stockée
      final prefs = await SharedPreferences.getInstance();
      final serverIp = prefs.getString('server_ip') ?? 'ws://votre-ip-serveur:port'; // Remplacez par l'URL de votre serveur WebSocket

      // Connecter avec l'adresse IP stockée
      service.connect(serverIp);
    }
  }

  void _navigateTo(BuildContext context, Widget screen) {
    Navigator.push(context, MaterialPageRoute(builder: (_) => screen));
  }

  Widget _buildLargeButton(
      BuildContext context, {
        required String label,
        required IconData icon,
        required List<Color> colors,
        required VoidCallback onTap,
      }) {
    return Expanded(
      child: GestureDetector(
        onTap: onTap,
        child: Container(
          margin: const EdgeInsets.symmetric(vertical: 4),
          decoration: BoxDecoration(
            gradient: LinearGradient(colors: colors),
            borderRadius: BorderRadius.circular(16),
            boxShadow: [
              BoxShadow(
                color: Colors.black.withOpacity(0.2),
                blurRadius: 8,
                offset: const Offset(0, 4),
              ),
            ],
          ),
          child: Material(
            color: Colors.transparent,
            child: InkWell(
              borderRadius: BorderRadius.circular(16),
              onTap: onTap,
              child: Center(
                child: Column(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    Icon(icon, size: 36, color: Colors.white),
                    const SizedBox(height: 8),
                    Text(
                      label,
                      textAlign: TextAlign.center,
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
        ),
      ),
    );
  }

  Widget _buildSmallButton({
    required String label,
    required IconData icon,
    required List<Color> colors,
    required VoidCallback onTap,
  }) {
    return Expanded(
      child: Container(
        margin: const EdgeInsets.all(2),
        child: Material(
          borderRadius: BorderRadius.circular(12),
          child: InkWell(
            borderRadius: BorderRadius.circular(12),
            onTap: onTap,
            child: Container(
              decoration: BoxDecoration(
                gradient: LinearGradient(colors: colors),
                borderRadius: BorderRadius.circular(12),
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
                        fontSize: 12,
                        fontWeight: FontWeight.bold,
                        color: Colors.white,
                      ),
                    ),
                  ],
                ),
              ),
            ),
          ),
        ),
      ),
    );
  }

  Widget _buildTinyButton({
    required String label,
    required IconData icon,
    required List<Color> colors,
    required VoidCallback onTap,
  }) {
    return Expanded(
      child: GestureDetector(
        onTap: onTap,
        child: Container(
          margin: EdgeInsets.zero,
          decoration: BoxDecoration(
            borderRadius: BorderRadius.circular(12),
            gradient: LinearGradient(
              begin: Alignment.topLeft,
              end: Alignment.bottomRight,
              colors: colors,
            ),
          ),
          child: Center(
            child: Column(
              mainAxisSize: MainAxisSize.min,
              children: [
                Icon(icon, color: Colors.white),
                const SizedBox(height: 4),
                Text(
                  label,
                  style: const TextStyle(
                      fontSize: 8,
                      fontWeight: FontWeight.bold,
                      color: Colors.white ),
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }

  void _showIPDialog(BuildContext context, WebSocketService service) async {
    final prefs = await SharedPreferences.getInstance();
    final savedIp = prefs.getString('server_ip') ?? '';
    final ipController = TextEditingController(text: savedIp);

    showDialog(
      context: context,
      builder: (context) => AlertDialog(
        title: const Text('Configuration IP'),
        content: TextField(
          controller: ipController,
          decoration: const InputDecoration(
            labelText: 'Adresse IP du serveur',
            border: OutlineInputBorder(),
          ),
        ),
        actions: [
          TextButton(
            onPressed: () => Navigator.pop(context),
            child: const Text('Annuler'),
          ),
          ElevatedButton(
            onPressed: () async {
              final serverIp = 'ws://${ipController.text}'; // Remplacez par l'URL de votre serveur WebSocket
              await prefs.setString('server_ip', ipController.text); // Sauvegarder l'adresse IP
              service.setServerIp(ipController.text);
              service.connect(serverIp);
              Navigator.pop(context);
            },
            child: const Text('Connecter'),
          ),
        ],
      ),
    );
  }
}

class _WifiConfig {
  final Color color;
  final IconData icon;
  final String label;

  _WifiConfig(this.color, this.icon, this.label);
}
