
// Réglage des différents paramètre :

// 1 = l'intensité de la bande
// 2 = le volume du son
// 3 = pour le wifi - SSID / mot de passe

void RgIntensite() {
  lcd.setCursor(0, 0);
  lcd.print("Page pour le reglage");
  lcd.setCursor(3, 1);
  lcd.print("intensite LED"); 
  lcd1.setCursor(0, 0);
  lcd1.print("Augmenter / bouton +");
  lcd1.setCursor(0, 1);
  lcd1.print("Diminuer  / bouton -");
  lcd1.setCursor(0, 3);
  lcd1.print("Pour sortir   --> OK");
  Serial.println("Appel de RgIntensite()");
  // Gestion des boutons
  statusBoutonG = digitalRead(boutonG);
  if (statusBoutonG == LOW) {
    brightness = min(brightness + 25, 250);
    Serial.print("Augmentation de la luminosité: ");
    Serial.println(brightness);
    delay(ButtonDelay);
  } 
  statusBoutonD = digitalRead(boutonD);
  if (statusBoutonD == LOW) {
    brightness = max(brightness - 25, 0);
    Serial.print("Diminution de la luminosité: ");
    Serial.println(brightness);
    delay(ButtonDelay);
  }
  // Appliquer la nouvelle luminosité
  FastLED.setBrightness(brightness);
  FastLED.show();
  Serial.println("FastLED mis à jour !");
  lcd.setCursor(0, 3);
  lcd.print("Luminosite : ");
  lcd.setCursor(13, 3);  // Position pour écraser l'ancienne valeur
  lcd.print("   ");      // Efface l'ancienne valeur
  lcd.setCursor(16, 3);
  lcd.print("/250");
  lcd.setCursor(13, 3);
  lcd.print(brightness);
  // Bouton pour quitter
  statusBoutonE = digitalRead(boutonE);
  if (statusBoutonE == LOW) {
    Serial.println("Retour à l'accueil...");
    inIntensityMode = false;      // Désactive le mode Intensité
    disableLedAnimation = false;  // Réactive les animations LED
    ParametresIL();
    delay(ButtonDelay);
  }
}

void RgVolume() {
  lcd.setCursor(0, 0);
  lcd.print("Page pour le reglage");
  lcd.setCursor(3, 1);
  lcd.print("du volume"); 
  lcd1.setCursor(0, 0);
  lcd1.print("Augmenter / bouton +");
  lcd1.setCursor(0, 1);
  lcd1.print("Diminuer  / bouton -");
  lcd1.setCursor(0, 3);
  lcd1.print("Pour sortir   --> OK");
  Serial.println("Appel de RgVolume()");
  // Gestion des boutons
  statusBoutonG = digitalRead(boutonG);
  if (statusBoutonG == LOW) { // Augmente le volume
    volume = min(volume + 3, 30);
    Serial.print("Volume augmenté: ");
    Serial.println(volume);
    delay(ButtonDelay); // Anti-rebond
  } 
  // Gestion des boutons
  statusBoutonD = digitalRead(boutonD);
  if (statusBoutonD == LOW) { // Diminue le volume
    volume = max(volume - 3, 0);
    Serial.print("Volume diminué: ");
    Serial.println(volume);
    delay(ButtonDelay); // Anti-rebond
  }
  // Appliquer le nouveau volume
  myDFPlayer.volume(volume);
  Serial.println("Volume mis à jour !");
  lcd.setCursor(0, 3);
  lcd.print("Volume actuel : ");
  lcd.setCursor(15, 3);  // Position pour écraser l'ancienne valeur
  lcd.print("   ");      // Efface l'ancienne valeur
  lcd.setCursor(17, 3);
  lcd.print("/30");
  lcd.setCursor(15, 3);
  lcd.print(volume);
  // Bouton pour quitter
  statusBoutonE = digitalRead(boutonE);
  if (statusBoutonE == LOW) {
    Serial.println("Retour à l'accueil...");
    inIntensitySon = false; // Variable pour suivre le volume
    disableSonAnimation = false;  // Variable pour désactiver SonAleatoire()
    ParametresIL();
    delay(ButtonDelay);
  }
}

