
void communications() {
  if (Serial1.available()) {
    String message = Serial1.readStringUntil('\n');
    message.trim();

    Serial.print("📥 Message reçu de l'ESP32 : ");
    Serial.println(message);

    if (message == "CF1") {
      // Démarrer la partie avec le groupe "CF1"
      Serial.println("🎮 Commande CF1 reçue !");
      startGame("CF1");
      Serial1.println("START_GAME");
      Serial.println("📤 Envoi à ESP32: START_GAME");
    } else if (message == "START_GAME") {
      // Démarrer la partie
      Serial.println("🎮 Commande START_GAME reçue !");
      CF1(); // Appeler CF1 pour envoyer la confirmation après avoir reçu START_GAME
    } else if (message == "Partie lancée") {
      // Partie lancée
      Serial.println("🎮 Commande Partie lancée reçue !");
      partieLancee = true;
      partieLanceeFonction(); // Appel de la fonction renommée
    } else if (message == "JoueurSuivant") {
      // Passer au joueur suivant
      Serial.println("🎮 Commande JoueurSuivant reçue !");
      joueurSuivant();
    } else if (message == "TourSuivant") {
      // Passer au tour suivant
      Serial.println("🎮 Commande TourSuivant reçue !");
      tourSuivant();
    } else if (message == "GO") {
      // Démarrer ou continuer le jeu
      Serial.println("🎮 Commande GO reçue !");
      go();
    }
  }

  // Vérification de l'état de la partie
  if (partieLancee) {
    Serial.println("Partie est bien lancée depuis CF1");
    // Ajoutez ici le code pour gérer la partie en cours
  }
}

void startGame(String group) {
  // Logique pour démarrer la partie avec le groupe spécifié
  Serial.println("Partie démarrée avec le groupe : " + group);
}

void startGame() {
  // Logique pour démarrer la partie
  Serial.println("Partie démarrée");
  // Envoyer le message "Partie lancée" à l'ESP32
  Serial1.println("Partie lancée");
  Serial.println("📤 Envoi à ESP32: PARTIE_LANCEE");
}

void partieLanceeFonction() {
  // Logique pour traiter le message "Partie lancée"
  Serial.println("Partie lancée");
}

void go() {
  // Logique pour démarrer ou continuer le jeu
  Serial.println("GO : Démarrage ou continuation du jeu");
  // Envoyer le message "GO" à l'ESP32
  Serial1.println("GO");
  Serial.println("📤 Envoi à ESP32: GO");
}

void joueurSuivant() {
  // Logique pour passer au joueur suivant
  Serial.println("Passage au joueur suivant");
  // Envoyer le message "JoueurSuivant" à l'ESP32
  Serial1.println("JoueurSuivant");
  Serial.println("📤 Envoi à ESP32: JOUEUR_SUIVANT");
}

void tourSuivant() {
  // Logique pour passer au tour suivant
  Serial.println("Passage au tour suivant");
  // Envoyer le message "TourSuivant" à l'ESP32
  Serial1.println("TourSuivant");
  Serial.println("📤 Envoi à ESP32: TOUR_SUIVANT");
}


