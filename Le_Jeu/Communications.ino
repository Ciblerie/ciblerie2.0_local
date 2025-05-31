
// 📨 📥
void communications() {
  if (Serial1.available() > 0) {
    String messageLu = Serial1.readStringUntil('\n');
    messageLu.trim();

    char messageRecu[32]; // Tableau pour stocker le message reçu
    messageLu.toCharArray(messageRecu, 32);
    messageRecu[messageLu.length()] = '\0';

    Serial.print("📥 Message reçu de l'ESP32 : ");
    Serial.println(messageRecu);

    // Traitement des messages
    if (messageRecu[0] != '\0' && strcmp(messageRecu, "START_GAME") != 0 && strcmp(messageRecu, "CONFIRMED_GAME") != 0 && strcmp(messageRecu, "NEXT_PLAYER") != 0 && strcmp(messageRecu, "NEXT_TURN") != 0 && strcmp(messageRecu, "FIN_GAME") != 0) {
      groupeSelectionne = String(messageRecu);
      Serial.print("Groupe sélectionné : ");
      Serial.println(groupeSelectionne);
      Serial.print("Groupe enregistré : ");
      Serial.println(groupeSelectionne);
      //envoyerMessage("START"); // Envoyer "START" pour activer le bouton "Attente groupe"
      Serial1.println("START"); // Envoyer "START" pour activer le bouton "Attente groupe"
      Serial.print("📨 Message envoyé à ESP32 : ");
      Serial.println("START"); // Log d'envoi
    } else if (strcmp(messageRecu, "START_GAME") == 0 && !partieDemarree) {
      Serial.println("Message reçu : START_GAME");
      Serial.print("Partie démarrée avec le groupe : ");
      Serial.println(groupeSelectionne);

      if (groupeSelectionne == "CF1") {
        CF1();
      } else if (groupeSelectionne == "CF2") {
        CF2();
      } else if (groupeSelectionne == "CF3") {
        CF3();
      } else if (groupeSelectionne == "CF4") {
        CF4();
      } else if (groupeSelectionne == "CSP1") {
        CSP1();
      } else if (groupeSelectionne == "CSP2") {
        CSP2();
      } else if (groupeSelectionne == "CSP3") {
        CSP3();
      } else if (groupeSelectionne == "CSP4") {
        CSP4();
      } else if (groupeSelectionne == "CP1") {
        CP1();
      } else if (groupeSelectionne == "CP2") {
        CP2();
      } else if (groupeSelectionne == "CP3") {
        CP3();
      } else if (groupeSelectionne == "CP4") {
        CP4();
      } else if (groupeSelectionne == "CC1") {
        CC1();
      } else if (groupeSelectionne == "CC2") {
        CC2();
      } else if (groupeSelectionne == "CC3") {
        CC3();
      } else if (groupeSelectionne == "CC4") {
        CC4();
      } else if (groupeSelectionne == "CL1") {
        CL1();
      } else if (groupeSelectionne == "CL2") {
        CL2();
      } else if (groupeSelectionne == "CL3") {
        CL3();
      } else if (groupeSelectionne == "CL4") {
        CL4();
      } else if (groupeSelectionne == "LJ1") {
        LJ1();
      } else if (groupeSelectionne == "LJ2") {
        LJ2();
      } else if (groupeSelectionne == "LJ3") {
        LJ3();
      } else if (groupeSelectionne == "LJ4") {
        LJ4();
      } else if (groupeSelectionne == "MS1") {
        MS1();
      } else if (groupeSelectionne == "MS2") {
        MS2();
      } else if (groupeSelectionne == "MS3") {
        MS3();
      } else if (groupeSelectionne == "MS4") {
        MS4();
      } else if (groupeSelectionne == "CPT1") {
        CPT1();
      } else {
        Serial.println("Groupe non reconnu !");
      }
      partieDemarree = true;
      groupeSelectionne = ""; // Réinitialiser la variable groupeSelectionne
    } else if (strcmp(messageRecu, "CONFIRMED_GAME") == 0 && partieDemarree) {
      Serial.println("Message reçu : CONFIRMED_GAME");
      //envoyerMessage("CONFIRMED_GAME");
      Serial1.println("CONFIRMED_GAME");
       Serial.print("📨 Message envoyé à ESP32 : ");
      Serial.println("CONFIRMED_GAME");
    } else if (strcmp(messageRecu, "NEXT_PLAYER") == 0 && partieDemarree) {
      Serial.println("Message reçu : NEXT_PLAYER");
      //envoyerMessage("GO");
      Serial1.println("GO");
       Serial.print("📨 Message envoyé à ESP32 : ");
      Serial.println("GO");
    } else if (strcmp(messageRecu, "NEXT_TURN") == 0 && partieDemarree) {
      Serial.println("Message reçu : NEXT_TURN");
      //envoyerMessage("GO");
      Serial1.println("GO");
       Serial.print("📨 Message envoyé à ESP32 : ");
      Serial.println("GO");
    } else if (strcmp(messageRecu, "FIN_GAME") == 0 && partieDemarree) {
      Serial.println("Message reçu : FIN_GAME");
      // Actions de fin de partie
      partieDemarree = false;
    }
  }
}

void envoyerMessage(String message) {
  Serial1.println(message);
  Serial.print("📨 Message envoyé à ESP32 : ");
  Serial.println(message);
}

