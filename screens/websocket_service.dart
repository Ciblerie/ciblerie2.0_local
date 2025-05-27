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
  config,
  started,
  finished,
}

class WebSocketService with ChangeNotifier {
  WebSocketChannel? _channel;
  final StreamController<String> _messageController = StreamController.broadcast();
  final ValueNotifier<Map<int, int>> scoresNotifier = ValueNotifier({0: 0, 1: 0, 2: 0, 3: 0});
  final ValueNotifier<Map<int, Map<int, int>>> frequenciesNotifier = ValueNotifier({
    0: {0: 0, 5: 0, 10: 0, 15: 0, 25: 0, 50: 0, 100: 0, 150: 0, 200: 0, 250: 0},
    1: {0: 0, 5: 0, 10: 0, 15: 0, 25: 0, 50: 0, 100: 0, 150: 0, 200: 0, 250: 0},
    2: {0: 0, 5: 0, 10: 0, 15: 0, 25: 0, 50: 0, 100: 0, 150: 0, 200: 0, 250: 0},
    3: {0: 0, 5: 0, 10: 0, 15: 0, 25: 0, 50: 0, 100: 0, 150: 0, 200: 0, 250: 0},
  });
  final ValueNotifier<String> groupNotifier = ValueNotifier('-');
  final ValueNotifier<Map<int, String>> pseudonymsNotifier = ValueNotifier({0: 'J1', 1: 'J2', 2: 'J3', 3: 'J4'});
  final ValueNotifier<GameState> gameStateNotifier = ValueNotifier(GameState.idle);
  final ValueNotifier<List<int>?> lastFinalScores = ValueNotifier(null);
  final ValueNotifier<bool> showSaveButton = ValueNotifier(false);

  ConnectionStatus _connectionStatus = ConnectionStatus.disconnected;
  String _serverIp = '';
  Timer? _reconnectTimer;

  WebSocketService() {
    // Initialisation sans argument
  }

  void connect(String url) {
    if (url.isEmpty) {
      debugPrint("URL serveur manquante.");
      return;
    }

    final uri = Uri.parse(url);
    _updateStatus(ConnectionStatus.connecting);

    try {
      _channel = WebSocketChannel.connect(uri);
      debugPrint("Connexion WebSocket établie à $uri");

      _channel!.stream.listen(
            (data) {
          _messageController.add(data);
          _handleIncomingMessage(data);
        },
        onDone: _handleDisconnection,
        onError: (error) {
          print('Erreur WebSocket : $error');
          _handleDisconnection();
        },
        cancelOnError: true,
      );

      _updateStatus(ConnectionStatus.connected);
      _cancelReconnectTimer();
    } catch (e) {
      print('Exception à la connexion WebSocket : $e');
      _handleDisconnection();
    }
  }

  void _handleDisconnection() {
    print('WebSocket déconnectée.');
    _channel = null;
    _updateStatus(ConnectionStatus.disconnected);
    _startReconnectTimer();
  }

  void _startReconnectTimer() {
    if (_reconnectTimer?.isActive ?? false) return;

    _reconnectTimer = Timer.periodic(const Duration(seconds: 5), (_) {
      if (_connectionStatus == ConnectionStatus.disconnected && _serverIp.isNotEmpty) {
        debugPrint("Tentative de reconnexion WebSocket...");
        connect(_serverIp);
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

  void setPseudonyms(Map<int, String> pseudonyms) {
    pseudonymsNotifier.value = Map<int, String>.from(pseudonyms);
    notifyListeners();
  }

  void setGameState(GameState state) {
    gameStateNotifier.value = state;
    notifyListeners();
  }

  void sendMessage(String message) {
    if (_channel != null) {
      try {
        _channel!.sink.add(message);
      } catch (e) {
        print('Erreur à l\'envoi du message : $e');
      }
    } else {
      print('Impossible d\'envoyer le message : WebSocket non connectée.');
    }
  }

  void _handleIncomingMessage(String data) {
    try {
      final decoded = jsonDecode(data);
      if (decoded is! Map<String, dynamic>) return;

      final type = decoded['type'];
      switch (type) {
        case 'config_pseudos':
          setGameState(GameState.config);
          break;
        case 'start_game':
          print('Message reçu start_game');
          break;
        case 'start_game_confirmed':
          break;
        case 'start':
          resetAllScores();
          resetFrequencies();
          setGameState(GameState.started);
          showSaveButton.value = false;
          break;
        case 'fin':
          setGameState(GameState.finished);
          showSaveButton.value = true;
          break;
        case 'groupe':
          groupNotifier.value = decoded["value"];
          break;
        case 'J1':
        case 'J2':
        case 'J3':
        case 'J4':
          final int index = int.parse(type.substring(1)) - 1;
          final int scores = decoded["scores"];
          final int points = decoded["points"];
          final int pointBonus = decoded["pointBonus"];

          scoresNotifier.value = {
            ...scoresNotifier.value,
            index: scores,
          };

          final current = Map<int, Map<int, int>>.from(frequenciesNotifier.value);
          final playerFreq = Map<int, int>.from(current[index] ?? {});
          playerFreq[points] = (playerFreq[points] ?? 0) + 1;
          current[index] = playerFreq;
          frequenciesNotifier.value = current;

          print('Message Jx reçu : Joueur $index, Scores $scores, Points $points, PointBonus $pointBonus');
          break;
        case 'next_player':
        // Gérer le passage au joueur suivant
          print('Message reçu next_player');
          break;
        case 'next_turn':
        // Gérer le passage au tour suivant
          print('Message reçu next_turn');
          break;
      }
    } catch (e) {
      print('Erreur de parsing JSON : $e');
    }
  }

  void resetAllScores() {
    scoresNotifier.value = {
      0: 0,
      1: 0,
      2: 0,
      3: 0,
    };
  }

  void resetFrequencies() {
    frequenciesNotifier.value = {
      0: {0: 0, 5: 0, 10: 0, 15: 0, 25: 0, 50: 0, 100: 0, 150: 0, 200: 0, 250: 0},
      1: {0: 0, 5: 0, 10: 0, 15: 0, 25: 0, 50: 0, 100: 0, 150: 0, 200: 0, 250: 0},
      2: {0: 0, 5: 0, 10: 0, 15: 0, 25: 0, 50: 0, 100: 0, 150: 0, 200: 0, 250: 0},
      3: {0: 0, 5: 0, 10: 0, 15: 0, 25: 0, 50: 0, 100: 0, 150: 0, 200: 0, 250: 0},
    };
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
    frequenciesNotifier.dispose();
    groupNotifier.dispose();
    pseudonymsNotifier.dispose();
    gameStateNotifier.dispose();
    lastFinalScores.dispose();
    showSaveButton.dispose();
    super.dispose();
  }

  void disconnect() {
    _channel?.sink.close(ws_status.normalClosure);
    _channel = null;
    _updateStatus(ConnectionStatus.disconnected);
    _cancelReconnectTimer();
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

  bool _validateIp(String ip) {
    final regex = RegExp(r'^\d{1,3}(\.\d{1,3}){3}(:\d+)?$');
    return regex.hasMatch(ip);
  }
}
