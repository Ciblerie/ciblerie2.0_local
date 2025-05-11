#include <Arduino.h>

// Groupes de scores
const char* groupes[] = {"F", "SP", "P", "C", "L", "LJ", "MS", "CPT"};
const int nombreGroupes = 8;
// F=0, SP=1, P=2, C=3, L=4, LJ=5, MS=6
int indexgroupe = 0; // Par défaut, groupe "F" = "Facile"

// Configuration des joueurs et scores
const int totalJoueurs = 4;             // Nombre de joueurs (J1 à J4)
const int totalScoresParJoueur = 12;    // Nombre de scores par joueur
const int intervalEnvoi = 1000;         // Intervalle entre chaque envoi (en ms)

// Valeurs possibles des points
//const int valeursPoints[] = {0, 5, 10, 15, 25, 50, 100, 150, 200, 250};
const int valeursPoints[] = {5, 10, 15, 25, 50};
const int totalValeursPoints = sizeof(valeursPoints) / sizeof(valeursPoints[0]);

// Variables pour la gestion des scores
int scoresJoueurs[totalJoueurs][totalScoresParJoueur]; // Table des scores pour chaque joueur
int joueurActuel = 0;                                  // Joueur en cours
int scoreActuelIndex = 0;                              // Score actuel à envoyer pour le joueur courant
unsigned long dernierEnvoi = 0;                        // Temps du dernier envoi
int scoreCumule = 0;                                   // Score cumulé pour le joueur courant

// Nouveaux états pour la configuration
bool pseudosConfigures = false;
bool partieDemarree = false;
unsigned long attenteConfigStart = 0;
const unsigned long timeoutConfig = 30000; // 30 secondes max d'attente

void setup() {
  // Initialisation des ports série
  Serial.begin(115200);    // Moniteur série pour le débogage
  Serial1.begin(9600);     // Communication avec l'ESP32 via Serial1

  // Générer le groupe aléatoire pour la partie
  randomSeed(analogRead(A15)); // Initialisation de la graine pour le générateur aléatoire
  indexgroupe = random(0, nombreGroupes); // Génération aléatoire d'un groupe

  // Génération des points aléatoires pour chaque joueur
  for (int joueur = 0; joueur < totalJoueurs; joueur++) {
    for (int score = 0; score < totalScoresParJoueur; score++) {
      scoresJoueurs[joueur][score] = valeursPoints[random(0, totalValeursPoints)];
    }
  }

  Serial.println("🎯 Scores générés pour chaque joueur :");
  for (int joueur = 0; joueur < totalJoueurs; joueur++) {
    Serial.print("J" + String(joueur + 1) + ": ");
    for (int score = 0; score < totalScoresParJoueur; score++) {
      Serial.print(scoresJoueurs[joueur][score]);
      if (score < totalScoresParJoueur - 1) Serial.print(", ");
    }
    Serial.println();
  }

  // Envoi de la demande de configuration des pseudos
  Serial1.println("CONFIG_PSEUDOS");
  Serial.println("📤 Envoi : CONFIG_PSEUDOS");
  attenteConfigStart = millis();
}

void loop() {
  // Vérification de la réponse de configuration
  if (!partieDemarree) {
    if (Serial1.available()) {
      String message = Serial1.readStringUntil('\n');
      message.trim();
      
      if (message == "START_GAME") {
        partieDemarree = true;
        pseudosConfigures = true;
        Serial1.println("Groupe : " + String(groupes[indexgroupe]));
        Serial.println("📤 Envoi : Groupe : " + String(groupes[indexgroupe]));
        dernierEnvoi = millis(); // Initialiser le timer pour le premier score
      }
    }

    // Timeout après 30 secondes
    if (millis() - attenteConfigStart > timeoutConfig && !pseudosConfigures) {
      Serial.println("⚠️ Timeout configuration - Démarrage avec pseudos par défaut");
      partieDemarree = true;
      pseudosConfigures = true;
      Serial1.println("Groupe : " + String(groupes[indexgroupe]));
      Serial.println("📤 Envoi : Groupe : " + String(groupes[indexgroupe]));
    }

    return;
  }

  // Gestion normale des envois de scores si la partie est démarrée
  if (millis() - dernierEnvoi >= intervalEnvoi) {
    dernierEnvoi = millis();

    // Mise à jour du score cumulé
    scoreCumule += scoresJoueurs[joueurActuel][scoreActuelIndex];

    // Envoi du score actuel et cumulé du joueur courant
    String message = "J" + String(joueurActuel + 1) + " : " + 
                    String(scoresJoueurs[joueurActuel][scoreActuelIndex]) + " : " + 
                    String(scoreCumule);
    Serial1.println(message); // Envoi à l'ESP32 via Serial1
    Serial.println("📤 Envoi : " + message);

    // Passage au score suivant
    scoreActuelIndex++;
    if (scoreActuelIndex >= totalScoresParJoueur) {
      // Si tous les scores du joueur courant ont été envoyés, passer au joueur suivant
      scoreActuelIndex = 0;
      scoreCumule = 0; // Réinitialisation du score cumulé pour le joueur suivant
      joueurActuel++;

      // Si tous les joueurs ont été traités, terminer le jeu
      if (joueurActuel >= totalJoueurs) {
        Serial1.println("FIN_GAME"); // Envoi du message de fin à l'ESP32
        Serial.println("📤 Envoi : FIN_GAME");
        while (true); // Arrêt du programme après la fin du jeu
      }
    }
  }
}