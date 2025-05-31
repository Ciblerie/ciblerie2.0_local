
#include <WiFi.h>
#include <WebSocketsServer.h>
#include <BluetoothSerial.h>
#include <ArduinoJson.h>

// === Configuration WiFi (modifiable via Bluetooth) ===
String ssid = "Livebox-9410";
String password = "37322944";

// === Déclaration des objets ===
WebSocketsServer webSocket = WebSocketsServer(81);
BluetoothSerial SerialBT;

// === Gestion Ping/Timeout WebSocket ===
unsigned long lastPingTime = 0;
const unsigned long PING_INTERVAL = 30000;
const unsigned long CLIENT_TIMEOUT = 60000;
unsigned long lastPongTimes[WEBSOCKETS_SERVER_CLIENT_MAX] = {0};

// === Gestion Jeu ===
enum GameState { IDLE, WAITING_CONFIRMATION, GAME_STARTED };
GameState currentGameState = IDLE;
unsigned long lastSerialActivity = 0;

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 16, 17);
  Serial.println("🔗 Liaison série avec Arduino Méga initialisée.");

  // === VOTRE PARTIE BLUETOOTH EXACTEMENT COMME VOUS L'AVEZ ===
  SerialBT.begin("🖥️ ESP32_BT_Config");
  Serial.println("📡 Bluetooth initialisé. Connectez-vous à 'ESP32_BT_Config'.");

  SerialBT.register_callback([](esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
    if (event == ESP_SPP_SRV_OPEN_EVT) {
      sendBluetoothWelcomeMessage();
    }
  });
  // === FIN DE VOTRE PARTIE BLUETOOTH ===

  connectToWiFi();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
  handleBluetoothCommands(); // Votre fonction originale
  processIncomingSerialData();

  // Gestion ping/timeout
  if (millis() - lastPingTime > PING_INTERVAL) {
    sendWebSocketPing();
    checkClientTimeouts();
    lastPingTime = millis();
  }
}

// ============== VOS FONCTIONS BLUETOOTH ORIGINALES (100% inchangées) ==============
void sendBluetoothWelcomeMessage() {
  SerialBT.println("🔗 Bienvenue sur ESP32_BT_Config !");
  SerialBT.println("Voici les informations actuelles et commandes disponibles :");

  if (WiFi.status() == WL_CONNECTED) {
    SerialBT.println("✅ WiFi connecté !");
    SerialBT.print("📶 Adresse IP : ");
    SerialBT.println(WiFi.localIP());
  } else {
    SerialBT.println("❌ WiFi non connecté.");
  }

  SerialBT.print("📡 SSID actuel : ");
  SerialBT.println(ssid);
  SerialBT.print("🔑 Mot de passe actuel : ");
  SerialBT.println(password);

  SerialBT.println("\n⚙️ Commandes disponibles :");
  SerialBT.println(" - SSID:<NomDuReseau>");
  SerialBT.println(" - PASS:<MotDePasse>");
  SerialBT.println(" - RESTART");
}

void handleBluetoothCommands() {
  if (SerialBT.available()) {
    String command = SerialBT.readStringUntil('\n');
    command.trim();

    if (command.startsWith("SSID:")) {
      ssid = command.substring(5);
      Serial.println("✅ SSID mis à jour : " + ssid);
      SerialBT.println("✅ SSID mis à jour : " + ssid);
      connectToWiFi();
    } else if (command.startsWith("PASS:")) {
      password = command.substring(5);
      Serial.println("✅ Mot de passe mis à jour.");
      SerialBT.println("✅ Mot de passe mis à jour.");
      connectToWiFi();
    } else if (command == "RESTART") {
      Serial.println("🔄 Redémarrage de l'ESP32...");
      SerialBT.println("🔄 Redémarrage de l'ESP32...");
      delay(1000);
      ESP.restart();
    } else {
      Serial.println("⚠️ Commande inconnue : " + command);
      SerialBT.println("⚠️ Commande inconnue : " + command);
    }
  }
}

// ============== FONCTIONS WiFi (adaptées pour garder votre style) ==============
void connectToWiFi() {
  Serial.println("🌐 Connexion en cours...");
  SerialBT.println("🌐 Connexion en cours...");

  WiFi.begin(ssid.c_str(), password.c_str());

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 20) {
    delay(500);
    Serial.print(".");
    SerialBT.print(".");
    retries++;
  }

  Serial.println("");
  SerialBT.println("");

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("✅ Connexion WiFi réussie !");
    SerialBT.println("✅ Connexion WiFi réussie !");
  } else {
    Serial.println("❌ Connexion WiFi échouée.");
    SerialBT.println("❌ Connexion WiFi échouée.");
  }
}

// ============== NOUVELLES FONCTIONS OPTIMISÉES ==============
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_TEXT: {
      String jsonStr = String((char*)payload);
      StaticJsonDocument<256> doc;

      DeserializationError error = deserializeJson(doc, jsonStr);
      if (error) {
        Serial.println("❌ Erreur JSON: " + String(error.c_str()));
        return;
      }

      String type = doc["type"] | "";
      String msg = doc["message"] | "";

      if (type == "group_game") {
        Serial1.println(msg);
        Serial.println("📨 Envoi à Arduino: " + msg);
        currentGameState = WAITING_CONFIRMATION;

      } else if (type == "game_status" && msg == "START_GAME") {
        Serial1.println("START_GAME");
        Serial.println("📨 Envoi à Arduino: START_GAME");

      } else if (type == "game_status" && msg == "CONFIRMED_GAME") {
        Serial1.println("CONFIRMED_GAME");
        Serial.println("📨 Envoi à Arduino: CONFIRMED_GAME");
      }
      break;
    }
    case WStype_PONG:
      lastPongTimes[num] = millis();
      break;
    case WStype_DISCONNECTED:
      Serial.printf("❌ Client %u déconnecté.\n", num);
      break;
    case WStype_CONNECTED:
      lastPongTimes[num] = millis();
      Serial.printf("✅ Client %u connecté.\n", num);
      break;
  }
}

void processIncomingSerialData() {
  while (Serial1.available()) {
    String incomingData = Serial1.readStringUntil('\n');
    incomingData.trim();
    lastSerialActivity = millis();

    Serial.println("📥 Message reçu de l'Arduino: " + incomingData);

    if (incomingData.startsWith("J")) {
      handleScoreData(incomingData.substring(1)); // Enlever le J ici aussi
    } else if (incomingData == "START") {
      sendGameStatus("START");
      currentGameState = WAITING_CONFIRMATION;
    } else if (incomingData == "CONFIRMED_GAME") {
      sendGameStatus("CONFIRMED_GAME");
    }
  }
}

void handleScoreData(const String& data) {
  int colon1 = data.indexOf(':');
  int colon2 = data.indexOf(':', colon1 + 1);
  int colon3 = data.lastIndexOf(':');

  // Extraction des données
  int playerIndex = data.substring(0, colon1).toInt();
  int point = data.substring(colon1 + 1, colon2).toInt();
  int pointbonus = data.substring(colon2 + 1, colon3).toInt();
  int score = data.substring(colon3 + 1).toInt();

  // Création du nouveau document JSON
  StaticJsonDocument<256> outputDoc;
  outputDoc["playerIndex"] = playerIndex;
  outputDoc["point"] = score;
  outputDoc["pointbonus"] = points;
  outputDoc["score"] = pointsbonus;

  // Serialisation et envoi
  String output;
  serializeJson(outputDoc, output);
  webSocket.broadcastTXT(output);
  Serial.println("📨 Score: " + output);
}

void sendGameStatus(const String& status) {
  StaticJsonDocument<128> doc;
  doc["type"] = "game_status";
  doc["message"] = status;
  String output;
  serializeJson(doc, output);
  webSocket.broadcastTXT(output);
  Serial.println("📨 Données envoyées via WebSocket : " + output); // Ajout du log
}

void sendWebSocketPing() {
  for (uint8_t i = 0; i < WEBSOCKETS_SERVER_CLIENT_MAX; i++) {
    if (webSocket.clientIsConnected(i)) {
      webSocket.sendPing(i);
    }
  }
}

void checkClientTimeouts() {
  unsigned long now = millis();
  for (uint8_t i = 0; i < WEBSOCKETS_SERVER_CLIENT_MAX; i++) {
    if (webSocket.clientIsConnected(i) && now - lastPongTimes[i] > CLIENT_TIMEOUT) {
      webSocket.disconnect(i);
    }
  }
}

