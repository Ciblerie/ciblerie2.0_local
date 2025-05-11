#include <WiFi.h>
#include <WebSocketsServer.h>
#include <BluetoothSerial.h>

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

// ✅ Suivi du début de partie
bool startSent = false;

void connectToWiFi();
void ensureWiFiConnection();
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length);
void processIncomingSerialData();
String convertToJSON(String data);
void handleBluetoothCommands();
void sendBluetoothWelcomeMessage();
void sendWebSocketPing();
void checkClientTimeouts();

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 16, 17);
  Serial.println("🔗 Liaison série avec Arduino Méga initialisée.");

  SerialBT.begin("🖥️ ESP32_BT_Config");
  Serial.println("📡 Bluetooth initialisé. Connectez-vous à 'ESP32_BT_Config'.");

  SerialBT.register_callback([](esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
    if (event == ESP_SPP_SRV_OPEN_EVT) {
      sendBluetoothWelcomeMessage();
    }
  });

  connectToWiFi();

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  ensureWiFiConnection();
  webSocket.loop();
  processIncomingSerialData();
  handleBluetoothCommands();

  unsigned long currentMillis = millis();
  if (currentMillis - lastPingTime > PING_INTERVAL) {
    sendWebSocketPing();
    checkClientTimeouts();
    lastPingTime = currentMillis;
  }
}

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

  sendBluetoothWelcomeMessage();
}

void ensureWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("⚠️ WiFi déconnecté. Tentative de reconnexion...");
    connectToWiFi();
  }
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

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_TEXT: {
      String message = String((char*)payload);
      Serial.println("📨 Message reçu : " + message);
      
      // Nouveau: Gestion du message START_GAME
      if (message == "{\"type\":\"start_game\"}") {
        Serial1.println("START_GAME");
        Serial.println("📤 Envoi à Arduino: START_GAME");
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
    default:
      break;
  }
}

void processIncomingSerialData() {
  while (Serial1.available()) {
    String incomingData = Serial1.readStringUntil('\n');
    incomingData.trim();

    if (!incomingData.isEmpty()) {
      // ✅ TRAITEMENT DU SCORE
      if (incomingData.startsWith("J")) {
        int colon1 = incomingData.indexOf(':');
        int colon2 = incomingData.lastIndexOf(':');

        String joueur = incomingData.substring(0, colon1);
        String points = incomingData.substring(colon1 + 1, colon2);
        String cumul = incomingData.substring(colon2 + 1);

        Serial.printf("📥 Reçu : %s : %s : %s\n", joueur.c_str(), points.c_str(), cumul.c_str());

        String jsonData = "{\"playerIndex\": " + String(joueur.substring(1).toInt() - 1) +
                          ", \"point\": " + points +
                          ", \"score\": " + cumul + "}";

        webSocket.broadcastTXT(jsonData);
        Serial.printf("📤 Données envoyées : %s\n", jsonData.c_str());

      // ✅ DÉTECTION DE LA CONFIGURATION DES PSEUDOS
      } else if (incomingData == "CONFIG_PSEUDOS") {
        Serial.println("📥 Reçu : CONFIG_PSEUDOS");
        String jsonData = "{\"type\": \"config_pseudos\"}";
        webSocket.broadcastTXT(jsonData);
        Serial.println("📤 Données envoyées via WebSocket : " + jsonData);

      // ✅ DÉTECTION DU DÉBUT DE PARTIE PAR "Groupe"
      } else if (incomingData.startsWith("Groupe : ")) {
        if (!startSent) {
          String jsonStart = "{\"type\": \"start\"}";
          webSocket.broadcastTXT(jsonStart);
          Serial.println("📤 Début de partie détecté → envoyé : " + jsonStart);
          startSent = true;
        }

        String groupe = incomingData.substring(9);
        Serial.printf("📥 Reçu : %s\n", groupe.c_str());
        String jsonData = "{\"type\": \"groupe\", \"value\": \"" + groupe + "\"}";
        webSocket.broadcastTXT(jsonData);
        Serial.println("📤 Données envoyées via WebSocket : " + jsonData);

      // ✅ FIN DE PARTIE
      } else if (incomingData == "FIN_GAME") {
        Serial.println("📥 Reçu : FIN_GAME");
        startSent = false;
        String jsonData = "{\"type\": \"fin\", \"message\": \"FIN_GAME\"}";
        webSocket.broadcastTXT(jsonData);
        Serial.println("📤 Données envoyées via WebSocket : " + jsonData);

      } else {
        String jsonData = convertToJSON(incomingData);
        webSocket.broadcastTXT(jsonData);
        Serial.println("📤 Données envoyées via WebSocket : " + jsonData);
      }

    } else {
      Serial.println("⚠️ Données non valides reçues !");
    }
  }
}

String convertToJSON(String data) {
  String json = "{";

  if (data.startsWith("Groupe : ")) {
    json += "\"type\": \"groupe\", \"value\": \"" + data.substring(9) + "\"";
  } else if (data == "FIN_GAME") {
    json += "\"type\": \"fin\", \"message\": \"FIN_GAME\"";
  } else if (data == "CONFIG_PSEUDOS") {
    json += "\"type\": \"config_pseudos\"";
  }

  json += "}";
  return json;
}

void sendWebSocketPing() {
  for (uint8_t i = 0; i < WEBSOCKETS_SERVER_CLIENT_MAX; i++) {
    if (webSocket.clientIsConnected(i)) {
      webSocket.sendPing(i);
      Serial.printf("📡 Ping envoyé au client %u\n", i);
    }
  }
}

void checkClientTimeouts() {
  unsigned long now = millis();
  for (uint8_t i = 0; i < WEBSOCKETS_SERVER_CLIENT_MAX; i++) {
    if (webSocket.clientIsConnected(i)) {
      if (now - lastPongTimes[i] > CLIENT_TIMEOUT) {
        Serial.printf("⏱️ Client %u inactif. Déconnexion forcée.\n", i);
        webSocket.disconnect(i);
      }
    }
  }
}