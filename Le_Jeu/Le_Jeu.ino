
// Le 02.05.22 à 8h "OK" le 10.09.22 à 17h50 sur le bureau
// Original à modifier si les test son OK sur celui des TEST
// Ok le 16.04.25 à 19h - Code 100% fonctionnel

// Mode ARCADE + ESP32 = ici c'est = Arduino méga

// ==========================
// DEBUT DU PROGRAMME DES LCD
// ==========================

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
LiquidCrystal_I2C lcd1(0x26,20,4);
unsigned long previousMillis = 0;
const long interval = 180000;
bool isMainMenu = false;
bool isBacklightOn = true;

// =============================
// DEBUT DU PROGRAMME DU PCA9685
// =============================

#include "Adafruit_PWMServoDriver.h"
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
#define MIN_PULSE_WIDTH 600
#define MAX_PULSE_WIDTH 2600
#define FREQUENCY 50
const int NUM_SERVOS = 16;
uint8_t servo1 = 0;
uint8_t servo2 = 1;
uint8_t servo3 = 2;
uint8_t servo4 = 3;
uint8_t servo5 = 4;
uint8_t servo6 = 5;
uint8_t servo7 = 6;
uint8_t servo8 = 7;
uint8_t servo9 = 8;
uint8_t servo10 = 9;
uint8_t servo11 = 10;
uint8_t servo12 = 11;
uint8_t servo13 = 12;
uint8_t servo14 = 13; 
uint8_t servo15 = 14; 
uint8_t servo16 = 15;

// =============================================
// DEBUT DU PROGRAMME DU MP3 - MINI-MP3 DFROBOT2
// =============================================

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mySoftwareSerial (10, 11);
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
// Définir la variable volume
int volume = 10; // Volume initial (entre 0 et 30)
bool inIntensitySon = false; // Variable pour suivre le volume
bool disableSonAnimation = false;  // Variable pour désactiver SonAleatoire()

// ==================================================
// DEBUT DU PROGRAMME DU LECTEUR DE CARTE SD - VMA304
// ==================================================

#include "SPI.h"
#include "SD.h"
#include <SPI.h>
#include <SD.h>
const byte SDCARD_CS_PIN = 53;
Sd2Card CarteSD;
SdVolume VolumeCarteSD;
uint32_t volumesize;
// Déclaration de la carte SD
File ResultatDesScores;
File fichier;
File myFile;
File root;

// ============================
// DEBUT DU PROGRAMME DU DS3231
// ============================


#include <DS3231.h>
#include <Wire.h>
DS3231  rtc (SDA, SCL);

char NOM_J;
char J1="Monday";
char J2="Tuesday";
char J3="Wednesday";
char J4="Thursday";
char J5="Friday";
char J6="Saturday";
char J7="Sunday";

char NOM_M;

// ============================================
// DEBUT DU PROGRAMME DE LA BANDE LED - DPL8806
// ============================================

#include <FastLED.h>
#define NUM_LEDS 48
#define DATA_PIN 8
#define CLOCK_PIN 9
CRGB leds[NUM_LEDS];
#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif
//#define BRIGHTNESS  255
int brightness = 250; // 0; //100; // Luminosité initiale (0 à 255) = Luminosité par défaut
bool inIntensityMode = false; // Variable pour suivre le mode Intensité
bool disableLedAnimation = false;  // Variable pour désactiver CodeLedAleatoire()

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;
extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

// ============================================
// DEBUT DU PROGRAMME DE LA GESTION DES BOUTONS
// ============================================

int ButtonDelay = 50;
int ButtonCode = 0;
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
int read_LCD_buttons()
{
  adc_key_in = analogRead(A0);
  if (adc_key_in > 900)  return btnNONE;
  if (adc_key_in < 110)  return btnSELECT;
  if (adc_key_in < 250)  return btnRIGHT;
  if (adc_key_in < 450)  return btnDOWN;
  if (adc_key_in < 650)  return btnUP;
  if (adc_key_in < 850)  return btnLEFT;
  return btnNONE;
}
int boutonE = A0; // Entrer ou Valider
int boutonG = 3; // Gauche
int boutonD = 2; // Droit
bool statusBoutonE;
bool statusBoutonG;
bool statusBoutonD;

// ===========================
// DEBUT DU PROGRAMME NRF24L01
// ===========================

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CE_PIN 48
#define CSN_PIN 49
RF24 radio(CE_PIN, CSN_PIN);
const byte adresse[6] = "00001";  // Adresse commune

// ===============================================
// Définir les broches pour la communication série
// ===============================================

#define RX_PIN 18
#define TX_PIN 19

// ============================================
// DEBUT DU PROGRAMME POUR LES AUTRES VARIABLES
// ============================================

int LEDV = 2;
int LED13 = 13;

bool partieDemarree = false; // Variable pour indiquer si la partie a démarrée
//String groupeSelectionne; // Dans "Communications"
String groupeSelectionne = ""; // Variable globale pour stocker le groupe sélectionné

// Groupes de scores
const char* groupes[] = {"F", "SP", "P", "C", "L", "LJ", "MS" , "CPT"};
const int nombreGroupes = 8;
// F=0, SP=1, P=2, C=3, L=4, LJ=5, MS=6
int indexgroupe = 0; // Par défaut, groupe "F" = "Facile"
// Déclaration après la liste des groupes
//const char* groupeSelectionne = groupes[indexgroupe];
bool confirmationSuppression = false;  // Variable pour gérer la confirmation de suppression
bool inAffichageScores = false; // Variable pour suivre les Scores
bool disableAffichageScores = false;  // Variable pour désactiver SonAleatoire() et LedAléatoires()
bool infosAffichees = false; // Flag pour éviter l'affichage multiple
// Variables pour la navigation
//bool afficherMenu = true;  // Garde l'affichage actif
// Déclaration du meilleur score global
//int meilleurScore = 0;
//bool nouveauRecord = false;  // 🔁 Pour savoir si on affiche le pseudo ou non
//bool record_annonce = false;  // Déclaration globale de la variable
bool sortie = false;
//int mode = 0; // ou une autre valeur initiale adaptée à ton système 

unsigned int ScreenNumber = 0;
unsigned long temps = 0;
int Counterseconde = 00;
int PreCounterseconde = 0;
int DelayBP = 100;
int counter = 0;

long randomNumber;
int randDelai;
int randetatsetRegisterPin;

// Gestion des cibles
int cible1 = 22; // 0 Point
int cible2 = 24; // 5 Points
int cible3 = 26; // 10 Points 
int cible4 = 28; // 15 Points
int cible5 = 30; // 25 Points
int cible6 = 32; // 50 Points
int cible7 = 34; // 100 Points
int cible8 = 36; // 150 Points
int cible9 = 38; // 200 Points
int cible10 = 40; // 250 Points
bool statusCible1;
bool statusCible2;
bool statusCible3;
bool statusCible4;
bool statusCible5;
bool statusCible6;
bool statusCible7;
bool statusCible8;
bool statusCible9;
bool statusCible10;

//variables pour la gestion du jeu

int oldNbJoueurs = 0;
int joueurEnCours = 1;
int nbJoueurs = 1;
int nbJoueurs2 = 2;
int nbJoueurs3 = 3;
int nbJoueurs4 = 4;
int oldCible = 1;
int resteEnCours = 3;
int resteEnCoursLJ = 1000000;
int resteEnCoursMS = 1000000;
int resteEnCoursCPT = 1000000;
int tourEnCours = 1;
int tourEnCoursLJ = 1;
int tourEnCoursMS = 1;
int tourEnCoursCPT = 1;
int nbTours = 3;
int nbToursLJ = 3;
int nbToursMS = 1;
int nbToursCPT = 1;

//int score = 0;
int scoreListSize = 0;
String scoreList[20];
boolean isShowScore = false;
bool bonusAttribue = false;  // Indicateur pour ne pas attribuer le bonus plusieurs fois
//#define BTN_START A0  // Bouton pour démarrer une nouvelle partie
//const int NB_SCORES = 9;
//unsigned long scores[NB_SCORES] = {0,0,0,0,0,0,0,0,0};
//unsigned long scores[9] = {0}; // Initialise tous les scores à 0
//int classement[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8}; // Assure un classement correct
//String tabScores[9];
String tabScores[8];
unsigned long scores[] = {0,0,0,0,0,0,0,0,0};
int tauxReussite[] = {0,0,0,0,0,0,0,0,0};
int oldClassement[] = {0,0,0,0,0,0,0,0,0};
int classement[] = {0,0,0,0,0,0,0,0,0};

int pointBonus[] = {0, 0, 0, 0, 0};
bool premiereTouche[5] = {true};  // Permet de savoir si c'est la première touche du joueur
unsigned long dernierTempsTouch[5] = {0};  // Stocke le temps de la dernière touche
// Déclaration des variables pour les points bonus
int pointBonus0[5] = {0, 0, 0, 0, 0};
int pointBonus5[5] = {0, 0, 0, 0, 0};
int pointBonus10[5] = {0, 0, 0, 0, 0};
int pointBonus15[5] = {0, 0, 0, 0, 0};
int pointBonus25[5] = {0, 0, 0, 0, 0};
int pointBonus50[5] = {0, 0, 0, 0, 0};
int pointBonus100[5] = {0, 0, 0, 0, 0};
int pointBonus150[5] = {0, 0, 0, 0, 0};
int pointBonus200[5] = {0, 0, 0, 0, 0};
int pointBonus250[5] = {0, 0, 0, 0, 0};

boolean killer[] = {0,0,0,0,0,0,0,0,0};
int levels[] = {0,0,0,0,0,0,0,0,0};
int currentIndexMenu = 0;
boolean Finleds = 1;
boolean initialisation = 1;
boolean partieEnCours = 0;
boolean partieFinie = 0;
boolean RetourMenu = 0;
boolean initialisationLJ = 1;
boolean partieEnCoursLJ = 0;
boolean partieFinieLJ = 0;
boolean RetourMenuLJ = 0;
boolean initialisationMS = 1;
boolean partieEnCoursMS = 0;
boolean partieFinieMS = 0;
boolean RetourMenuMS = 0;
boolean initialisationJ = 1;
boolean ReglagesenCours = 0;
boolean ReglagesFinie = 0;
boolean RetourMenuJ = 0;
boolean eclairage = 0;
float tempsrestant;
bool coursesCommencees = false;
bool coursesFinies = false;
bool debugMode=false;
int delaiTemporisation = 100;

float startTime;

//Facile
int Period1F, Period2F;
unsigned long Time1F, Time2F;
//Semi-Pro
int Period1SP, Period2SP;
unsigned long Time1SP, Time2SP;
//Pro
int Period1P, Period2P;
unsigned long Time1P, Time2P;
//Champion
int Period1C, Period2C;
unsigned long Time1C, Time2C;
//Légendaire
int Period1L, Period2L;
unsigned long Time1L, Time2L;

//Temps Aléatoire
int TA1, TA2;
unsigned long Time1A, Time2A;

///////////////////////////////////////////

// TEST A FAIRE EN REEL POUR GERER LE TEMPS

//Facile
int tempstotalF;
//Semi-Pro
int tempstotalSP;
//Pro
int tempstotalP;
//Champion
int tempstotalC;
//Légendaire
int tempstotalL;

int PeriodPose;
unsigned long TimePose;
int Period3S;
unsigned long Time3S;
int Period18M;
unsigned long Time18M;
int Period1S;
unsigned long Time1S;
int Period2S;
unsigned long Time2S;

unsigned long currentTime=0;
unsigned long previousTime=0;

// Temps de base - "Le Jeu"
int Temps;
unsigned long Time1, Time2;
int Period1, Period2;
int TempsLJ = 2;
int TempsAleatoire;
// Temps Aléatoire
int Period1LJ, Period2LJ;
unsigned long Time1LJ, Time2LJ;
// Temps aléatoire "Le Jeu"
int TempsAleatoireLJ;
// ✅ Empêche de générer un nouveau temps en boucle
bool tempsGenere = false;
// Variables pour le délai non bloquant des LEDs
unsigned long ledsAllumeesMillis = 0;  
bool ledsAllumees = false;
// bool ledsAllumees = true; // Indique si les LEDs sont allumées ou non
// Variables pour le changement de couleur non bloquant
int colorIndex = 0; // Index de couleur actuel
unsigned long lastColorChange = 0;
// Ajout de variables pour gérer le changement de couleur séparément
bool colorChangeDone = false; // ✅ Empêche la répétition
bool colorSequenceActive = false; // ✅ Active/Désactive la séquence
// Variables pour le changement de couleur (case 5)
// Tableau des couleurs dans l'ordre souhaité
// Définition des couleurs pour chaque case
//CRGB colorsR[] = {CRGB::Red}; // 🔴 Rouge
CRGB colorsO[] = {CRGB::Orange, CRGB::Red}; // 🟠 Orange
CRGB colorsJ[] = {CRGB::Yellow, CRGB::Orange, CRGB::Red}; // 🟡 Jaune
CRGB colorsV[] = {CRGB::Green, CRGB::Yellow, CRGB::Orange, CRGB::Red}; // 🟢 Vert
CRGB colorsB[] = {CRGB::Blue, CRGB::Green, CRGB::Yellow, CRGB::Orange, CRGB::Red}; // 🔵 Bleu
CRGB colorsW[] = {CRGB::White, CRGB::Blue, CRGB::Green, CRGB::Yellow, CRGB::Orange, CRGB::Red}; // Blanc
// Variables de gestion des couleurs
int colorIndexes[] = {0, 0, 0, 0, 0}; // Indexes pour Orange, Jaune, Vert, Bleu
CRGB* colorArrays[] = {colorsO, colorsJ, colorsV, colorsB, colorsW}; // Pointeurs vers les tableaux de couleurs
int colorSizes[] = {2, 3, 4, 5, 6}; // Nombre de couleurs par tableau
unsigned long lastColorChanges[] = {0, 0, 0, 0, 0, 0}; // Dernière mise à jour des couleurs


uint8_t custChar[8][8] = {
{
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
},// Small top line - 0
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
},// Small bottom line - 1
{
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
},// Small lines top and bottom -2
{
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
}, // -3
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B01111,
  B00111
},// Left bottom chamfer full - 4
{
  B11100,
  B11110,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
},// Right top chamfer full -5
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11110,
  B11100
},// Right bottom chamfer full -6
{
  B00111,
  B01111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
},// Left top chamfer full -7 
};

uint8_t bigNums[38][6] = {
  {7, 0, 5, 4, 1, 6}, //0
  {0, 5, 254, 1, 255, 1},     //1
  {0, 0, 5, 4, 2, 2},         //2
  {3, 3, 5, 2, 2, 6},         //3
  {4, 1, 5, 254, 254, 255},   //4
  {255, 3, 3, 2, 2, 6},       //5 
  {7, 3, 3, 4, 2, 6},         //6 
  {0, 0, 5, 254, 7, 254},     //7 
  {7, 3, 5, 4, 2, 6},         //8 
  {7, 3, 5, 254, 254, 6},     //9
  {0, 3, 5, 254, 2, 254},//? 10
  {254, 255, 254, 254, 2, 254},//! 11 
 {7, 3, 5, 255, 254, 255}, //A 12
 {255, 3, 6, 255, 2, 5}, //B 13
 {7, 0, 0, 4, 1, 1}, //C 14
 {255, 0, 5, 255, 1, 6}, //D 15
 {255, 3, 3, 255, 2, 2}, //E 16
 {255, 3, 3, 255, 254, 254}, //F 17
 {7, 0, 0, 4, 1, 5}, //G 18
 {255, 1, 255, 255, 254, 255},  //H 19
 {0, 255, 0, 1, 255, 1}, //I 20
 {254, 254, 255,1,1, 6}, //J 21
 {255, 1, 6, 255, 254, 5}, //K 22
 {255, 254, 254, 255, 1, 1}, //L 23
 {5,1,7,255,254,255}, //M 24
 {5,1,255,255,0,4}, //N 25
 {7, 0, 5, 4, 1, 6}, //O 26
 {255, 3, 5, 255, 254, 254}, //P 27
 {7,0,5,4,1,255}, //Q 28
 {255, 3, 5, 255, 254,5}, //R 29
 {7, 3, 3, 2, 2,6}, //S 30
 {0, 255, 0, 254, 255, 254}, //T 31
 {255, 254, 255, 4, 1, 6}, //U 32
 {5, 254, 7, 4, 1, 6}, //V 33
 {5, 1, 7, 4,255, 6}, //W 34
 {4, 1, 6, 7, 254, 5}, //X 35
 {4,1,6,254,255,254}, //Y 36
 {0,3,6,7,2,1}, //Z 37  
};

void printBigNum(int number, int startCol, int startRow){
  // Position cursor to requested position (each char takes 3 cols plus a space col)
  lcd.setCursor(startCol, startRow);
  // Each number split over two lines, 3 chars per line. Retrieve character
  // from the main array to make working with it here a bit easier.
  uint8_t thisNumber[6];
  for (int cnt = 0; cnt < 6; cnt++) {
    thisNumber[cnt] = bigNums[number][cnt];
  }
  // First line (top half) of digit
  for (int cnt = 0; cnt < 3; cnt++) {
    lcd.print((char)thisNumber[cnt]);
  }
  // Now position cursor to next line at same start column for digit
  lcd.setCursor(startCol, startRow + 1);
  // 2nd line (bottom half)
  for (int cnt = 3; cnt < 6; cnt++) {
    lcd.print((char)thisNumber[cnt]);
  }
}

//---------FIN VARIABLE DE LA BANDE----------
/////////////////////////////////////////////
//------------------SETUP--------------------

void setup(){
  // Initialisation des ports série
  Serial.begin(115200); // Logs pour le PC
  Serial1.begin(9600);  // Communication avec ESP32-1 (WebSocket) / (pins 18 et 19)
  Serial.println("Arduino Mega Local est prêt !");
  Serial2.begin(9600);  // Communication avec ESP32-2 (Firestore) / (pins 16 et 17)

// ====================
// DEBUT DU TEST DU LCD
// ==================== 
  
  lcd.clear();
  lcd1.clear();
  lcd.init();  
  lcd1.init();
  lcd.backlight();   
  lcd1.backlight();

// ==============================
// DEBUT DU TEST DES SERVOMOTEURS
// ==============================   

  pwm.begin();
  pwm.setPWMFreq(50);
  
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    pwm.setPWM(5, 0, pulseWidth(0));
    pwm.setPWM(6, 0, pulseWidth(0));
    pwm.setPWM(7, 0, pulseWidth(0));
    pwm.setPWM(8, 0, pulseWidth(0));
    pwm.setPWM(9, 0, pulseWidth(0));
    pwm.setPWM(10, 0, pulseWidth(0));
    pwm.setPWM(11, 0, pulseWidth(0));
    pwm.setPWM(12, 0, pulseWidth(0));
    pwm.setPWM(13, 0, pulseWidth(0));
    pwm.setPWM(14, 0, pulseWidth(0));
    pwm.setPWM(15, 0, pulseWidth(0));

// ========================
// DEBUT DU TEST DE L'HEURE
// ========================        

  rtc.begin();  
//  rtc.setDOW("Mercredi");     // Set Day-of-Week to SUNDAY
//  rtc.setTime(18, 55, 00);     // Set the time to 12:00:00 (24hr format)
//  rtc.setDate(25, 1, 21);   // Set the date to January 1st, 2014

//  NOM_J = (rtc.getDOWStr());
  NOM_J = (rtc.getDOWStr());
  lcd.setCursor(0,0);
   if (NOM_J == J1) lcd.print("Lundi   ");
   if (NOM_J == J2) lcd.print("Mardi   ");
   if (NOM_J == J3) lcd.print("Mercredi");
   if (NOM_J == J4) lcd.print("Jeudi   ");
   if (NOM_J == J5) lcd.print("Vendredi");
   if (NOM_J == J6) lcd.print("Samdi   ");
   if (NOM_J == J7) lcd.print("Dimanche");

  lcd.setCursor(12, 0);   
//  lcd.print(rtc.getDateStr(FORMAT_SHORT,FORMAT_LITTLEENDIAN,'/')); // ( Jour / Mois / Année) 
  lcd.print(rtc.getDateStr(FORMAT_SHORT,FORMAT_BIGENDIAN,'/')); // ( Année / Mois / Jour)
  NOM_M = (rtc.getDateStr());

  currentTime=millis();
  if((currentTime-previousTime)>1000){
    previousTime=currentTime;
  lcd.setCursor(9, 2);  
  lcd.print(rtc.getTimeStr());
  }
  lcd.setCursor(0, 3);  
  lcd.print(rtc.getTemp());
  lcd.setCursor(5, 3);  
  lcd.print((char)223);
  delay(5000);

// ============================================
// DEBUT DU CODE - CARTE SD - SAUVEGARDE DU JEU
// ============================================

  SD.begin(SDCARD_CS_PIN);

// ============================
// DEBUT DU TEST DE LA CARTE SD
// ============================

  Serial.println();
  Serial.println(F("Affichage des informations de la carte SD raccordée à l'Arduino"));
  Serial.println(F("==============================================================="));
  Serial.println();
  Serial.print(F("Init SD card... "));
  if (!SD.begin(SDCARD_CS_PIN)) {
    Serial.println(F("FAIL"));
    lcd.clear(); 
    lcd.setCursor(0, 0);
    lcd.print(F("Echec lors de"));
    lcd.setCursor(0, 1);
    lcd.print(F("l'initialisation"));        
    lcd.setCursor(0, 2);
    lcd.print(F("du jeu : "));
    lcd.setCursor(0, 3);
    lcd.print(F("Est-ce que"));
    lcd1.clear();    
    lcd1.setCursor(0, 0);
    lcd1.print(F("la carte SD est"));
    lcd1.setCursor(0, 1);
    lcd1.print(F("bien inseree"));
    lcd1.setCursor(0, 2);
    lcd1.print(F("dans le lecteur ?"));
    lcd1.setCursor(0, 3);
    lcd1.print(F("ensuite redemarer"));    
    for(;;); //  appui sur bouton RESET   
  }
  Serial.println(F("OK"));

//  if (!CarteSD.init(SPI_HALF_SPEED, sdCardSelect)) {
  if (!CarteSD.init(SPI_HALF_SPEED, SDCARD_CS_PIN)) {
    Serial.println(F("Échec lors de l'initialisation. Essayez de jeter un coup d'oeil à : "));        
    Serial.println(F("- est-ce que vos branchements électriques sont corrects ?"));
    Serial.println(F("- est-ce que le 'chipSelect' choisi dans le programme correspond bien à celui branché sur l'arduino ? (pin D10, par défaut)"));
    Serial.println();
    Serial.println(F("Appuyez sur RESET pour relancer le programme, au besoin."));
    while (1); 
  } 
  else {
    
    FastLED.clear(); XYMatrix(); FastLED.show();
    Serial.println(F("Câblage correct, Carte SD trouvée, Activation du Jeu."));
    Serial.println();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("LCD ... Ok"));
    lcd.setCursor(0, 1);
    lcd.print(F("Bande Leds ... Ok"));
    lcd.setCursor(0, 2);
    lcd.print(F("DFPlayer Mini online"));
    lcd.setCursor(0, 3);
    lcd.print(F("Carte SD trouvee"));
    lcd1.clear();
    lcd1.setCursor(0, 0);
    lcd1.print(F("Init SD card... "));    
    lcd1.setCursor(0, 1);
    lcd1.print(F("Blocs cibles ... OK"));
    delay(3000);
    FastLED.clear(); XYMatrix(); FastLED.show();
    lcd1.setCursor(0, 2);
    lcd1.print(F("Activation du Jeu"));   
    delay(3000);        
  }
  Serial.print(F("Type de carte SD insérée : "));
  switch (CarteSD.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println(F("SD1"));
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println(F("SD2"));
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println(F("SDHC"));
      break;
    default:
      Serial.println(F("Inconnu"));
  }
  Serial.println();
  if (!VolumeCarteSD.init(CarteSD)) {
    Serial.println(F("Aucune partition FAT16/FAT32 trouvée."));
    Serial.println(F("Vérifiez si votre carte SD est bien formatée !"));
    while (1);
  } else {
    Serial.print(F("Format du volume : FAT"));
    Serial.println(VolumeCarteSD.fatType(), DEC);
  }
  Serial.print(F("Nombre de clusters : ")); 
  Serial.println(VolumeCarteSD.clusterCount());
  Serial.print(F("Nombre de blocs par cluster : "));
  Serial.println(VolumeCarteSD.blocksPerCluster());
  Serial.print(F("Nombre total de blocs : "));
  Serial.println(VolumeCarteSD.blocksPerCluster() * VolumeCarteSD.clusterCount());
  Serial.println();
  volumesize = VolumeCarteSD.clusterCount() * VolumeCarteSD.blocksPerCluster();
  volumesize = volumesize / 2; 
  Serial.print(F("Taille du volume (en KB): ")); Serial.println(volumesize);
  Serial.print(F("Taille du volume (en MB): ")); Serial.println(volumesize / 1024);
  Serial.print(F("Taille du volume (en GB): ")); Serial.println(volumesize / 1024 / 1024.0);
  Serial.println();
  Serial.println(F("Fin !"));

//----Programme de sauvegarde sur carte SD----
//  printFilenames();

// ==============================
// DEBUT DU TEST DE LA BANDE LEDs
// ============================== 

  FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  FastLED.clear(); FastLED.show();
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;

// ==========================================
// DEBUT DU TEST DE LA CARTE SD - LECTEUR MP3
// ==========================================
  
  mySoftwareSerial.begin(9600);
//  Serial.begin(115200);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.setTimeOut(500);
  myDFPlayer.volume(volume); // Initialiser le volume
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

// =========================
// DEBUT DU TEST DU NRF24L01
// =========================

//    Serial.begin(115200);
    radio.begin();
    radio.openReadingPipe(1, adresse);
    radio.setPALevel(RF24_PA_HIGH);
    radio.startListening();  // Démarrer en mode réception

/*
    // Lire un message reçu
    if (radio.available()) {
        char messageRecu[32] = "";
        radio.read(&messageRecu, sizeof(messageRecu));
        Serial.print("Message reçu : ");
        Serial.println(messageRecu);

        // Répondre après réception
        delay(500);  // Petit délai avant d'envoyer la réponse
        radio.stopListening();  // Passer en mode émission

        const char reponse[] = "Message bien reçu !";
        radio.write(&reponse, sizeof(reponse));
        Serial.println("Réponse envoyée.");

        radio.startListening();  // Revenir en mode réception
*/

// ======================
// FIN DU CODE - NRF24L01
// ======================

    myDFPlayer.stop(); myDFPlayer.playMp3Folder(22);
    FastLED.clear(); XYMatrix(); FastLED.show();

/////////////////////////////////////////////////

// Emplacement des nouveaux pour -- Test de Codes
    pinMode(LEDV , OUTPUT);
    pinMode(LED13 , OUTPUT);   
    // For generate random values
    randomSeed(analogRead(15));
    temps = millis();
    counter = 10;

    Time1 = Time2 = millis();
    Period1 = Temps * 1000;
    Period2 = Temps * 1000;

//    tempsrestant = tempstotalF;
    TempsAleatoire = random(1 , 6);
    // LJ
    Time1LJ = Time2LJ = millis();
    Period1LJ = TempsAleatoireLJ * 1000;
    Period2LJ = TempsAleatoireLJ * 1000;
    //F = Facile
    Time1F = Time2F = millis();
    Period1F = 1000; // Coucher
    Period2F = 1000; // Lever
    //SM - Semi-Pro
    Time1SP = Time2SP = millis(); ////////// Réglages pour tests ///
    Period1SP = 6000;                       // 6000
    Period2SP = 2000;                       // 2000;
    //P = Pro
    Time1P = Time2P = millis();
    Period1P = 5000;
    Period2P = 3000;
    //C = Champion
    Time1C = Time2C = millis();
    Period1C = 4000;
    Period2C = 2000;
    //L = Légendaire
    Time1L = Time2L = millis();
    Period1L = 3000;
    Period2L = 2000;
    // Temps de pose en attente de reprendre
    TimePose = millis();
    PeriodPose = 3000;
    // Temps Code Led Aléatoire 3 secondes
    Time3S = millis();
    Period3S = 3000; //3000;
    // Temps music = 30 minutes
    Time18M = millis();
    Period18M = 1800000; // 1800000 = 30 sec
    // Temps Horloge 1 secondes
    Time1S = millis();
    Period1S = 1000;
  pinMode(boutonE, INPUT_PULLUP);
  pinMode(boutonG, INPUT_PULLUP);
  pinMode(boutonD, INPUT_PULLUP);
  pinMode(cible1,INPUT_PULLUP);
  pinMode(cible2,INPUT_PULLUP);
  pinMode(cible3,INPUT_PULLUP);
  pinMode(cible4,INPUT_PULLUP);
  pinMode(cible5,INPUT_PULLUP);
  pinMode(cible6,INPUT_PULLUP);
  pinMode(cible7,INPUT_PULLUP);
  pinMode(cible8,INPUT_PULLUP);
  pinMode(cible9,INPUT_PULLUP);
  pinMode(cible10,INPUT_PULLUP);

  //cration des caractres spciaux pour l'affichage big font  
    for (int cnt = 0; cnt < sizeof(custChar) / 8; cnt++) {
        lcd.createChar(cnt, custChar[cnt]);
    }        
    FastLED.clear(); XYMatrix(); FastLED.show();      
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    pwm.setPWM(5, 0, pulseWidth(0));
    pwm.setPWM(6, 0, pulseWidth(0));
    pwm.setPWM(7, 0, pulseWidth(0));
    pwm.setPWM(8, 0, pulseWidth(0));
    pwm.setPWM(9, 0, pulseWidth(0));
    pwm.setPWM(10, 0, pulseWidth(0));
    pwm.setPWM(11, 0, pulseWidth(0));
    pwm.setPWM(12, 0, pulseWidth(0));
    pwm.setPWM(13, 0, pulseWidth(0));
    pwm.setPWM(14, 0, pulseWidth(0));
    pwm.setPWM(15, 0, pulseWidth(0));    
    delay(500);
    FastLED.clear(); XYMatrix(); FastLED.show();    
    pwm.setPWM(0, 0, pulseWidth(85));
    pwm.setPWM(1, 0, pulseWidth(85));
    pwm.setPWM(2, 0, pulseWidth(85));
    pwm.setPWM(3, 0, pulseWidth(85));
    pwm.setPWM(4, 0, pulseWidth(85));
    pwm.setPWM(5, 0, pulseWidth(85));
    pwm.setPWM(6, 0, pulseWidth(85));
    pwm.setPWM(7, 0, pulseWidth(85));
    pwm.setPWM(8, 0, pulseWidth(85));
    pwm.setPWM(9, 0, pulseWidth(85));
    pwm.setPWM(10, 0, pulseWidth(85));
    pwm.setPWM(11, 0, pulseWidth(85));
    pwm.setPWM(12, 0, pulseWidth(85));
    pwm.setPWM(13, 0, pulseWidth(85));
    pwm.setPWM(14, 0, pulseWidth(85));
    pwm.setPWM(15, 0, pulseWidth(85));    
    delay(500);
    FastLED.clear(); XYMatrix(); FastLED.show();        
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    pwm.setPWM(5, 0, pulseWidth(0));
    pwm.setPWM(6, 0, pulseWidth(0));
    pwm.setPWM(7, 0, pulseWidth(0));
    pwm.setPWM(8, 0, pulseWidth(0));
    pwm.setPWM(9, 0, pulseWidth(0));
    pwm.setPWM(10, 0, pulseWidth(0));
    pwm.setPWM(11, 0, pulseWidth(0));
    pwm.setPWM(12, 0, pulseWidth(0));
    pwm.setPWM(13, 0, pulseWidth(0));
    pwm.setPWM(14, 0, pulseWidth(0));
    pwm.setPWM(15, 0, pulseWidth(0));    
    delay(500);
    FastLED.clear(); XYMatrix(); FastLED.show();        

  lcd.setCursor(0, 0);
  lcd.print(F("CIBLERIE CC BY-PMT 2"));
  lcd.setCursor(0, 1);
  lcd.print(F("BY POLICARPE MAT/TH" ));
  lcd.setCursor(0, 2);
  lcd.print(F(" create.arduino.cc/" ));
  lcd.setCursor(0, 3);
  lcd.print(F("projet/PolMT/NTE2022"));
  

  for (int i = 0; i < 3; i++) {

    FastLED.clear(); XYMatrix(); FastLED.show();     
    pwm.setPWM(0, 0, pulseWidth(85));
    pwm.setPWM(1, 0, pulseWidth(85));
    pwm.setPWM(2, 0, pulseWidth(85));
    pwm.setPWM(3, 0, pulseWidth(85));
    pwm.setPWM(4, 0, pulseWidth(85));
    pwm.setPWM(5, 0, pulseWidth(85));
    pwm.setPWM(6, 0, pulseWidth(85));
    pwm.setPWM(7, 0, pulseWidth(85));
    pwm.setPWM(8, 0, pulseWidth(85));
    pwm.setPWM(9, 0, pulseWidth(85));
    pwm.setPWM(10, 0, pulseWidth(85));
    pwm.setPWM(11, 0, pulseWidth(85));
    pwm.setPWM(12, 0, pulseWidth(85));
    pwm.setPWM(13, 0, pulseWidth(85));
    pwm.setPWM(14, 0, pulseWidth(85));
    pwm.setPWM(15, 0, pulseWidth(85));                   
    delay(500);
    lcd.noDisplay();
    FastLED.clear(); XYMatrix(); FastLED.show();     
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    pwm.setPWM(5, 0, pulseWidth(0));
    pwm.setPWM(6, 0, pulseWidth(0));
    pwm.setPWM(7, 0, pulseWidth(0));
    pwm.setPWM(8, 0, pulseWidth(0));
    pwm.setPWM(9, 0, pulseWidth(0));
    pwm.setPWM(10, 0, pulseWidth(0));
    pwm.setPWM(11, 0, pulseWidth(0));
    pwm.setPWM(12, 0, pulseWidth(0));
    pwm.setPWM(13, 0, pulseWidth(0));
    pwm.setPWM(14, 0, pulseWidth(0));
    pwm.setPWM(15, 0, pulseWidth(0));                
    delay(250);
    lcd.display();
    FastLED.clear(); XYMatrix(); FastLED.show();     
    pwm.setPWM(0, 0, pulseWidth(85));
    pwm.setPWM(1, 0, pulseWidth(85));
    pwm.setPWM(2, 0, pulseWidth(85));
    pwm.setPWM(3, 0, pulseWidth(85));
    pwm.setPWM(4, 0, pulseWidth(85));
    pwm.setPWM(5, 0, pulseWidth(85));
    pwm.setPWM(6, 0, pulseWidth(85));
    pwm.setPWM(7, 0, pulseWidth(85));
    pwm.setPWM(8, 0, pulseWidth(85));
    pwm.setPWM(9, 0, pulseWidth(85));
    pwm.setPWM(10, 0, pulseWidth(85));
    pwm.setPWM(11, 0, pulseWidth(85));
    pwm.setPWM(12, 0, pulseWidth(85));
    pwm.setPWM(13, 0, pulseWidth(85));
    pwm.setPWM(14, 0, pulseWidth(85));
    pwm.setPWM(15, 0, pulseWidth(85));
    delay(500);   
   }
  FastLED.clear(); XYMatrix(); FastLED.show();    
  lcd1.clear();       
  lcd1.setCursor(0, 0);
  lcd1.print(F("  Depassez-vous !!! "));
  lcd1.setCursor(0, 1);
  lcd1.print(F("        Mais        "));
  lcd1.setCursor(0, 2);
  lcd1.print(F("Qui sera le prochain"));
  lcd1.setCursor(0, 3);                
  delay(2000);
    FastLED.clear(); XYMatrix(); FastLED.show(); 
    pwm.setPWM(0, 0, pulseWidth(0));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(0));
    pwm.setPWM(4, 0, pulseWidth(0));
    pwm.setPWM(5, 0, pulseWidth(0));
    pwm.setPWM(6, 0, pulseWidth(0));
    pwm.setPWM(7, 0, pulseWidth(0));
    pwm.setPWM(8, 0, pulseWidth(0));
    pwm.setPWM(9, 0, pulseWidth(0));
    pwm.setPWM(10, 0, pulseWidth(0));
    pwm.setPWM(11, 0, pulseWidth(0));
    pwm.setPWM(12, 0, pulseWidth(0));
    pwm.setPWM(13, 0, pulseWidth(0));
    pwm.setPWM(14, 0, pulseWidth(0));
    pwm.setPWM(15, 0, pulseWidth(0));      
    delay(2000);
    
    FastLED.clear(); FastLED.show();
    MainScreen();


} //--------FIN DE LA SUITE DU SETUP--------------------------


int pulseWidth(int angle) {
  
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
}

int random_f (int min, int max)
{
    return (min + (rand () % (max-min+1)));
}
int attente() {
        randDelai = random(10, 150);
        return (randDelai);
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++){ leds[i].nscale8(250); } }


 
//--------FIN SETUP--------------------------
/////////////////////////////////////////////
//------------LOOP---------------------------

void loop() 
{
  if (inIntensityMode) { 
    RgIntensite();
  } else {
    if (!disableLedAnimation) { 
      CodeLedAleatoire();
      SonsAleatoires();
    }
  }
  if (inIntensitySon) {
    RgVolume();
  } else {
    if (!disableSonAnimation) {
      CodeLedAleatoire();
      SonsAleatoires(); 
    }
  }

  PresystemStart();

  communications();

} //---------------------------------------------FIN LOOP-------------------------------

//--------FIN LOOP---------------------------
/////////////////////////////////////////////
//------------LOOP---------------------------


