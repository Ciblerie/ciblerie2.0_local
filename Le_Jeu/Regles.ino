
void SMRAZ(){ // Remise des servos à zéro
  EcranScores1();
    for (int i = 0; i < NUM_SERVOS; i++) {
        pwm.setPWM(i, 0, pulseWidth(0));
    }
    delay(500);
}

void SMRAZTP(){ // Action pour faire tomber la cible
  EcranScores1();
    // Position initiale (0)
    for (int i = 0; i < NUM_SERVOS; i++) {
        pwm.setPWM(i, 0, pulseWidth(0));
    }
    delay(500);
    // Position pour faire tomber la cible (85)
    for (int i = 0; i < NUM_SERVOS; i++) {
        pwm.setPWM(i, 0, pulseWidth(85));
    }
    delay(500);
}

// ✅ Nouvelle version de MoteurLJ() avec activation/désactivation propre des cibles (moteurs)
void Moteur(){
    int Motor_aleatoire = random(0, 3); // Choisir un moteur aléatoire entre 0 et 2
    if (millis() - Time1 >= Period1) {
        pwm.setPWM(Motor_aleatoire, 0, pulseWidth(0)); // Éteint le moteur sélectionné
        Time1 = millis();
    }
    if (millis() - Time2 >= Period2) {
        for (int i = 0; i < 16; i++) {
            pwm.setPWM(i, 0, pulseWidth(0)); // Éteindre tous les moteurs
        }
        pwm.setPWM(Motor_aleatoire, 0, pulseWidth(85)); // Activer le moteur sélectionné
        Time2 = millis();
    }
}

void EcranTourSuivant(){
  EcranScores1();  
  lcd.clear();
  printBigNum(31, 2, 1);
  printBigNum(26, 5, 1);
  printBigNum(32, 8, 1);
  printBigNum(29, 11, 1); 
  printBigNum(tourEnCours,15,1);
  delay(2000);
  EcranScores1();
}

void EcranJoueurSuivant(){
  EcranScores1();
  lcd.clear();
  printBigNum(21, 6, 1);
  printBigNum(joueurEnCours,10,1);
  delay(2000);
  EcranScores1(); 
}

void EcranGo() {
  EcranScores1();
  myDFPlayer.playMp3Folder(31);
  delay(3000);
  EcranScores1();
  lcd.clear();
  printBigNum(18, 7, 1);
  printBigNum(26, 11, 1);
  delay(1000);  
}

void EcranGoJeux(){
  EcranScores1();
  lcd.clear();
  printBigNum(18, 7, 1);
  printBigNum(26, 11, 1);
  delay(1000);   
}

void Oups(){
  EcranScores1();
  lcd.clear();
  printBigNum(26, 3, 0); //O
  printBigNum(32, 7, 0); //U
  printBigNum(27, 11, 0); //P
  printBigNum(30, 15, 0); //S
  delay(2000);
}

void GameOver()
{
  EcranScores1();
  lcd.clear();  
  printBigNum(18, 3, 0); //G
  printBigNum(12, 7, 0); //A
  printBigNum(24, 11, 0); //M
  printBigNum(16, 15, 0); //E
  printBigNum(26, 3, 2); //O
  printBigNum(33, 7, 2); //V
  printBigNum(16, 11, 2); //E
  printBigNum(29, 15, 2); //R  
  delay(2000);
  EcranScores1();
}

void FinGame(){
  EcranScores1();
  lcd.clear();
  printBigNum(17, 3, 0); //F
  printBigNum(20, 7, 0); //I
  printBigNum(25, 11, 0); //N 
  printBigNum(18, 3, 2); //G
  printBigNum(12, 7, 2); //A
  printBigNum(24, 11, 2); //M
  printBigNum(16, 15, 2); //E
  EcranScores1();
  delay(2000);
  EcranScores1();
}

void clignotementLED(int repetitions){
  for (int i = 0; i < repetitions; i++) {
    fill_solid(leds, NUM_LEDS, CRGB::Red); FastLED.show(); delay(50);
    fill_solid(leds, NUM_LEDS, CRGB::Orange); FastLED.show(); delay(50);
    fill_solid(leds, NUM_LEDS, CRGB::Yellow); FastLED.show(); delay(50);
  }
}

void Cinquante(){ //50
  EcranScores1();
  lcd.clear();
  myDFPlayer.stop();
  for (int i = 0; i < 3; i++) { // Répète 3 fois
  fill_solid(leds, NUM_LEDS, CRGB::Blue); FastLED.show(); printBigNum(5, 6, 1); printBigNum(0, 10, 1); delay(300); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::White); FastLED.show(); printBigNum(5, 6, 1); printBigNum(0, 10, 1); delay(300); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Red); FastLED.show(); printBigNum(5, 6, 1); printBigNum(0, 10, 1); delay(300); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Black); FastLED.show(); printBigNum(5, 6, 1); printBigNum(0, 10, 1); delay(300); FastLED.clear(); FastLED.show();
  // delay de 1s200 part cycle
  }
// Delay total 3s600 d'intéruption
} 

void Cent(){ //100
  EcranScores1();
  lcd.clear();
  myDFPlayer.stop();
  for (int i = 0; i < 3; i++) { // Répète 3 fois
  fill_solid(leds, NUM_LEDS, CRGB::Green); FastLED.show(); printBigNum(1, 4, 1); printBigNum(0, 8, 1); printBigNum(0, 12, 1); delay(250); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Blue); FastLED.show(); printBigNum(1, 4, 1); printBigNum(0, 8, 1); printBigNum(0, 12, 1); delay(250); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Green); FastLED.show(); printBigNum(1, 4, 1); printBigNum(0, 8, 1); printBigNum(0, 12, 1); delay(250); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Blue); FastLED.show(); printBigNum(1, 4, 1); printBigNum(0, 8, 1); printBigNum(0, 12, 1); delay(250); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Black); FastLED.show(); printBigNum(1, 4, 1); printBigNum(0, 8, 1); printBigNum(0, 12, 1); delay(250); FastLED.clear(); FastLED.show();
  // delay de 1s250 part cycle
  }
  fill_solid(leds, NUM_LEDS, CRGB::Green);  FastLED.show(); printBigNum(1, 4, 1); printBigNum(0, 8, 1); printBigNum(0, 12, 1); delay(500); FastLED.clear(); FastLED.show();
// Delay total 4s250 d'intéruption
}

void CentCinquante(){ //150
  EcranScores1();
  lcd.clear();
  myDFPlayer.stop();
  for (int i = 0; i < 4; i++) { // Répète 4 fois
  fill_solid(leds, NUM_LEDS, CRGB::Green); FastLED.show(); printBigNum(1, 4, 1); printBigNum(5, 8, 1); printBigNum(0, 12, 1); delay(200); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Blue); FastLED.show(); printBigNum(1, 4, 1); printBigNum(5, 8, 1); printBigNum(0, 12, 1); delay(200); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Magenta); FastLED.show(); printBigNum(1, 4, 1); printBigNum(5, 8, 1); printBigNum(0, 12, 1); delay(200); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Green); FastLED.show(); printBigNum(1, 4, 1); printBigNum(5, 8, 1); printBigNum(0, 12, 1); delay(200); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Blue); FastLED.show(); printBigNum(1, 4, 1); printBigNum(5, 8, 1); printBigNum(0, 12, 1); delay(200); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Magenta); FastLED.show(); printBigNum(1, 4, 1); printBigNum(5, 8, 1); printBigNum(0, 12, 1); delay(200); FastLED.clear(); FastLED.show();
  // delay de 1s200 part cycle
  }
  fill_solid(leds, NUM_LEDS, CRGB::Orange);  FastLED.show(); printBigNum(1, 4, 1); printBigNum(5, 8, 1); printBigNum(0, 12, 1); delay(500); FastLED.clear(); FastLED.show();
// Delay total 5s300 d'intéruption
}

void DeuxCent(){ //200
  EcranScores1();
  lcd.clear();
  myDFPlayer.stop();
  for (int i = 0; i < 4; i++) { // Répète 4 fois
  fill_solid(leds, NUM_LEDS, CRGB::Green); FastLED.show(); printBigNum(2, 4, 1); printBigNum(0, 8, 1); printBigNum(0, 12, 1); delay(150); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Blue); FastLED.show(); printBigNum(2, 4, 1); printBigNum(0, 8, 1); printBigNum(0, 12, 1); delay(150); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Magenta); FastLED.show(); printBigNum(2, 4, 1); printBigNum(0, 8, 1); printBigNum(0, 12, 1); delay(150); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Cyan); FastLED.show(); printBigNum(2, 4, 1); printBigNum(0, 8, 1); printBigNum(0, 12, 1); delay(150); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Green); FastLED.show(); printBigNum(2, 4, 1); printBigNum(0, 8, 1); printBigNum(0, 12, 1); delay(150); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Blue); FastLED.show(); printBigNum(2, 4, 1); printBigNum(0, 8, 1); printBigNum(0, 12, 1); delay(150); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Magenta); FastLED.show(); printBigNum(2, 4, 1); printBigNum(0, 8, 1); printBigNum(0, 12, 1); delay(150); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Cyan); FastLED.show(); printBigNum(2, 4, 1); printBigNum(0, 8, 1); printBigNum(0, 12, 1); delay(150); FastLED.clear(); FastLED.show();
  // delay de 1s200 part cycle
  }
  fill_solid(leds, NUM_LEDS, CRGB::Yellow);  FastLED.show(); printBigNum(2, 4, 1); printBigNum(0, 8, 1); printBigNum(0, 12, 1); delay(500); FastLED.clear(); FastLED.show();
// Delay total 5s300 d'intéruption
}

void DeuxCentCinquante(){ //250
  EcranScores1();
  lcd.clear();
  myDFPlayer.stop();
  for (int i = 0; i < 4; i++) { // Répète 4 fois
  fill_solid(leds, NUM_LEDS, CRGB::Green); FastLED.show(); printBigNum(2, 4, 1); printBigNum(5, 8, 1); printBigNum(0, 12, 1); delay(150); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Blue); FastLED.show(); printBigNum(2, 4, 1); printBigNum(5, 8, 1); printBigNum(0, 12, 1); delay(150); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Magenta); FastLED.show(); printBigNum(2, 4, 1); printBigNum(5, 8, 1); printBigNum(0, 12, 1); delay(150); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Cyan); FastLED.show(); printBigNum(2, 4, 1); printBigNum(5, 8, 1); printBigNum(0, 12, 1); delay(150); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Purple); FastLED.show(); printBigNum(2, 4, 1); printBigNum(5, 8, 1); printBigNum(0, 12, 1); delay(150); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Green); FastLED.show(); printBigNum(2, 4, 1); printBigNum(5, 8, 1); printBigNum(0, 12, 1); delay(150); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Blue); FastLED.show(); printBigNum(2, 4, 1); printBigNum(5, 8, 1); printBigNum(0, 12, 1); delay(150); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Magenta); FastLED.show(); printBigNum(2, 4, 1); printBigNum(5, 8, 1); printBigNum(0, 12, 1); delay(150); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Cyan); FastLED.show(); printBigNum(2, 4, 1); printBigNum(5, 8, 1); printBigNum(0, 12, 1); delay(150); FastLED.clear(); FastLED.show();
  fill_solid(leds, NUM_LEDS, CRGB::Purple); FastLED.show(); printBigNum(2, 4, 1); printBigNum(5, 8, 1); printBigNum(0, 12, 1); delay(150); FastLED.clear(); FastLED.show();
  // delay de 1s500 part cycle
  }
  fill_solid(leds, NUM_LEDS, CRGB::White);  FastLED.show(); printBigNum(2, 4, 1); printBigNum(5, 8, 1); printBigNum(0, 12, 1); delay(500); FastLED.clear(); FastLED.show();
// Delay total 6s500 d'intéruption
}

void EcranEnJeu() {
  lcd1.clear();
  lcd1.setCursor(0,0);
  lcd1.print("J1 : " + String(scores[1]));
  Serial.println("J1 : " + String(scores[1]));
//  Serial1.println("J1 : " + String(scores[1]));
//  Serial.println("📤 Envoi à ESP32: J1 : " + String(scores[1]));

  lcd1.setCursor(0,1);
  lcd1.print("J2 : " + String(scores[2]));
  Serial.println("J2 : " + String(scores[2]));
//  Serial1.println("J2 : " + String(scores[2]));
//  Serial.println("📤 Envoi à ESP32 : J2 : " + String(scores[2]));

  lcd1.setCursor(0,2);
  lcd1.print("J3 : " + String(scores[3]));
  Serial.println("J3 : " + String(scores[3]));
//  Serial1.println("J3 : " + String(scores[3]));
//  Serial.println("📤 Envoi à ESP32 : J3 : " + String(scores[3]));

  lcd1.setCursor(0,3);
  lcd1.print("J4 : " + String(scores[4]));
  Serial.println("J4 : " + String(scores[4]));
//  Serial1.println("J4 : " + String(scores[4]));
//  Serial.println("📤 Envoi à ESP32: J4 : " + String(scores[4]));

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tour  : "+ String(tourEnCours)+"  Reste : " + String(resteEnCours));
  Serial.println("Tour  : "+ String(tourEnCours)+"  Reste : " + String(resteEnCours));

  lcd.setCursor(0,3);
  lcd.print("Joueur: " + String(joueurEnCours));
  Serial.println("Joueur: " + String(joueurEnCours));
  
  String scorestring = String(scores[joueurEnCours]);
  // Code de 100.000 à 999.999  
    if (scorestring.length()==6){
      String Cmille  = String(scorestring.charAt(0));
      printBigNum(Cmille  .toInt(), 2, 1);      
      String Dmille  = String(scorestring.charAt(1));
      printBigNum(Dmille  .toInt(), 5, 1);      
      String millier = String(scorestring.charAt(2));
      printBigNum(millier.toInt(), 8, 1);      
      String centaine = String(scorestring.charAt(3));
      printBigNum(centaine.toInt(), 11, 1);
      String dizaine = String(scorestring.charAt(4));
      printBigNum(dizaine.toInt(), 14, 1);
      String unite = String(scorestring.charAt(5));
      printBigNum(unite.toInt(), 17, 1);
      }
  // Code de 10.000 à 99.999     
    else if (scorestring.length()==5){
      String Dmille  = String(scorestring.charAt(0));
      printBigNum(Dmille  .toInt(), 5, 1);      
      String millier = String(scorestring.charAt(1));
      printBigNum(millier.toInt(), 8, 1);      
      String centaine = String(scorestring.charAt(2));
      printBigNum(centaine.toInt(), 11, 1);
      String dizaine = String(scorestring.charAt(3));
      printBigNum(dizaine.toInt(), 14, 1);
      String unite = String(scorestring.charAt(4));
      printBigNum(unite.toInt(), 17, 1);
      }
  // Code de 1.000 à 9.999
    else if (scorestring.length()==4){
      String millier = String(scorestring.charAt(0));
      printBigNum(millier.toInt(), 8, 1);      
      String centaine = String(scorestring.charAt(1));
      printBigNum(centaine.toInt(), 11, 1);
      String dizaine = String(scorestring.charAt(2));
      printBigNum(dizaine.toInt(), 14, 1);
      String unite = String(scorestring.charAt(3));
      printBigNum(unite.toInt(), 17, 1);
    }
  // Code de 100 à 999      
    else if (scorestring.length()==3){
      String centaine = String(scorestring.charAt(0));
      printBigNum(centaine.toInt(), 11, 1);
      String dizaine = String(scorestring.charAt(1));
      printBigNum(dizaine.toInt(), 14, 1);
      String unite = String(scorestring.charAt(2));
      printBigNum(unite.toInt(), 17, 1);
    }
  // Code de 10 à 99    
    else if (scorestring.length()==2){
      String dizaine = String(scorestring.charAt(0));
      printBigNum(dizaine.toInt(), 14, 1); // 12
      String unite = String(scorestring.charAt(1));
      printBigNum(unite.toInt(), 17, 1); // 15
    }
  // Code de 01 à 09    
    else{
      String unite = String(scorestring.charAt(0));
      printBigNum(0, 14, 1); // 12
      printBigNum(unite.toInt(), 17, 1); // 15     
    }         
}

void EcranScores(){
  EcranScores1();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("J1 : " + String(scores[1]));
  Serial.println("J1 : " + String(scores[1]));
  lcd.setCursor(0,1);
  lcd.print("J2 : " + String(scores[2]));
  Serial.println("J2 : " + String(scores[2]));
  lcd.setCursor(0,2);
  lcd.print("J3 : " + String(scores[3]));
  Serial.println("J3 : " + String(scores[3]));
  lcd.setCursor(0,3);
  lcd.print("J4 : " + String(scores[4]));
  Serial.println("J4 : " + String(scores[4]));    
  delay(4000);
}

void EcranScores1(){
  if(millis()-Time18M>=Period18M){
  lcd1.clear();
  lcd1.setCursor(0,0);
  lcd1.print("J1 : " + String(scores[1]));
  Serial.println("J1 : " + String(scores[1]));
  lcd1.setCursor(0,1);
  lcd1.print("J2 : " + String(scores[2]));
  Serial.println("J2 : " + String(scores[2]));
  lcd1.setCursor(0,2);
  lcd1.print("J3 : " + String(scores[3]));
  Serial.println("J3 : " + String(scores[3]));
  lcd1.setCursor(0,3);
  lcd1.print("J4 : " + String(scores[4]));
  Serial.println("J4 : " + String(scores[4]));
  Time18M=millis();
  } 
}

void testKiller(){
  EcranScores1();
  if (killer[joueurEnCours] == 1){
  }
}

void AcquisitionCapteurs(){
  statusBoutonE = digitalRead(boutonE);    
  statusBoutonG = digitalRead(boutonG);
  statusBoutonD = digitalRead(boutonD);
  statusCible1 = digitalRead(cible1);
  statusCible2 = digitalRead(cible2);
  statusCible3 = digitalRead(cible3);
  statusCible4 = digitalRead(cible4);
  statusCible5 = digitalRead(cible5);
  statusCible6 = digitalRead(cible6);
  statusCible7 = digitalRead(cible7);
  statusCible8 = digitalRead(cible8);
  statusCible9 = digitalRead(cible9);
  statusCible10 = digitalRead(cible10);       
}

void Temporisation(){
  for (int T = 1; T <= 100 ; T++){
    while(statusBoutonE==LOW ||statusBoutonD==LOW || statusBoutonG==LOW || statusCible1==LOW || statusCible2==LOW || statusCible3==LOW || statusCible4==LOW || statusCible5==LOW || statusCible6==LOW || statusCible7==LOW || statusCible8==LOW || statusCible9==LOW || statusCible10==LOW ){    
      AcquisitionCapteurs();
      delay(125);
      delay(delaiTemporisation);
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------

void resetAllBonus0() {
    pointBonus5[joueurEnCours] = 0;
    pointBonus10[joueurEnCours] = 0;
    pointBonus15[joueurEnCours] = 0;
    pointBonus25[joueurEnCours] = 0;
    pointBonus50[joueurEnCours] = 0;
    pointBonus100[joueurEnCours] = 0;
    pointBonus150[joueurEnCours] = 0;
    pointBonus200[joueurEnCours] = 0;
    pointBonus250[joueurEnCours] = 0;
}
void resetAllBonus5() {
    pointBonus10[joueurEnCours] = 0;
    pointBonus15[joueurEnCours] = 0;
    pointBonus25[joueurEnCours] = 0;
    pointBonus50[joueurEnCours] = 0;
    pointBonus100[joueurEnCours] = 0;
    pointBonus150[joueurEnCours] = 0;
    pointBonus200[joueurEnCours] = 0;
    pointBonus250[joueurEnCours] = 0;
}
void resetAllBonus10() {
    pointBonus5[joueurEnCours] = 0;
    pointBonus15[joueurEnCours] = 0;
    pointBonus25[joueurEnCours] = 0;
    pointBonus50[joueurEnCours] = 0;
    pointBonus100[joueurEnCours] = 0;
    pointBonus150[joueurEnCours] = 0;
    pointBonus200[joueurEnCours] = 0;
    pointBonus250[joueurEnCours] = 0;
}
void resetAllBonus15() {
    pointBonus5[joueurEnCours] = 0;
    pointBonus10[joueurEnCours] = 0;
    pointBonus25[joueurEnCours] = 0;
    pointBonus50[joueurEnCours] = 0;
    pointBonus100[joueurEnCours] = 0;
    pointBonus150[joueurEnCours] = 0;
    pointBonus200[joueurEnCours] = 0;
    pointBonus250[joueurEnCours] = 0;
}
void resetAllBonus25() {
    pointBonus5[joueurEnCours] = 0;
    pointBonus10[joueurEnCours] = 0;
    pointBonus15[joueurEnCours] = 0;
    pointBonus50[joueurEnCours] = 0;
    pointBonus100[joueurEnCours] = 0;
    pointBonus150[joueurEnCours] = 0;
    pointBonus200[joueurEnCours] = 0;
    pointBonus250[joueurEnCours] = 0;
}
void resetAllBonus50() {
    pointBonus5[joueurEnCours] = 0;
    pointBonus10[joueurEnCours] = 0;
    pointBonus15[joueurEnCours] = 0;
    pointBonus25[joueurEnCours] = 0;
    pointBonus100[joueurEnCours] = 0;
    pointBonus150[joueurEnCours] = 0;
    pointBonus200[joueurEnCours] = 0;
    pointBonus250[joueurEnCours] = 0;
}
void resetAllBonus100() {
    pointBonus5[joueurEnCours] = 0;
    pointBonus10[joueurEnCours] = 0;
    pointBonus15[joueurEnCours] = 0;
    pointBonus25[joueurEnCours] = 0;
    pointBonus50[joueurEnCours] = 0;
    pointBonus150[joueurEnCours] = 0;
    pointBonus200[joueurEnCours] = 0;
    pointBonus250[joueurEnCours] = 0;
}
void resetAllBonus150() {
    pointBonus5[joueurEnCours] = 0;
    pointBonus10[joueurEnCours] = 0;
    pointBonus15[joueurEnCours] = 0;
    pointBonus25[joueurEnCours] = 0;
    pointBonus50[joueurEnCours] = 0;
    pointBonus100[joueurEnCours] = 0;
    pointBonus200[joueurEnCours] = 0;
    pointBonus250[joueurEnCours] = 0;
}
void resetAllBonus200() {
    pointBonus5[joueurEnCours] = 0;
    pointBonus10[joueurEnCours] = 0;
    pointBonus15[joueurEnCours] = 0;
    pointBonus25[joueurEnCours] = 0;
    pointBonus50[joueurEnCours] = 0;
    pointBonus100[joueurEnCours] = 0;
    pointBonus150[joueurEnCours] = 0;
    pointBonus250[joueurEnCours] = 0;
}
void resetAllBonus250() {
    pointBonus5[joueurEnCours] = 0;
    pointBonus10[joueurEnCours] = 0;
    pointBonus15[joueurEnCours] = 0;
    pointBonus25[joueurEnCours] = 0;
    pointBonus50[joueurEnCours] = 0;
    pointBonus100[joueurEnCours] = 0;
    pointBonus150[joueurEnCours] = 0;
    pointBonus200[joueurEnCours] = 0;
}

void TTRST(){   
    // Réinitialisation des scores
    for (int i = 0; i < 9; i++) { 
    scores[i] = 0; // Remise à zéro des scores pour éviter l'infinie
    }
    // Réinitialisation des bonus
    for (int i = 0; i < 9; i++) {
    pointBonus5[i] = 0;  // Remise à zéro du bonus pour éviter la croissance infinie
    }
    // Réinitialisation des bonus
    for (int i = 0; i < 9; i++) {
    pointBonus10[i] = 0;  // Remise à zéro du bonus pour éviter la croissance infinie
    }
    // Réinitialisation des bonus
    for (int i = 0; i < 9; i++) {
    pointBonus15[i] = 0;  // Remise à zéro du bonus pour éviter la croissance infinie
    }
    // Réinitialisation des bonus
    for (int i = 0; i < 9; i++) {
    pointBonus25[i] = 0;  // Remise à zéro du bonus pour éviter la croissance infinie
    }
    // Réinitialisation des bonus
    for (int i = 0; i < 9; i++) {
    pointBonus50[i] = 0;  // Remise à zéro du bonus pour éviter la croissance infinie
    }
    // Réinitialisation des bonus
    for (int i = 0; i < 9; i++) {
    pointBonus100[i] = 0;  // Remise à zéro du bonus pour éviter la croissance infinie
    }
    // Réinitialisation des bonus
    for (int i = 0; i < 9; i++) {
    pointBonus150[i] = 0;  // Remise à zéro du bonus pour éviter la croissance infinie
    }
    // Réinitialisation des bonus
    for (int i = 0; i < 9; i++) {
    pointBonus200[i] = 0;  // Remise à zéro du bonus pour éviter la croissance infinie
    }
    // Réinitialisation des bonus
    for (int i = 0; i < 9; i++) {
    pointBonus250[i] = 0;  // Remise à zéro du bonus pour éviter la croissance infinie
    }
  Serial.println("Scores réinitialisés !");
  Serial.println("Bonus réinitialisés !");
}

/*
void checkBonus() {
    for (int i = 0; i < NB_SCORES; i++) {
        if (scores[i] >= 1000) {
            Serial.print("Bonus débloqué pour le score ");
            Serial.print(i);
            Serial.print(" : ");
            Serial.println(scores[i]);
            // Ajoute ici toute autre action nécessaire (affichage sur écran, LED, son, etc.)
        }
    }
}
*/


//----------------------------------------------------------------------------------------------------------------------------------------------------------


void SonsAleatoires(){
  if (disableSonAnimation) { // Ne fait rien si désactivé
    return; 
  }
  if (disableLedAnimation) { // Ne fait rien si désactivé
    return;
  }
  int Son_aleatoire;
  Son_aleatoire = random(0 , 19);
  switch (Son_aleatoire) {

  case 0:
    if(millis()-Time18M>=Period18M){
      myDFPlayer.playMp3Folder(35);
      Time18M=millis();}
  case 1:
    if(millis()-Time18M>=Period18M){
      myDFPlayer.playMp3Folder(36);
      Time18M=millis();}
  case 2:    
    if(millis()-Time18M>=Period18M){      
      myDFPlayer.playMp3Folder(87);
      Time18M=millis();}
  case 3:    
    if(millis()-Time18M>=Period18M){      
      myDFPlayer.playMp3Folder(38);
      Time18M=millis();}
  case 4:    
    if(millis()-Time18M>=Period18M){      
      myDFPlayer.playMp3Folder(39);
      Time18M=millis();}
  case 5:    
    if(millis()-Time18M>=Period18M){     
      myDFPlayer.playMp3Folder(40);
      Time18M=millis();}
  case 6:
    if(millis()-Time18M>=Period18M){
      myDFPlayer.playMp3Folder(41);     
      Time18M=millis();}
  case 7:
    if(millis()-Time18M>=Period18M){
      myDFPlayer.playMp3Folder(42);
      Time18M=millis();}
  case 8:    
    if(millis()-Time18M>=Period18M){      
      myDFPlayer.playMp3Folder(43);
      Time18M=millis();}
  case 9:    
    if(millis()-Time18M>=Period18M){      
      myDFPlayer.playMp3Folder(44);
      Time18M=millis();}
  case 10:    
    if(millis()-Time18M>=Period18M){      
      myDFPlayer.playMp3Folder(45);
      Time18M=millis();}
  case 11:    
    if(millis()-Time18M>=Period18M){     
      myDFPlayer.playMp3Folder(46);
      Time18M=millis();}
  case 12:    
    if(millis()-Time18M>=Period18M){      
      myDFPlayer.playMp3Folder(47);
      Time18M=millis();}
  case 13:    
    if(millis()-Time18M>=Period18M){      
      myDFPlayer.playMp3Folder(48);
      Time18M=millis();}
  case 14:    
    if(millis()-Time18M>=Period18M){     
      myDFPlayer.playMp3Folder(49);
      Time18M=millis();}
  case 15:    
    if(millis()-Time18M>=Period18M){     
      myDFPlayer.playMp3Folder(24);
      Time18M=millis();}
  case 16:    
    if(millis()-Time18M>=Period18M){      
      myDFPlayer.playMp3Folder(25);
      Time18M=millis();}
  case 17:    
    if(millis()-Time18M>=Period18M){      
      myDFPlayer.playMp3Folder(26);
      Time18M=millis();}
  case 18:    
    if(millis()-Time18M>=Period18M){     
      myDFPlayer.playMp3Folder(28);
      Time18M=millis();}             
  }  
}

void Messages(){
  lcd.setCursor(0,2); 
  int Ms_aleatoire;
  Ms_aleatoire = random(0 , 10);
  switch (Ms_aleatoire) {

  case 0:
    if(millis()-Time2S>=Period2S){      
      lcd.print(F("     Bah, alors     "));
      Time2S=millis();}
      break;
  case 1:
    if(millis()-Time2S>=Period2S){
      lcd.print(F("  Ouvres les yeux   "));
      Time2S=millis();}
      break;
  case 2:    
    if(millis()-Time2S>=Period2S){      
      lcd.print(F("     Tu louches     "));
      Time2S=millis();}
      break;
  case 3:    
    if(millis()-Time2S>=Period2S){      
      lcd.print(F("   Vise la cible    "));
      Time2S=millis();}
      break;      
  case 4:    
    if(millis()-Time2S>=Period2S){      
      lcd.print(F("   Viser la lune    "));
      Time2S=millis();}
      break;      
  case 5:    
    if(millis()-Time2S>=Period2S){     
      lcd.print(F("      Tu dors       "));
      Time2S=millis();}
      break;      
  case 6:
    if(millis()-Time2S>=Period2S){
      lcd.print(F("    Tu es partie    "));     
      Time2S=millis();}
      break;      
  case 7:
    if(millis()-Time2S>=Period2S){
      lcd.print(F("     Tu es mort     "));
      Time2S=millis();}
      break;      
  case 8:    
    if(millis()-Time2S>=Period2S){      
      lcd.print(F("   Tu es en enfer   "));
      Time2S=millis();}
      break;      
  case 9:    
    if(millis()-Time2S>=Period2S){      
      lcd.print(F("   Reveilles toi    "));
      Time2S=millis();}
      break;               
  }  
}

