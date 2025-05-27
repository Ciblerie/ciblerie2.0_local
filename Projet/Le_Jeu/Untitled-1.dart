import 'dart:async';
import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:shared_preferences/shared_preferences.dart';
import 'package:web_socket_channel/web_socket_channel.dart';
import 'package:web_socket_channel/status.dart' as ws_status;

enum ConnectionStatus {
  connected,
  disconnected,
  connecting,
}

enum GameState {
  idle,
  config,  // Nouvel état pour la configuration des pseudos
  started,
  finished,
}

class WebSocketService with ChangeNotifier {
  WebSocketChannel? _channel;
  final StreamController<String> _messageController = StreamController.broadcast();

  // Scores et données existantes
  final ValueNotifier<Map<int, int>> scoresNotifier = ValueNotifier({
    0: 0,
    1: 0,
    2: 0,
    3: 0,
  });

  // Nouveau: Gestion des pseudonymes
  final ValueNotifier<Map<int, String>> pseudonymsNotifier = ValueNotifier({
    0: 'J1',
    1: 'J2',
    2: 'J3',
    3: 'J4',
  });

  final ValueNotifier<Map<int, Map<int, int>>> frequenciesNotifier = ValueNotifier({
    0: {5: 0, 10: 0, 15: 0, 25: 0, 50: 0},
    1: {5: 0, 10: 0, 15: 0, 25: 0, 50: 0},
    2: {5: 0, 10: 0, 15: 0, 25: 0, 50: 0},
    3: {5: 0, 10: 0, 15: 0, 25: 0, 50: 0},
  });

  final ValueNotifier<List<int>?> lastFinalScores = ValueNotifier(null);
  final ValueNotifier<bool> showSaveButton = ValueNotifier(false);
  final ValueNotifier<String> groupNotifier = ValueNotifier("A");

  ConnectionStatus _connectionStatus = ConnectionStatus.disconnected;
  String _serverIp = '';
  Timer? _reconnectTimer;

  GameState _gameState = GameState.idle;
  GameState get gameState => _gameState;

  String _group = "A";
  String get group => _group;

  WebSocketService() {
    _loadSavedIP();
  }

  Future<void> _loadSavedIP() async {
    final prefs = await SharedPreferences.getInstance();
    _serverIp = prefs.getString('server_ip') ?? '';
    notifyListeners();
  }

  Future<void> setServerIp(String ip) async {
    if (!_validateIp(ip)) {
      debugPrint('IP invalide : $ip');
      return;
    }

    _serverIp = ip;
    final prefs = await SharedPreferences.getInstance();
    await prefs.setString('server_ip', ip);
    notifyListeners();
  }

  void connect() {
    if (_serverIp.isEmpty) {
      debugPrint("IP serveur manquante.");
      return;
    }

    final uri = Uri.parse('ws://$_serverIp');
    _updateStatus(ConnectionStatus.connecting);

    try {
      _channel = WebSocketChannel.connect(uri);
      debugPrint("Connexion WebSocket établie à $uri");

      _channel!.stream.listen(
        (data) {
          debugPrint("Message reçu : $data");
          _messageController.add(data);
          _handleIncomingMessage(data);
        },
        onDone: _handleDisconnection,
        onError: (error) {
          debugPrint("Erreur WebSocket : $error");
          _handleDisconnection();
        },
        cancelOnError: true,
      );

      _updateStatus(ConnectionStatus.connected);
      _cancelReconnectTimer();
    } catch (e) {
      debugPrint("Exception à la connexion WebSocket : $e");
      _handleDisconnection();
    }
  }

  void disconnect() {
    _channel?.sink.close(ws_status.normalClosure);
    _channel = null;
    _updateStatus(ConnectionStatus.disconnected);
    _cancelReconnectTimer();
  }

  void _handleDisconnection() {
    debugPrint("WebSocket déconnectée.");
    _channel = null;
    _updateStatus(ConnectionStatus.disconnected);
    _startReconnectTimer();
  }

  void _startReconnectTimer() {
    if (_reconnectTimer?.isActive ?? false) return;

    _reconnectTimer = Timer.periodic(const Duration(seconds: 5), (_) {
      if (_connectionStatus == ConnectionStatus.disconnected && _serverIp.isNotEmpty) {
        debugPrint("Tentative de reconnexion WebSocket...");
        connect();
      }
    });
  }

  void _cancelReconnectTimer() {
    _reconnectTimer?.cancel();
    _reconnectTimer = null;
  }

  void _updateStatus(ConnectionStatus newStatus) {
    _connectionStatus = newStatus;
    notifyListeners();
  }

  bool _validateIp(String ip) {
    final regex = RegExp(r'^(\d{1,3}\.){3}\d{1,3}(:\d+)?$');
    return regex.hasMatch(ip);
  }

  // Nouvelle méthode pour définir les pseudos
  void setPseudonyms(Map<int, String> pseudonyms) {
    pseudonymsNotifier.value = Map<int, String>.from(pseudonyms);
    notifyListeners();
  }

  // Nouvelle méthode pour démarrer le jeu
  void startGame() {
    sendMessage('{"type": "start_game"}');
    setGameState(GameState.started);
  }

  void _handleIncomingMessage(String data) {
    try {
      final decoded = jsonDecode(data);
      if (decoded is! Map<String, dynamic>) return;

      final type = decoded['type'];
      if (type == 'config_pseudos') {
        setGameState(GameState.config);
      } else if (type == 'start') {
        resetAllScores();
        resetFrequencies();
        setGameState(GameState.started);
        showSaveButton.value = false;
      } else if (type == 'fin') {
        setGameState(GameState.finished);
        showSaveButton.value = true;
      } else if (type == 'groupe') {
        _group = decoded["value"];
        groupNotifier.value = _group;
        notifyListeners();
      }

      if (_gameState != GameState.started) return;

      if (decoded.containsKey("playerIndex") && decoded.containsKey("score")) {
        final int index = decoded["playerIndex"];
        final int score = decoded["score"];

        scoresNotifier.value = {
          ...scoresNotifier.value,
          index: score,
        };
      }

      if (decoded.containsKey("playerIndex") && decoded.containsKey("point")) {
        final int index = decoded["playerIndex"];
        final int point = decoded["point"];

        final current = Map<int, Map<int, int>>.from(frequenciesNotifier.value);
        final playerFreq = Map<int, int>.from(current[index] ?? {});
        playerFreq[point] = (playerFreq[point] ?? 0) + 1;
        current[index] = playerFreq;
        frequenciesNotifier.value = current;
      }
    } catch (e) {
      debugPrint("Erreur WebSocket : $e");
    }
  }

  void sendMessage(String message) {
    if (_channel != null && _connectionStatus == ConnectionStatus.connected) {
      try {
        _channel!.sink.add(message);
      } catch (e) {
        debugPrint("Erreur à l'envoi du message : $e");
      }
    } else {
      debugPrint("Impossible d'envoyer le message : WebSocket non connectée.");
    }
  }

  void resetAllScores() {
    scoresNotifier.value = {
      0: 0,
      1: 0,
      2: 0,
      3: 0,
    };
    scoresNotifier.notifyListeners();
  }

  void resetFrequencies() {
    frequenciesNotifier.value = {
      0: {5: 0, 10: 0, 15: 0, 25: 0, 50: 0},
      1: {5: 0, 10: 0, 15: 0, 25: 0, 50: 0},
      2: {5: 0, 10: 0, 15: 0, 25: 0, 50: 0},
      3: {5: 0, 10: 0, 15: 0, 25: 0, 50: 0},
    };
  }

  void setGameState(GameState state) {
    _gameState = state;
    notifyListeners();
  }

  void clearFinalScores() {
    lastFinalScores.value = null;
  }

  Stream<String> get messages => _messageController.stream;
  ConnectionStatus get status => _connectionStatus;
  String get serverIp => _serverIp;

  @override
  void dispose() {
    disconnect();
    _messageController.close();
    scoresNotifier.dispose();
    pseudonymsNotifier.dispose();
    frequenciesNotifier.dispose();
    lastFinalScores.dispose();
    showSaveButton.dispose();
    groupNotifier.dispose();
    super.dispose();
  }
}