
void communications() {
  if (Serial1.available() > 0) {
    char message[32]; // Tableau pour stocker le message reçu
    int len = Serial1.readBytesUntil('\n', message, 31); // Lire jusqu'à 31 caractères
    message[len] = '\0'; // Terminer la chaîne de caractères

    Serial.print("Message reçu de l'ESP32 : ");
    Serial.println(message);

    // Traitement des messages
    if (message[0] == 'C' && message[1] == 'F') { // Si le message commence par CF
      Serial.print("Groupe sélectionné : ");
      Serial.println(message); // Afficher le message (groupe)
      //strncpy(groupeSelectionne, message, 3); // Copier le groupe sélectionné // Suppression car groupeSelectionne non utilisé
      //groupeSelectionne[3] = '\0'; // Terminer la chaîne // Suppression car groupeSelectionne non utilisé
      Serial.print("Groupe enregistré : ");
      Serial.println(message); // Afficher le groupe // Modifié car groupeSelectionne non utilisé
      envoyerMessage("START"); // Envoyer "START" pour activer le bouton "Attente groupe"
    } else if (strcmp(message, "START_GAME") == 0 && !partieDemarree) {
      Serial.println("Message reçu : START_GAME"); // Log de réception
      Serial.print("Partie démarrée avec le groupe : ");
      Serial.println(message); // Afficher le groupe sélectionné // Modifié car groupeSelectionne non utilisé
      //envoyerMessage("START_GAME"); // Ne pas renvoyer START_GAME
      //CF1(); // Appeler CF1() pour lancer la partie // Suppression car CF1() fait déjà l'envoi de CONFIRMED_GAME
      envoyerMessage("CONFIRMED_GAME"); // Envoyer "CONFIRMED_GAME" directement
      partieDemarree = true;
    } else if (strcmp(message, "CONFIRMED_GAME") == 0 && partieDemarree) {
      Serial.println("Message reçu : CONFIRMED_GAME"); // Log de réception
      envoyerMessage("CONFIRMED_GAME");
    } else if (strcmp(message, "NEXT_PLAYER") == 0 && partieDemarree) {
      Serial.println("Message reçu : NEXT_PLAYER"); // Log de réception
      envoyerMessage("GO");
    } else if (strcmp(message, "NEXT_TURN") == 0 && partieDemarree) {
      Serial.println("Message reçu : NEXT_TURN"); // Log de réception
      envoyerMessage("GO");
    } else if (strcmp(message, "FIN_GAME") == 0 && partieDemarree) {
      Serial.println("Message reçu : FIN_GAME"); // Log de réception
      // Actions de fin de partie
      partieDemarree = false;
    }
  }
}

void envoyerMessage(String message) {
  Serial1.println(message);
  Serial.print("Message envoyé à ESP32 : ");
  Serial.println(message); // Log d'envoi
}

