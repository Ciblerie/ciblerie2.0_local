
void MS2(){ //------------------------------------------------------------------------------------
  Serial.println(F("MS2"));
  Serial.println(F("MS2 , Ok pour le lancement du jeu"));

  Serial1.println("START_GAME");
  Serial.println("📨 Envoi à ESP32: START_GAME");

  Serial1.println("CONFIRMED_GAME");
  Serial.println("📨 Envoi à ESP32: CONFIRMED_GAME");

  indexgroupe = 6;  // Toujours revenir au groupe MS avant le début de chaque partie
  AcquisitionCapteurs();
  if (initialisation==true){InitGameMS2();}     
  if (partieEnCours==true){trtPartieEnCoursMS2();} 
  if (partieFinie==true){trtPartieFinieMS2();}
}
//---------------------------------------------FIN LOOP-------------------------------

void trtPartieFinieMS2(){   
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
    
void trtPartieEnCoursMS2(){

    FastLED.clear(); FastLED.show();
    Temporisation();
    EcranEnJeuMS();            
    while (statusCible1==HIGH && statusCible2==HIGH && statusCible3==HIGH && statusCible4==HIGH && statusCible5==HIGH && statusCible6==HIGH && statusCible7==HIGH && statusCible8==HIGH && statusCible9==HIGH && statusCible10==HIGH ){
      AcquisitionCapteurs();   
      PenaliteMS2();     
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
     fill_solid(leds, NUM_LEDS, CRGB::Red);  FastLED.show();
     myDFPlayer.playMp3Folder(1); delay(3000);
     FastLED.clear(); FastLED.show();
     resteEnCoursMS = 1;
     SMRAZ();
     GameOver();
     EcranEnJeuMS();
     GererInterruptionMS2();}

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
  GererInterruptionMS2();  
}

void PenaliteMS2() 
{
  if (!coursesCommencees)
  {
    EcranEnJeuMS();
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
      EcranEnJeuMS();
      GererInterruptionMS2();
      }
     else lcd.print(tempsrestant); 
    }         
}

void GererInterruptionMS2()
{
  if ( joueurEnCours == nbJoueurs2 && tourEnCoursMS == nbToursMS && resteEnCoursMS == 1 ){
    testKiller();
    coursesCommencees = false;
    coursesFinies = false;
    partieEnCours = false;
    partieFinie = true;
    SMRAZ();
  }
  else if (  joueurEnCours == nbJoueurs2 && resteEnCoursMS == 1 )
  {
    myDFPlayer.stop();
    testKiller();
    joueurEnCours = 1;            
    resteEnCoursMS = 1000000;
    tourEnCoursMS++;
    EcranTourSuivantMS();    
    myDFPlayer.playMp3Folder(30);   
    EcranJoueurSuivant();  
    lcd.clear();
   while (statusBoutonE==HIGH){
        AcquisitionCapteurs();
        printBigNum(21, 13, 0);
        printBigNum(joueurEnCours,17,0);
        lcd.setCursor(0,0);
        lcd.print("Tour  : "+ String(tourEnCoursMS));
        lcd.setCursor(0,2);
        lcd.print("Quand pret");         
        lcd.setCursor(8,3);
        lcd.print("Start --> OK");
        FastLED.clear(); FastLED.show();              
   }
   EcranGo();                      
  }
  else if ( resteEnCoursMS != 1 ){
    resteEnCoursMS--; 
  }  
  else
  {
    myDFPlayer.stop();
    testKiller();
    joueurEnCours++;
    resteEnCoursMS = 1000000;
    myDFPlayer.playMp3Folder(30);   
    EcranJoueurSuivant();  
    lcd.clear();
   while (statusBoutonE==HIGH){
        AcquisitionCapteurs();      
        printBigNum(21, 13, 0);
        printBigNum(joueurEnCours,17,0);
        lcd.setCursor(0,0);
        lcd.print("Tour  : "+ String(tourEnCoursMS));
        lcd.setCursor(0,2);
        lcd.print("Quand pret");        
        lcd.setCursor(8,3);
        lcd.print("Start --> OK");
        FastLED.clear(); FastLED.show();
   }
   EcranGo();    
  }  
}

void EcranInitialisationMS2()
{
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Nb joueurs : " + String(nbJoueurs2) + "      ");        
}

void InitGameMS2()
{
  FastLED.clear(); FastLED.show();
  myDFPlayer.stop();
  myDFPlayer.playMp3Folder(19);
  tourEnCoursMS = 1;
  resteEnCoursMS = 1000000;
  joueurEnCours = 1; 
  for(int i=1; i<=4; i++){
    scores[i] = 0;
    killer[1] = 0;
    levels[1] = 0;
    oldClassement[1] = 0;
    classement[1] = 0;
  }
  statusBoutonE = digitalRead(boutonE);
    
    if (nbJoueurs2 == 1){
       nbJoueurs2 = 1;
    }
    if (nbJoueurs2 != oldNbJoueurs){
      oldNbJoueurs = nbJoueurs2;
    }
    if (statusBoutonE==LOW){ 
        for (int i = 1; i <= nbJoueurs2 ; i++) {
          killer[i] = 1;         
       }
    }  
    initialisation = false;
    partieEnCours = true;
    EcranEnJeuMS();
    EcranGo();
}  

// ----------------------------------------------------------------------------------------------
// ----------------AFFICHAGE FIN DE PARTIE
// ----------------------------------------------------------------------------------------------
