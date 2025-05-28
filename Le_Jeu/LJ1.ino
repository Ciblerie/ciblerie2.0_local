
void LJ1(){//------------------------------------------------------------------------------------
  Serial.println(F("LJ1"));
  Serial.println(F("LJ1 , Ok pour le lancement du jeu"));

  Serial1.println("START_GAME");
  Serial.println("📨 Envoi à ESP32: START_GAME");

  Serial1.println("CONFIRMED_GAME");
  Serial.println("📨 Envoi à ESP32: CONFIRMED_GAME");
  
  indexgroupe = 5;  // Toujours revenir au groupe LJ avant le début de chaque partie
  AcquisitionCapteurs();
  if (initialisation==true){InitGameLJ();}   
  if (partieEnCours==true){trtPartieEnCoursLJ();} 
  if (partieFinie==true){trtPartieFinieLJ();}
}
//---------------------------------------------FIN LOOP-------------------------------

void trtPartieFinieLJ(){
    FinGame();   
    while(killer[1]==1 || killer[2]==1 || killer[3]==1 || killer[4]==1 ){
      Serial.println("KILLER STATUS J1 " + String(killer[1]) + String(killer[2]) + String(killer[3]) + String(killer[4]));   
        for (int i = 1; i <= nbJoueurs ; i++){
          if (killer[i] == 1){
            joueurEnCours = i;
          }
        } 
    }
  partieFinie = false;
  partieEnCours = false;
  initialisation = true;
  oldNbJoueurs = 0;
  triclassement();
  AfficheFin();
}  
// ---------------------------------FIN trtPartieFinie ----------------------------------
   
void trtPartieEnCoursLJ()
{
    FastLED.clear(); FastLED.show();
    Temporisation();
    EcranEnJeuLJ();            
    while (statusCible1==HIGH && statusCible2==HIGH && statusCible3==HIGH && statusCible4==HIGH && statusCible5==HIGH && statusCible6==HIGH && statusCible7==HIGH && statusCible8==HIGH && statusCible9==HIGH && statusCible10==HIGH ){
      AcquisitionCapteurs();    
      PenaliteLJ();     
      if (partieFinie==true){
        delay(0); 
        break;
        }
      else {      
          killer[joueurEnCours] = 0;
      }        
    }

    statusCible1 = digitalRead(cible1);
    if (statusCible1 == LOW){
     coursesCommencees = false; 
     coursesFinies = false;                  
     fill_solid(leds, NUM_LEDS, CRGB::Red);  FastLED.show();
     myDFPlayer.playMp3Folder(1); delay(3000);
     FastLED.clear(); FastLED.show();
     resteEnCoursLJ = 1;
     SMRAZ();
     EcranEnJeuLJ();
     GererInterruptionLJ();} // 🔄 Passe au joueur suivant immédiatement 

    statusCible2 = digitalRead(cible2);
    if (statusCible2 == LOW){
     coursesCommencees = false; 
     coursesFinies = false;                        
     fill_solid(leds, NUM_LEDS, CRGB::Orange);  FastLED.show();
     myDFPlayer.playMp3Folder(2); delay(3000);
     FastLED.clear(); FastLED.show();
     scores[joueurEnCours] = scores[joueurEnCours]+5+pointBonus5[joueurEnCours];
     pointBonus5[joueurEnCours] = pointBonus5[joueurEnCours]+1;
     // Remise à zéro des autres bonus
     resetAllBonus5();  // Appel à la fonction de réinitialisation
     Serial.println(5);}

    statusCible3 = digitalRead(cible3);
    if (statusCible3 == LOW){
     coursesCommencees = false; 
     coursesFinies = false;      
     fill_solid(leds, NUM_LEDS, CRGB::Yellow);  FastLED.show();
     myDFPlayer.playMp3Folder(3); delay(3000);
     FastLED.clear(); FastLED.show();
     scores[joueurEnCours] = scores[joueurEnCours]+10+pointBonus10[joueurEnCours];
     pointBonus10[joueurEnCours] = pointBonus10[joueurEnCours]+2;
     // Remise à zéro des autres bonus
     resetAllBonus10();  // Appel à la fonction de réinitialisation
     Serial.println(10);}

    statusCible4 = digitalRead(cible4);
    if (statusCible4 == LOW){
     coursesCommencees = false; 
     coursesFinies = false;                              
     fill_solid( leds, NUM_LEDS, CRGB::Green);  FastLED.show();
     myDFPlayer.playMp3Folder(5); delay(3000);
     FastLED.clear (); FastLED.show();
     scores[joueurEnCours] = scores[joueurEnCours]+15+pointBonus15[joueurEnCours];
     pointBonus15[joueurEnCours] = pointBonus15[joueurEnCours]+3;
     // Remise à zéro des autres bonus
     resetAllBonus15();  // Appel à la fonction de réinitialisation
     Serial.println(15);}   

    statusCible5 = digitalRead(cible5);
    if (statusCible5 == LOW){
     coursesCommencees = false; 
     coursesFinies = false;
     fill_solid(leds, NUM_LEDS, CRGB::Blue);  FastLED.show();
     myDFPlayer.playMp3Folder(8); delay(3000);
     FastLED.clear(); FastLED.show();
     scores[joueurEnCours] = scores[joueurEnCours]+25+pointBonus25[joueurEnCours];
     pointBonus25[joueurEnCours] = pointBonus25[joueurEnCours]+4;
     // Remise à zéro des autres bonus
     resetAllBonus25();  // Appel à la fonction de réinitialisation
     Serial.println(25);}    

    statusCible6 = digitalRead(cible6);
    if (statusCible6 == LOW){
     coursesCommencees = false; 
     coursesFinies = false;
     Cinquante();               
     scores[joueurEnCours] = scores[joueurEnCours]+50+pointBonus50[joueurEnCours];
     pointBonus50[joueurEnCours] = pointBonus50[joueurEnCours]+5;
     // Remise à zéro des autres bonus
     resetAllBonus50();  // Appel à la fonction de réinitialisation
     Serial.println(50);}

    statusCible7 = digitalRead(cible7);
    if (statusCible7 == LOW){
     coursesCommencees = false; 
     coursesFinies = false;
     Cent();
     scores[joueurEnCours] = scores[joueurEnCours]+100+pointBonus100[joueurEnCours];
     pointBonus100[joueurEnCours] = pointBonus100[joueurEnCours]+10;
     // Remise à zéro des autres bonus
     resetAllBonus100();  // Appel à la fonction de réinitialisation
     Serial.println(100);}

    statusCible8 = digitalRead(cible8);
    if (statusCible8 == LOW){
     coursesCommencees = false; 
     coursesFinies = false;
     CentCinquante();
     scores[joueurEnCours] = scores[joueurEnCours]+150+pointBonus150[joueurEnCours];
     pointBonus150[joueurEnCours] = pointBonus150[joueurEnCours]+15;
     // Remise à zéro des autres bonus
     resetAllBonus150();  // Appel à la fonction de réinitialisation
     Serial.println(150);}

    statusCible9 = digitalRead(cible9);
    if (statusCible9 == LOW){
     coursesCommencees = false; 
     coursesFinies = false;
     DeuxCent();
     scores[joueurEnCours] = scores[joueurEnCours]+200+pointBonus200[joueurEnCours];
     pointBonus200[joueurEnCours] = pointBonus200[joueurEnCours]+20;
     // Remise à zéro des autres bonus
     resetAllBonus200();  // Appel à la fonction de réinitialisation
     Serial.println(200);}

    statusCible10 = digitalRead(cible10);
    if (statusCible10 == LOW){
     coursesCommencees = false; 
     coursesFinies = false;
     DeuxCentCinquante();
     scores[joueurEnCours] = scores[joueurEnCours]+250+pointBonus250[joueurEnCours];
     pointBonus250[joueurEnCours] = pointBonus250[joueurEnCours]+25;
     // Remise à zéro des autres bonus
     resetAllBonus250();  // Appel à la fonction de réinitialisation
     Serial.println(250);}           

    else {
      killer[joueurEnCours] = 0;
      }
  SMRAZ();        
  GererInterruptionLJ();
}

void PenaliteLJ() 
{ 
  if (!coursesCommencees)
  {
    EcranEnJeuLJ();
    myDFPlayer.playMp3Folder(19);
    lcd.setCursor(11,3);
    lcd.print("TR: ");
    coursesCommencees = true;
    // Réinitialisation des couleurs et états
    memset(colorIndexes, 0, sizeof(colorIndexes)); // Réinitialise tous les index de couleur
    memset(lastColorChanges, 0, sizeof(lastColorChanges));
    startTime = millis();
    tempsGenere = false;  // ✅ Réinitialise l'état pour la prochaine manche
  }
  if(!coursesFinies && coursesCommencees) {
    if (!tempsGenere) {
      TempsAleatoireLJ = random(1, 6);  // ⏳ Temps entre 1 et 5 secondes
      Period1LJ = TempsAleatoireLJ * 1000;
      Period2LJ = TempsAleatoireLJ * 1000;
      tempsGenere = true;  // ✅ Marque que le temps a été généré
      // ✅ Affichage immédiat du temps restant pour éviter qu'il ne soit manquant
      lcd.setCursor(15,3);
      lcd.print(TempsAleatoireLJ);
      // 🎨 Affichage du code couleur correspondant
      if (TempsAleatoireLJ == 1) fill_solid(leds, NUM_LEDS, CRGB::Red); // 🔴 Rouge
      else if (TempsAleatoireLJ >= 2 && TempsAleatoireLJ <= 5) { 
        int index = TempsAleatoireLJ - 2;
        fill_solid(leds, NUM_LEDS, colorArrays[index][colorIndexes[index]]); // 🟠 Orange <- 🟡 Jaune <- 🟢 Vert <- 🔵 Bleu ( Sens de décomptage )
        lastColorChanges[index] = millis();
      }
      FastLED.show();
      Moteur();  // ✅ Activation immédiate
      // ✅ Démarre le délai non bloquant pour éteindre les LEDs après 1 seconde
      ledsAllumeesMillis = millis();
      ledsAllumees = true;
    }
     // ✅ Éteindre les LEDs après 1 seconde sans bloquer le code
     if (ledsAllumees && millis() - ledsAllumeesMillis >= 500) {
      FastLED.clear(); FastLED.show(); // ⭕ Éteint les LEDs après 1 seconde
      ledsAllumees = false;
     }
    // ✅ Changement de couleur toutes les secondes si TempsAleatoireLJ entre 2 et 5
    if (TempsAleatoireLJ >= 2 && TempsAleatoireLJ <= 5) {
      int index = TempsAleatoireLJ - 2;
      if (millis() - lastColorChanges[index] >= 1000) {
        colorIndexes[index] = (colorIndexes[index] + 1) % colorSizes[index];
        fill_solid(leds, NUM_LEDS, colorArrays[index][colorIndexes[index]]); //  🔵 Bleu -> 🟢 Vert -> 🟡 Jaune -> 🟠 Orange ( Sens réel )
        FastLED.show();
        lastColorChanges[index] = millis();
      }
    }
     // ⏳ Temps écoulé, on passe au joueur/tour suivant
     lcd.setCursor(15,3);
     tempsrestant = TempsAleatoireLJ - ( millis() - startTime) / 1000;
     if(tempsrestant < 0)
     {
      coursesFinies = true;
      SMRAZTP();
      lcd.clear();
      clignotementLED(1);
      lcd.setCursor(3, 1);
      lcd.print("Temps ecoule !");
      clignotementLED(1);
      myDFPlayer.playMp3Folder(1);
      clignotementLED(1);
      Messages();
      clignotementLED(1);
      fill_solid(leds, NUM_LEDS, CRGB::Red);  FastLED.show();
      delay(2000);
      lcd.clear();
      FastLED.clear(); FastLED.show();
      coursesCommencees = false;
      coursesFinies = false;
      resteEnCoursLJ = 1;
      // Remise à zéro des autres bonus
      resetAllBonus0();  // Appel à la fonction de réinitialisation
      SMRAZ();
      EcranEnJeuLJ();
      GererInterruptionLJ();  // 🔄 Passe au joueur suivant immédiatement  
     }
     else lcd.print(tempsrestant);
    }         
}

void GererInterruptionLJ()
{
  if ( joueurEnCours == nbJoueurs && tourEnCoursLJ == nbToursLJ && resteEnCoursLJ == 1 ){
    testKiller();
    coursesCommencees = false;
    coursesFinies = false;
    partieEnCours = false;
    partieFinie = true;
    SMRAZ();
  }
  else if (  joueurEnCours == nbJoueurs && resteEnCoursLJ == 1 )
  {
    myDFPlayer.stop();
    testKiller();
    joueurEnCours = 1;            
    resteEnCoursLJ = 1000000;
    tourEnCoursLJ++;
    EcranTourSuivantLJ();    
    myDFPlayer.playMp3Folder(30);   
    EcranJoueurSuivant();  
    lcd.clear();
   while (statusBoutonE==HIGH){
        AcquisitionCapteurs();
        printBigNum(21, 13, 0);
        printBigNum(joueurEnCours,17,0);
        lcd.setCursor(0,0);
        lcd.print("Tour  : "+ String(tourEnCoursLJ));
        lcd.setCursor(0,2);
        lcd.print("Quand pret");         
        lcd.setCursor(8,3);
        lcd.print("Start --> OK");
        FastLED.clear(); FastLED.show();             
   }
   EcranGo();                      
  }
  else if ( resteEnCoursLJ != 1 ){
    resteEnCoursLJ--; 
  }  
  else
  {
    myDFPlayer.stop();
    testKiller();
    joueurEnCours++;
    resteEnCoursLJ = 1000000;
    EcranTourSuivantLJ();    
    myDFPlayer.playMp3Folder(30);   
    EcranJoueurSuivant();  
    lcd.clear();
   while (statusBoutonE==HIGH){
        AcquisitionCapteurs();      
        printBigNum(21, 13, 0);
        printBigNum(joueurEnCours,17,0);
        lcd.setCursor(0,0);
        lcd.print("Tour  : "+ String(tourEnCoursLJ));
        lcd.setCursor(0,2);
        lcd.print("Quand pret");        
        lcd.setCursor(8,3);
        lcd.print("Start --> OK");
        FastLED.clear(); FastLED.show();
   }
   EcranGo();    
  }  
}

void EcranEnJeuLJ()
{
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
                                                         
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tour  : "+ String(tourEnCoursLJ)); // +"  Reste : " + String(resteEnCoursLJ));
  Serial.println("Tour  : "+ String(tourEnCoursLJ));
  lcd.setCursor(0,3);
  lcd.print("Joueur: " + String(joueurEnCours));
  Serial.println("Joueur: " + String(joueurEnCours));
  
  String scorestring = String(scores[joueurEnCours]);
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

void EcranTourSuivantLJ()
{
  EcranScores1();
  lcd.clear();
  printBigNum(31, 2, 1);
  printBigNum(26, 5, 1);
  printBigNum(32, 8, 1);
  printBigNum(29, 11, 1); 
  printBigNum(tourEnCoursLJ,15,1);
  delay(2000);
  EcranScores1();
}

void EcranInitialisationLJ()
{
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Nb joueurs : " + String(nbJoueurs) + "      ");        
}

void InitGameLJ()
{
  FastLED.clear(); FastLED.show();
  myDFPlayer.stop();
  myDFPlayer.playMp3Folder(19);
  tourEnCoursLJ = 1;
  resteEnCoursLJ = 1000000;
  joueurEnCours = 1;
  for(int i=1; i<=4; i++){
    scores[i] = 0;
    killer[1] = 0;
    levels[1] = 0;
    oldClassement[1] = 0;
    classement[1] = 0;
  }
  statusBoutonE = digitalRead(boutonE);
    
    if (nbJoueurs == 1){
       nbJoueurs = 1;
    }
    if (nbJoueurs != oldNbJoueurs){
      oldNbJoueurs=nbJoueurs;
    }
    if (statusBoutonE==LOW){ 
        for (int i = 1; i <= nbJoueurs ; i++) {
          killer[i] = 1;         
       }
    }  
    initialisation = false;
    partieEnCours = true;
    EcranEnJeu();
    EcranGo();
}

// ----------------------------------------------------------------------------------------------
// ----------------AFFICHAGE FIN DE PARTIE
// ----------------------------------------------------------------------------------------------
