
void CPT1(){ //------------------------------------------------------------------------------------
  Serial.println(F("CPT1"));
  Serial.println(F("CPT1 , Ok pour le lancement du jeu"));

  Serial1.println("START_GAME");
  Serial.println("📨 Envoi à ESP32: START_GAME");

  Serial1.println("CONFIRMED_GAME");
  Serial.println("📨 Envoi à ESP32: CONFIRMED_GAME");

  AcquisitionCapteurs();
  if (initialisation==true){InitGameCPT();}   
  if (partieEnCours==true){trtPartieEnCoursCPT();} 
  if (partieFinie==true){trtPartieFinieCPT();}
}
//---------------------------------------------FIN LOOP-------------------------------

void trtPartieFinieCPT(){   
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
    
void trtPartieEnCoursCPT(){

    FastLED.clear(); FastLED.show();
    Temporisation();
    EcranEnJeuMS();            
    while (statusCible1==HIGH && statusCible2==HIGH && statusCible3==HIGH && statusCible4==HIGH && statusCible5==HIGH && statusCible6==HIGH && statusCible7==HIGH && statusCible8==HIGH && statusCible9==HIGH && statusCible10==HIGH ){
      AcquisitionCapteurs();    
      PenaliteMS();     
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
     resteEnCoursMS = 1;
     SMRAZ();
     GameOver();
     EcranEnJeuMS();
     partieFinie = true;}

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
  GererInterruptionCPT();  
}

void PenaliteCPT() 
{ 
  if (!coursesCommencees)
  {
    EcranEnJeuCPT();
    Moteur();
    myDFPlayer.playMp3Folder(19);
    lcd.setCursor(11,3);
    lcd.print("TR: ");
    coursesCommencees = true;
    startTime = millis();
  }      
  if(!coursesFinies && coursesCommencees)
    {
     lcd.setCursor(15,3);
     tempsrestant = tempstotalL - ( millis() - startTime) / 1000;
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
      resteEnCoursMS = 1;
      // Remise à zéro des autres bonus
      resetAllBonus0();  // Appel à la fonction de réinitialisation
      SMRAZ();
      GameOver();
      EcranEnJeuCPT();
      partieFinie = true;
      }
     else lcd.print(tempsrestant); 
    }         
}

void GererInterruptionCPT()
{
  if ( joueurEnCours == nbJoueurs && tourEnCoursCPT == nbToursMS && resteEnCoursCPT == 1 ){
    testKiller();
    coursesCommencees = false;
    coursesFinies = false;
    partieEnCours = false;
    partieFinie = true;
    SMRAZ();
  }
  else if (  joueurEnCours == nbJoueurs && resteEnCoursCPT == 1 )
  {
    myDFPlayer.stop();
    testKiller();
    joueurEnCours = 1;            
    resteEnCoursCPT = 1000000;
    tourEnCoursCPT++;
    EcranTourSuivantCPT();    
    myDFPlayer.playMp3Folder(30);   
    EcranJoueurSuivant();  
    lcd.clear();
   while (statusBoutonE==HIGH){
        AcquisitionCapteurs();
        printBigNum(21, 13, 0);
        printBigNum(joueurEnCours,17,0);
        lcd.setCursor(0,0);
        lcd.print("Tour  : "+ String(tourEnCoursCPT));
        lcd.setCursor(0,2);
        lcd.print("Quand pret");         
        lcd.setCursor(8,3);
        lcd.print("Start --> OK");
        FastLED.clear(); FastLED.show();              
   }
   EcranGo();                      
  }
  else if ( resteEnCoursCPT != 1 ){
    resteEnCoursCPT--; 
  }  
  else
  {
    myDFPlayer.stop();
    testKiller();
    joueurEnCours++;
    resteEnCoursCPT = 1000000;
    myDFPlayer.playMp3Folder(30);   
    EcranJoueurSuivant();  
    lcd.clear();
   while (statusBoutonE==HIGH){
        AcquisitionCapteurs();      
        printBigNum(21, 13, 0);
        printBigNum(joueurEnCours,17,0);
        lcd.setCursor(0,0);
        lcd.print("Tour  : "+ String(tourEnCoursCPT));
        lcd.setCursor(0,2);
        lcd.print("Quand pret");        
        lcd.setCursor(8,3);
        lcd.print("Start --> OK");
        FastLED.clear(); FastLED.show();
   }
   EcranGo();    
  }  
}

void EcranEnJeuCPT(){
  
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
    else if (scorestring.length()==3){
      String centaine = String(scorestring.charAt(0));
      printBigNum(centaine.toInt(), 11, 1);
      String dizaine = String(scorestring.charAt(1));
      printBigNum(dizaine.toInt(), 14, 1);
      String unite = String(scorestring.charAt(2));
      printBigNum(unite.toInt(), 17, 1);
    }    
    else if (scorestring.length()==2){
      String dizaine = String(scorestring.charAt(0));
      printBigNum(dizaine.toInt(), 14, 1);
      String unite = String(scorestring.charAt(1));
      printBigNum(unite.toInt(), 17, 1);
    }    
    else{
      String unite = String(scorestring.charAt(0));
      printBigNum(0, 14, 1);
      printBigNum(unite.toInt(), 17, 1);     
    }         
}

void EcranTourSuivantCPT()
{
  EcranScores1();
  lcd.clear();
  printBigNum(31, 2, 1);
  printBigNum(26, 5, 1);
  printBigNum(32, 8, 1);
  printBigNum(29, 11, 1); 
  printBigNum(tourEnCoursCPT,15,1);
  delay(20);
  EcranScores1();
}

void EcranInitialisationCPT()
{
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Nb joueurs : " + String(nbJoueurs) + "      ");        
}

void InitGameCPT()
{
  FastLED.clear(); FastLED.show();
  myDFPlayer.stop();
  myDFPlayer.playMp3Folder(19);
  tourEnCoursCPT = 1;
  resteEnCoursCPT = 1000000;
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
    EcranEnJeuCPT();
    EcranGo();
}   

// ----------------------------------------------------------------------------------------------
// ----------------AFFICHAGE FIN DE PARTIE
// ----------------------------------------------------------------------------------------------
