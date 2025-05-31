
//----------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------AFFICHAGE FIN DE PARTIE
//----------------------------------------------------------------------------------------------------------------------------------------------------------

// TABLEAU DE SCORES
void ScoresFin(){

 Serial.println("\t");       
 ResultatDesScores.println("\t");      
 Serial.print("\t");
 
 tabScores[0]=("1ER : J" + String(classement[1])+ " : " + String(scores[classement[1]]));
 Serial.println("1ER : J" + String(classement[1])+ " : " + String(scores[classement[1]]));
 ResultatDesScores.println("1ER : J" + String(classement[1])+ " : " + String(scores[classement[1]]));
 Serial.print("\t");  
 tabScores[1]=("2EM : J" + String(classement[2])+ " : " + String(scores[classement[2]]));
 Serial.println("2EM : J" + String(classement[2])+ " : " + String(scores[classement[2]]));
 ResultatDesScores.println("2EM : J" + String(classement[2])+ " : " + String(scores[classement[2]]));
 Serial.print("\t");  
 tabScores[2]=("3EM : J" + String(classement[3])+ " : " + String(scores[classement[3]]));
 Serial.println("3EM : J" + String(classement[3])+ " : " + String(scores[classement[3]]));
 ResultatDesScores.println("3EM : J" + String(classement[3])+ " : " + String(scores[classement[3]]));
 Serial.print("\t"); 
 tabScores[3]=("4EM : J" + String(classement[4])+ " : " + String(scores[classement[4]]));
 Serial.println("4EM : J" + String(classement[4])+ " : " + String(scores[classement[4]]));
 ResultatDesScores.println("4EM : J" + String(classement[4])+ " : " + String(scores[classement[4]]));
 Serial.print("\t");
}
  
void affichageScores(int a){

  FastLED.clear();

 lcd.clear();
 for (int i=0;i<=3;i++){
   lcd.setCursor(0,i);
   lcd.print(tabScores[a]);   
   a++;   
   if (a>4){a=0;}
 }
 lcd1.clear();
 lcd1.setCursor(8,3);
 lcd1.print(F("Start --> OK"));
}

void affichageScoresJeu(int a){

  FastLED.clear();

 lcd.clear();
 for (int i=0;i<=3;i++){
   lcd1.setCursor(0,i);
   lcd1.print(tabScores[a]);   
   a++;   
   if (a>4){a=0;}
 }
}
 
//PROCEDURE PRINCIPALE de fin de partie

void AfficheFin(){
  
 myDFPlayer.playMp3Folder(20);
 int indexScrollScore=0;
 unsigned long currentMillis = millis();
 unsigned long previousMillis = millis();
 unsigned long period = 2000;  
 Temporisation();
 ScoresFin(); 
 while(statusBoutonE==HIGH){
//  while(statusBoutonE==LOW){
   currentMillis = millis();
   if (currentMillis - previousMillis >= period) {
     previousMillis = currentMillis;
     affichageScores(indexScrollScore);
     
     indexScrollScore++;
     if (indexScrollScore>0)
       {indexScrollScore=0;}   
   }
   AcquisitionCapteurs();     
  }   
  delay(500);  
    if(statusBoutonE==LOW){
      AcquisitionCapteurs();
      initialisation = true;
      delay(125);
    }
}

//---------------------------------------------------------------------------------------

//Fonction tri  bulle pour le classement des joueurs en fin de partie
void triclassement(){
//***********************************************************************************************
// classer classement[] = {0,0,0,0,0};int scores[] = {0,0,0,0,0};
// pour ne pas faire le tri plusieurs fois, sera mis  1  la fin du traitement, remis  0 au dpart de la partie suivante
// remplissage du tableau de classement
classement[1]=1;
classement[2]=2;
classement[3]=3;
classement[4]=4;
// tri  bulle
  do
    { // boucle do/while
    classement[0]=0; // sera utilis dans le tri comme flag de permutation
      for (int i = 1 ; i < 4 ; i++)
        { // on parcourt le tableau
          if (scores[classement[i]]<scores[classement[i+1]])
            { // si le score de l'lment est <  l'lment suivant, on permute
            classement[0]=classement[i];          // on stocke le premier lment
            classement[i]=classement[i+1];          // on remonte le suivant
            classement[i+1]=classement[0];          // on termine la permutation
            classement[0]=1;                // on passe le flag de permutation  1
            } // fin if
          } // fin for
    } 
  while (classement[0]==1); // tant qu'on a fait une permutation, on recommence.
//*******************************************************************************************************   
}

///////////////////////////////////////////////////////////////////////////////////////////////////////// code fournis ..................................

void testEnvoiESP32() {
    String pseudo = "JoueurTest";
    int score = 999;
    
    String jsonMessage = "{\"pseudo\": \"" + pseudo + "\", \"score\": " + String(score) + "}";
    Serial1.println(jsonMessage); // Envoi au WebSocket via Serial1

    // Affichage pour vérification
    Serial.println("Test - Données envoyées via Serial1 :");
    Serial.println(jsonMessage);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////// code fournis ..................................

