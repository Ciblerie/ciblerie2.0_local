
void PresystemStart() {  // Nouveau code réalisé le 30/11/24 à 12H

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
  unsigned long currentMillis = millis();    
  ButtonCode = read_LCD_buttons();  
  switch (ButtonCode)
  {

/////////////////////////////////////// BOUTON DE DROITE   
    
    case btnRIGHT:
      {
        previousMillis = currentMillis;
        isBacklightOn = true;
        lcd.backlight();
        delay(ButtonDelay);
        break;
      }

/////////////////////////////////////// BOUTON DE GAUCHE
  
    case btnLEFT:
      {
        previousMillis = currentMillis;
        isBacklightOn = true;
        lcd.backlight();
        delay(ButtonDelay);
        break;
      }



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


                   
    case btnUP: // BOUTON DU HAUT
      {
        delay(250);
        previousMillis = currentMillis;
        isBacklightOn = true;
        lcd.backlight();
        switch (ScreenNumber)
        {

///////////////// Acceuil

          case 10:
            {
              lcd.clear();
              MenuScreen5();
              break;
            }
          case 11:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }
          case 12:
            {
              lcd.clear();
              MenuScreen1();
              break;
            }
          case 13:
            {
              lcd1.clear();
              MenuScreen2();
              break;
            }
          case 14:
            {
              lcd1.clear();
              MenuScreen3();
              break;
            }
          case 15:
            {
              lcd1.clear();
              MenuScreen4();
              break;
            }

///////////////// NOMBRE DE JOUEUR - MODE SURVI
            
          case 100:
            {
              lcd.clear();
              NbjoueursScreenMSE();
              break;
            }
          case 101:
            {
              lcd.clear();
              NbjoueursScreenMS0();
              break;
            }
          case 102:
            {
              lcd.clear();
              NbjoueursScreenMS1();
              break;
            }
          case 103:
            {
              lcd.clear();
              NbjoueursScreenMS2();
              break;
            }
          case 104:
            {
              lcd.clear();
              NbjoueursScreenMS3();
              break;
            }

///////////////// NOMBRE DE JOUEUR - LE JEU

          case 110:
            {
              lcd.clear();
              NbjoueursScreenLJE();
              break;
            }
          case 111:
            {
              lcd.clear();
              NbjoueursScreenLJ0();
              break;
            }
          case 112:
            {
              lcd.clear();
              NbjoueursScreenLJ1();
              break;
            }
          case 113:
            {
              lcd.clear();
              NbjoueursScreenLJ2();
              break;
            }
          case 114:
            {
              lcd.clear();
              NbjoueursScreenLJ3();
              break;
            }

///////////////// NIVEAUX - LE CLASSIQUE

          case 120:
            {
              lcd.clear();
              LevelsScreenCE();
              break;
            }
          case 121:
            {
              lcd.clear();
              LevelsScreenC0();
              break;
            }
          case 122:
            {
              lcd.clear();
              LevelsScreenC1();
              break;
            }
          case 123:
            {
              lcd.clear();
              LevelsScreenC2();
              break;
            }
          case 124:
            {
              lcd.clear();
              LevelsScreenC3();
              break;
            }
          case 125:
            {
              lcd.clear();
              LevelsScreenC4();
              break;
            }                        

///////////////// PARAMETRES

          case 130:
            {
              lcd.clear();
              ParametresE();
              break;
            }
          case 131:
            {
              lcd.clear();
              ParametresIL();
              break;
            }
          case 132:
            {
              lcd.clear();
              ParametresS();
              break;
            }
          case 133:
            {
              lcd.clear();
              ParametresW();
              break;
            }                        

//////////////////// AFFICHAGE DES SCORES

          case 140:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }
          case 141:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }

//////////////////// MODE COMPETITION

          case 150:
            {
              lcd.clear();
              ModeMenuScreenCPTE();
              break;
            }              
          case 151:
            {
              lcd.clear();
              ModeMenuScreenCPT0();
              break;
            }                       

//////////////////// MODE SURVI
            
          case 1000:
            {
              lcd.clear();
              ModeMenuScreenMMMS1();
              break;
            }
          case 1001:
            {
              lcd.clear();
              ModeMenuScreenMMMS0();
              break;
            }
          case 1002:
            {
              lcd.clear();
              ModeMenuScreenMMMS3();
              break;
            }             
          case 1003:
            {
              lcd.clear();
              ModeMenuScreenMMMS2();
              break;
            }
          case 1004:
            {
              lcd.clear();
              ModeMenuScreenMMMS5();
              break;
            }
          case 1005:
            {
              lcd.clear();
              ModeMenuScreenMMMS4();
              break;
            }
          case 1006:
            {
              lcd.clear();
              ModeMenuScreenMMMS7();
              break;
            }
          case 1007:
            {
              lcd.clear();
              ModeMenuScreenMMMS6();
              break;
            }

//////////////////// LE JEU 
           
          case 1010:
            {
              lcd.clear();
              ModeMenuScreenMMLJ1();
              break;
            }
          case 1011:
            {
              lcd.clear();
              ModeMenuScreenMMLJ0();
              break;
            }
          case 1012:
            {
              lcd.clear();
              ModeMenuScreenMMLJ3();
              break;
            }
          case 1013:
            {
              lcd.clear();
              ModeMenuScreenMMLJ2();
              break;
            }            
          case 1014:
            {
              lcd.clear();
              ModeMenuScreenMMLJ5();
              break;
            }
          case 1015:
            {
              lcd.clear();
              ModeMenuScreenMMLJ4();
              break;
            }
          case 1016:
            {
              lcd.clear();
              ModeMenuScreenMMLJ7();
              break;
            }
          case 1017:
            {
              lcd.clear();
              ModeMenuScreenMMLJ6();
              break;
            }

//////////////////// LE CLASSIQUE - FACILE

          case 1020:
            {
              lcd.clear();
              NbjoueursScreenCFE();
              break;
            }
          case 1021:
            {
              lcd.clear();
              NbjoueursScreenCF0();
              break;
            }
          case 1022:
            {
              lcd.clear();
              NbjoueursScreenCF1();
              break;
            }
          case 1023:
            {
              lcd.clear();
              NbjoueursScreenCF2();
              break;
            }
          case 1024:
            {
              lcd.clear();
              NbjoueursScreenCF3();
              break;
            }

//////////////////// LE CLASSIQUE - SEMI-PRO

          case 1030:
            {
              lcd.clear();
              NbjoueursScreenCSPE();
              break;
            }
          case 1031:
            {
              lcd.clear();
              NbjoueursScreenCSP0();
              break;
            }
          case 1032:
            {
              lcd.clear();
              NbjoueursScreenCSP1();
              break;
            }
          case 1033:
            {
              lcd.clear();
              NbjoueursScreenCSP2();
              break;
            }
          case 1034:
            {
              lcd.clear();
              NbjoueursScreenCSP3();
              break;
            }

//////////////////// LE CLASSIQUE - PRO

          case 1040:
            {
              lcd.clear();
              NbjoueursScreenCPE();
              break;
            }
          case 1041:
            {
              lcd.clear();
              NbjoueursScreenCP0();
              break;
            }
          case 1042:
            {
              lcd.clear();
              NbjoueursScreenCP1();
              break;
            }
          case 1043:
            {
              lcd.clear();
              NbjoueursScreenCP2();
              break;
            }
          case 1044:
            {
              lcd.clear();
              NbjoueursScreenCP3();
              break;
            }

//////////////////// LE CLASSIQUE - CHAMPION

          case 1050:
            {
              lcd.clear();
              NbjoueursScreenCCE();
              break;
            }
          case 1051:
            {
              lcd.clear();
              NbjoueursScreenCC0();
              break;
            }
          case 1052:
            {
              lcd.clear();
              NbjoueursScreenCC1();
              break;
            }
          case 1053:
            {
              lcd.clear();
              NbjoueursScreenCC2();
              break;
            }
          case 1054:
            {
              lcd.clear();
              NbjoueursScreenCC3();
              break;
            }

//////////////////// LE CLASSIQUE - LEGENDE

          case 1060:
            {
              lcd.clear();
              NbjoueursScreenCLE();
              break;
            }
          case 1061:
            {
              lcd.clear();
              NbjoueursScreenCL0();
              break;
            }
          case 1062:
            {
              lcd.clear();
              NbjoueursScreenCL1();
              break;
            }
          case 1063:
            {
              lcd.clear();
              NbjoueursScreenCL2();
              break;
            }
          case 1064:
            {
              lcd.clear();
              NbjoueursScreenCL3();
              break;
            }                                                            

//////////////////// MODE MENU - CLASSIQUE - FACILE
            
          case 1100:
            {
              lcd.clear();
              ModeMenuScreenMM1();
              break;
            }
          case 1101:
            {
              lcd.clear();
              ModeMenuScreenMM0();
              break;
            }
          case 1102:
            {
              lcd.clear();
              ModeMenuScreenMM3();
              break;
            }
          case 1103:
            {
              lcd.clear();
              ModeMenuScreenMM2();
              break;
            }
          case 1104:
            {
              lcd.clear();
              ModeMenuScreenMM5();
              break;
            }
          case 1105:
            {
              lcd.clear();
              ModeMenuScreenMM4();
              break;
            }
          case 1106:
            {
              lcd.clear();
              ModeMenuScreenMM7();
              break;
            }
          case 1107:
            {
              lcd.clear();
              ModeMenuScreenMM6();
              break;
            }

//////////////////// MODE MENU - CLASSIQUE - SEMI-PRO           
                       
          case 1110:
            {
              lcd.clear();
              ModeMenuScreenMM11();
              break;
            }
          case 1111:
            {
              lcd.clear();
              ModeMenuScreenMM10();
              break;
            }
          case 1112:
            {
              lcd.clear();
              ModeMenuScreenMM13();
              break;
            }
          case 1113:
            {
              lcd.clear();
              ModeMenuScreenMM12();
              break;
            }
          case 1114:
            {
              lcd.clear();
              ModeMenuScreenMM15();
              break;
            }
          case 1115:
            {
              lcd.clear();
              ModeMenuScreenMM14();
              break;
            }
          case 1116:
            {
              lcd.clear();
              ModeMenuScreenMM17();
              break;
            }
          case 1117:
            {
              lcd.clear();
              ModeMenuScreenMM16();
              break;
            }                                                                                   

//////////////////// MODE MENU - CLASSIQUE - PRO                                                                                              

          case 1120:
            {
              lcd.clear();
              ModeMenuScreenMM21();
              break;
            }
          case 1121:
            {
              lcd.clear();
              ModeMenuScreenMM20();
              break;
            }
          case 1122:
            {
              lcd.clear();
              ModeMenuScreenMM23();
              break;
            }
          case 1223:
            {
              lcd.clear();
              ModeMenuScreenMM22();
              break;
            }
          case 1124:
            {
              lcd.clear();
              ModeMenuScreenMM25();
              break;
            }
          case 1125:
            {
              lcd.clear();
              ModeMenuScreenMM24();
              break;
            }
          case 1126:
            {
              lcd.clear();
              ModeMenuScreenMM27();
              break;
            }
          case 1127:
            {
              lcd.clear();
              ModeMenuScreenMM26();
              break;
            }            

//////////////////// MODE MENU - CLASSIQUE - CHAMPION                                                                                              

          case 1130:
            {
              lcd.clear();
              ModeMenuScreenMM31();
              break;
            }
          case 1131:
            {
              lcd.clear();
              ModeMenuScreenMM30();
              break;
            }
          case 1132:
            {
              lcd.clear();
              ModeMenuScreenMM33();
              break;
            }
          case 1133:
            {
              lcd.clear();
              ModeMenuScreenMM32();
              break;
            }
          case 1134:
            {
              lcd.clear();
              ModeMenuScreenMM35();
              break;
            }
          case 1135:
            {
              lcd.clear();
              ModeMenuScreenMM34();
              break;
            }
          case 1136:
            {
              lcd.clear();
              ModeMenuScreenMM37();
              break;
            }
          case 1137:
            {
              lcd.clear();
              ModeMenuScreenMM36();
              break;
            }

//////////////////// MODE MENU - CLASSIQUE - LEGENDE                                                                                              

          case 1140:
            {
              lcd.clear();
              ModeMenuScreenMM41();
              break;
            }
          case 1141:
            {
              lcd.clear();
              ModeMenuScreenMM40();
              break;
            }
          case 1142:
            {
              lcd.clear();
              ModeMenuScreenMM43();
              break;
            }
          case 1143:
            {
              lcd.clear();
              ModeMenuScreenMM42();
              break;
            }
          case 1144:
            {
              lcd.clear();
              ModeMenuScreenMM45();
              break;
            }
          case 1145:
            {
              lcd.clear();
              ModeMenuScreenMM44();
              break;
            }
          case 1146:
            {
              lcd.clear();
              ModeMenuScreenMM47();
              break;
            }
          case 1147:
            {
              lcd.clear();
              ModeMenuScreenMM46();
              break;
            }

///////////////// FIN BOUTON DU HAUT

         }
        delay(ButtonDelay);
        break;
      }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    case btnDOWN: // BOUTON DU BAS
      {
        delay(250);        
        previousMillis = currentMillis;
        isBacklightOn = true;
        lcd.backlight();
        switch (ScreenNumber)
        {

///////////////// Acceuil

          case 10:
            {
              lcd.clear();
              MenuScreen1();
              break;
            }
          case 11:
            {
              lcd1.clear();
              MenuScreen2();
              break;
            }
          case 12:
            {
              lcd.clear();
              MenuScreen3();
              break;
            }
          case 13:
            {
              lcd.clear();
              MenuScreen4();
              break;
            }
          case 14:
            {
              lcd1.clear();
              MenuScreen5();
              break;
            }
          case 15:
            {
              lcd1.clear();
              MenuScreen0();
              break;
            }

///////////////// NOMBRE DE JOUEUR - MODE SURVI

          case 100:
            {
              lcd.clear();
              NbjoueursScreenMS1();
              break;
            }
          case 101:
            {
              lcd.clear();
              NbjoueursScreenMS2();
              break;
            }
          case 102:
            {
              lcd.clear();
              NbjoueursScreenMS3();
              break;
            }
          case 103:
            {
              lcd.clear();
              NbjoueursScreenMSE();
              break;
            }
          case 104:
            {
              lcd.clear();
              NbjoueursScreenMS0();
              break;
            }

///////////////// NOMBRE DE JOUEUR - LE JEU      
            
          case 110:
            {
              lcd.clear();
              NbjoueursScreenLJ1();
              break;
            }
          case 111:
            {
              lcd.clear();
              NbjoueursScreenLJ2();
              break;
            }
          case 112:
            {
              lcd.clear();
              NbjoueursScreenLJ3();
              break;
            }
          case 113:
            {
              lcd.clear();
              NbjoueursScreenLJE();
              break;
            }
          case 114:
            {
              lcd.clear();
              NbjoueursScreenLJ0();
              break;
            }

///////////////// NIVEAUX CLASSIQUE
                     
          case 120:
            {
              lcd.clear();
              LevelsScreenC1();
              break;
            }
          case 121:
            {
              lcd.clear();
              LevelsScreenC2();
              break;
            }
          case 122:
            {
              lcd.clear();
              LevelsScreenC3();
              break;
            }
          case 123:
            {
              lcd.clear();
              LevelsScreenC4();
              break;
            }
          case 124:
            {
              lcd.clear();
              LevelsScreenCE();
              break;
            }            
          case 125:
            {
              lcd.clear();
              LevelsScreenC0();
              break;
            }

///////////////// NIVEAUX CLASSIQUE
                     
          case 130:
            {
              lcd.clear();
              ParametresS();
              break;
            }
          case 131:
            {
              lcd.clear();
              ParametresW();
              break;
            }
          case 132:
            {
              lcd.clear();
              ParametresE();
              break;
            }
          case 133:
            {
              lcd.clear();
              ParametresIL();
              break;
            }

//////////////////// AFFICHAGE DES SCORES

          case 140:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }
          case 141:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }

//////////////////// MODE COMPETITION

          case 150:
            {
              lcd.clear();
              ModeMenuScreenCPTE();
              break;
            }
          case 151:
            {
              lcd.clear();
              ModeMenuScreenCPT0();
              break;
            }                        

//////////////////// MODE SURVI
            
          case 1000:
            {
              lcd.clear();
              ModeMenuScreenMMMS1();
              break;
            }
          case 1001:
            {
              lcd.clear();
              ModeMenuScreenMMMS0();
              break;
            }
          case 1002:
            {
              lcd.clear();
              ModeMenuScreenMMMS3();
              break;
            }             
          case 1003:
            {
              lcd.clear();
              ModeMenuScreenMMMS2();
              break;
            }
          case 1004:
            {
              lcd.clear();
              ModeMenuScreenMMMS5();
              break;
            }
          case 1005:
            {
              lcd.clear();
              ModeMenuScreenMMMS4();
              break;
            }
          case 1006:
            {
              lcd.clear();
              ModeMenuScreenMMMS7();
              break;
            }
          case 1007:
            {
              lcd.clear();
              ModeMenuScreenMMMS6();
              break;
            }

//////////////////// LE JEU
           
          case 1010:
            {
              lcd.clear();
              ModeMenuScreenMMLJ1();
              break;
            }
          case 1011:
            {
              lcd.clear();
              ModeMenuScreenMMLJ0();
              break;
            }
          case 1012:
            {
              lcd.clear();
              ModeMenuScreenMMLJ3();
              break;
            }
          case 1013:
            {
              lcd.clear();
              ModeMenuScreenMMLJ2();
              break;
            }            
          case 1014:
            {
              lcd.clear();
              ModeMenuScreenMMLJ5();
              break;
            }
          case 1015:
            {
              lcd.clear();
              ModeMenuScreenMMLJ4();
              break;
            }
          case 1016:
            {
              lcd.clear();
              ModeMenuScreenMMLJ7();
              break;
            }
          case 1017:
            {
              lcd.clear();
              ModeMenuScreenMMLJ6();
              break;
            }

//////////////////// LE CLASSIQUE - FACILE

          case 1020:
            {
              lcd.clear();
              NbjoueursScreenCF1();
              break;
            }
          case 1021:
            {
              lcd.clear();
              NbjoueursScreenCF2();
              break;
            }
          case 1022:
            {
              lcd.clear();
              NbjoueursScreenCF3();
              break;
            }
          case 1023:
            {
              lcd.clear();
              NbjoueursScreenCFE();
              break;
            }
          case 1024:
            {
              lcd.clear();
              NbjoueursScreenCF0();
              break;
            }

//////////////////// LE CLASSIQUE - SEMI-PRO

          case 1030:
            {
              lcd.clear();
              NbjoueursScreenCSP1();
              break;
            }
          case 1031:
            {
              lcd.clear();
              NbjoueursScreenCSP2();
              break;
            }
          case 1032:
            {
              lcd.clear();
              NbjoueursScreenCSP3();
              break;
            }
          case 1033:
            {
              lcd.clear();
              NbjoueursScreenCSPE();
              break;
            }
          case 1034:
            {
              lcd.clear();
              NbjoueursScreenCSP0();
              break;
            }

//////////////////// LE CLASSIQUE - PRO

          case 1040:
            {
              lcd.clear();
              NbjoueursScreenCP1();
              break;
            }
          case 1041:
            {
              lcd.clear();
              NbjoueursScreenCP2();
              break;
            }
          case 1042:
            {
              lcd.clear();
              NbjoueursScreenCP3();
              break;
            }
          case 1043:
            {
              lcd.clear();
              NbjoueursScreenCPE();
              break;
            }
          case 1044:
            {
              lcd.clear();
              NbjoueursScreenCP0();
              break;
            }

//////////////////// LE CLASSIQUE - CHAMPION

          case 1050:
            {
              lcd.clear();
              NbjoueursScreenCC1();
              break;
            }
          case 1051:
            {
              lcd.clear();
              NbjoueursScreenCC2();
              break;
            }
          case 1052:
            {
              lcd.clear();
              NbjoueursScreenCC3();
              break;
            }
          case 1053:
            {
              lcd.clear();
              NbjoueursScreenCCE();
              break;
            }
          case 1054:
            {
              lcd.clear();
              NbjoueursScreenCC0();
              break;
            }

//////////////////// LE CLASSIQUE - LEGENDE

          case 1060:
            {
              lcd.clear();
              NbjoueursScreenCL1();
              break;
            }
          case 1061:
            {
              lcd.clear();
              NbjoueursScreenCL2();
              break;
            }
          case 1062:
            {
              lcd.clear();
              NbjoueursScreenCL3();
              break;
            }
          case 1063:
            {
              lcd.clear();
              NbjoueursScreenCLE();
              break;
            }
          case 1064:
            {
              lcd.clear();
              NbjoueursScreenCL0();
              break;
            }

//////////////////// MODE MENU - CLASSIQUE - FACILE
            
          case 1100:
            {
              lcd.clear();
              ModeMenuScreenMM1();
              break;
            }
          case 1101:
            {
              lcd.clear();
              ModeMenuScreenMM0();
              break;
            }
          case 1102:
            {
              lcd.clear();
              ModeMenuScreenMM3();
              break;
            }
          case 1103:
            {
              lcd.clear();
              ModeMenuScreenMM2();
              break;
            }
          case 1104:
            {
              lcd.clear();
              ModeMenuScreenMM5();
              break;
            }
          case 1105:
            {
              lcd.clear();
              ModeMenuScreenMM4();
              break;
            }
          case 1106:
            {
              lcd.clear();
              ModeMenuScreenMM7();
              break;
            }
          case 1107:
            {
              lcd.clear();
              ModeMenuScreenMM6();
              break;
            }

//////////////////// MODE MENU - CLASSIQUE - SEMI-PRO           
                       
          case 1110:
            {
              lcd.clear();
              ModeMenuScreenMM11();
              break;
            }
          case 1111:
            {
              lcd.clear();
              ModeMenuScreenMM10();
              break;
            }
          case 1112:
            {
              lcd.clear();
              ModeMenuScreenMM13();
              break;
            }
          case 1113:
            {
              lcd.clear();
              ModeMenuScreenMM12();
              break;
            }
          case 1114:
            {
              lcd.clear();
              ModeMenuScreenMM15();
              break;
            }
          case 1115:
            {
              lcd.clear();
              ModeMenuScreenMM14();
              break;
            }
          case 1116:
            {
              lcd.clear();
              ModeMenuScreenMM17();
              break;
            }
          case 1117:
            {
              lcd.clear();
              ModeMenuScreenMM16();
              break;
            }                                                                                   

//////////////////// MODE MENU - CLASSIQUE - PRO                                                                                              

          case 1120:
            {
              lcd.clear();
              ModeMenuScreenMM21();
              break;
            }
          case 1121:
            {
              lcd.clear();
              ModeMenuScreenMM20();
              break;
            }
          case 1122:
            {
              lcd.clear();
              ModeMenuScreenMM23();
              break;
            }
          case 1223:
            {
              lcd.clear();
              ModeMenuScreenMM22();
              break;
            }
          case 1124:
            {
              lcd.clear();
              ModeMenuScreenMM25();
              break;
            }
          case 1125:
            {
              lcd.clear();
              ModeMenuScreenMM24();
              break;
            }
          case 1126:
            {
              lcd.clear();
              ModeMenuScreenMM27();
              break;
            }
          case 1127:
            {
              lcd.clear();
              ModeMenuScreenMM26();
              break;
            }            

//////////////////// MODE MENU - CLASSIQUE - CHAMPION                                                                                              

          case 1130:
            {
              lcd.clear();
              ModeMenuScreenMM31();
              break;
            }
          case 1131:
            {
              lcd.clear();
              ModeMenuScreenMM30();
              break;
            }
          case 1132:
            {
              lcd.clear();
              ModeMenuScreenMM33();
              break;
            }
          case 1133:
            {
              lcd.clear();
              ModeMenuScreenMM32();
              break;
            }
          case 1134:
            {
              lcd.clear();
              ModeMenuScreenMM35();
              break;
            }
          case 1135:
            {
              lcd.clear();
              ModeMenuScreenMM34();
              break;
            }
          case 1136:
            {
              lcd.clear();
              ModeMenuScreenMM37();
              break;
            }
          case 1137:
            {
              lcd.clear();
              ModeMenuScreenMM36();
              break;
            }

//////////////////// MODE MENU - CLASSIQUE - LEGENDE                                                                                              

          case 1140:
            {
              lcd.clear();
              ModeMenuScreenMM41();
              break;
            }
          case 1141:
            {
              lcd.clear();
              ModeMenuScreenMM40();
              break;
            }
          case 1142:
            {
              lcd.clear();
              ModeMenuScreenMM43();
              break;
            }
          case 1143:
            {
              lcd.clear();
              ModeMenuScreenMM42();
              break;
            }
          case 1144:
            {
              lcd.clear();
              ModeMenuScreenMM45();
              break;
            }
          case 1145:
            {
              lcd.clear();
              ModeMenuScreenMM44();
              break;
            }
          case 1146:
            {
              lcd.clear();
              ModeMenuScreenMM47();
              break;
            }
          case 1147:
            {
              lcd.clear();
              ModeMenuScreenMM46();
              break;
            }                                                     
                        
///////////////// FIN DU BOUTON DU BAS

         }
        delay(ButtonDelay);
        break;
      }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    case btnSELECT: // BOUTON DE SELECTION
      {
        delay(250);        
        previousMillis = currentMillis;
        isBacklightOn = true;
        lcd.backlight();
        switch (ScreenNumber)
        {
          case 0:
            {
              ScreenNumber = 1;                         
              break;
            }

///////////////// ACCES AU JEU

          case 1:
            {
              MenuScreen0();
              break;
            }

///////////////// ACCEUIL
                                              
          case 10:
            {
              lcd.clear();
              LevelsScreenC0(); // Le Classic
              break;
            }
          case 11:
            {
              lcd.clear();
              NbjoueursScreenLJ0(); // Le Jeu
              break;
            }
          case 12:
            {
              lcd.clear();
              NbjoueursScreenMS0(); // Mode Survi
              break;
            }
          case 13:
            {
              lcd.clear();
              lcd1.clear();
              while (!sortie) {
                CPT1();
               if (initialisation == true){ModeMenuScreenCPT0(); delay(50); break;}
               }
              break;
            }
          case 14:
            {
              lcd.clear();
              lcd1.clear();
              ParametresIL();
              break;
            }
          case 15:
            {
              lcd.clear();
              lcd1.clear();
              inAffichageScores = true; // Active le mode afficherScores
              break;
            }

//////////////////// MODE SURVI

          case 100:
            {
              lcd.clear();
              lcd1.clear();
              while (!sortie) {
                MS1();
               if (initialisation == true){ModeMenuScreenMMMS0(); delay(50); break;} // 1/4
               }
              break;
            }
          case 101:
            {
              lcd.clear();
              lcd1.clear();
              while (!sortie) {
                MS2();
               if (initialisation == true){ModeMenuScreenMMMS2(); delay(50); break;} // 2/4
               }
              break;
            }            
          case 102:
            {
              lcd.clear();
              lcd1.clear();
              while (!sortie) {
                MS3();
               if (initialisation == true){ModeMenuScreenMMMS4(); delay(50); break;} // 3/4
               }
              break;
            }
          case 103:
            {
              lcd.clear();
              lcd1.clear();
              while (!sortie) {
                MS4();
               if (initialisation == true){ModeMenuScreenMMMS6(); delay(50); break;} // 4/4
               }
              break;
            }
          case 104:
            {
              lcd.clear();
              lcd1.clear();
              MenuScreen0(); // E
              break;
            }

//////////////////// LE JEU

          case 110:
            {
              lcd.clear();
              while (1) {
                LJ1();
               if (initialisation == true){ModeMenuScreenMMLJ0(); delay(50); break;} // 1/4
               }
              break;
            }                                 
          case 111:
            {             
              lcd.clear();
              while (1) {
                LJ2();
               if (initialisation == true){ModeMenuScreenMMLJ2(); delay(50); break;} // 2/4
               }
              break;
            }            
          case 112:
            {             
              lcd.clear();
              while (1) {
                LJ3();
               if (initialisation == true){ModeMenuScreenMMLJ4(); delay(50); break;} // 3/4
               }
              break;
            }            
          case 113:
            {             
              lcd.clear();
              while (1) {
                LJ4();
               if (initialisation == true){ModeMenuScreenMMLJ6(); delay(50); break;} // 4/4
               }
              break;
            }
          case 114:
            {
              lcd.clear();
              MenuScreen0(); // E
              break;
            }

//////////////////// LE CLASSIQUE

          case 120:
            {
              lcd.clear();
              NbjoueursScreenCF0(); // Facile
              break;
            }
          case 121:
            {
              lcd.clear();                           
              NbjoueursScreenCSP0(); // Semi-Pro
              break;
            }
          case 122:
            {
              lcd.clear();                           
              NbjoueursScreenCP0(); // Pro
              break;
            }
          case 123:
            {
              lcd.clear();                           
              NbjoueursScreenCC0(); // Champion
              break;
            }
          case 124:
            {
              lcd.clear();
              NbjoueursScreenCL0(); // Légende
              break;
            }
          case 125:
            {
              lcd.clear();
              MenuScreen0(); // E
              break;
            }

//////////////////// Paramètres

          case 130:
            {
              lcd.clear();
              lcd1.clear();
              inIntensityMode = true; // Active le mode Intensité
              break;
            }
          case 131:
            {
              lcd.clear();
              lcd1.clear();
              inIntensitySon = true; // Active le mode Son
              break;
            }
          case 132:
            {
              lcd.clear();
              lcd1.clear();                          
            //  RWifi();
              break;
            }
          case 133:
            {
              lcd.clear();
              lcd1.clear();                           
              MenuScreen0();
              break;
            }

//////////////////// AFFICHAGE DES SCORES

          case 140:
            {
              lcd.clear();
              lcd1.clear();
              MenuScreen0();
              break;
            }
          case 141:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }                        

//////////////////// MODE COMPETITION

          case 150:
            {
              lcd.clear();
              lcd1.clear();
              while (!sortie) {
                CPT1();
               if (initialisation == true){ModeMenuScreenCPT0(); delay(50); break;}
               }
              break;
            }
          case 151:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }

//////////////////// ACTIONS DU MODE SURVI

          case 1000:
            {
              lcd.clear();
              lcd1.clear();
              while (!sortie) {
                MS1();
               if (initialisation == true){ModeMenuScreenMMMS0(); delay(50); break;} // 1/4
               }
              break;
            }
          case 1001:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }
          case 1002:
            {
              lcd.clear();
              lcd1.clear();
              while (!sortie) {
                MS2();
               if (initialisation == true){ModeMenuScreenMMMS2(); delay(50); break;}
               }
              break;
            }
          case 1003:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }            
          case 1004:
            {
              lcd.clear();
              lcd1.clear();
              while (!sortie) {
                MS3();
               if (initialisation == true){ModeMenuScreenMMMS4(); delay(50); break;}
               }
              break;
            }
          case 1005:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }
          case 1006:
            {
              lcd.clear();
              lcd1.clear();
              while (!sortie) {
                MS4();
               if (initialisation == true){ModeMenuScreenMMMS6(); delay(50); break;}
               }
              break;
            }
          case 1007:
            {
              lcd.clear();
              lcd1.clear();
              MenuScreen0();
              break;
            }

//////////////////// ACTIONS DU MODE - LE JEU

          case 1010:
            {
              lcd.clear();              
              while (1) {
                LJ1();
               if (initialisation == true){ModeMenuScreenMMLJ0(); delay(50); break;}
               }
              break;
            }            
          case 1011:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }                     
          case 1012:
            {             
              lcd.clear();
              while (1) {
                LJ2();
               if (initialisation == true){ModeMenuScreenMMLJ2(); delay(50); break;}
               }
              break;
            }
          case 1013:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }            
          case 1014:
            {             
              lcd.clear();
              while (1) {
                LJ3();
               if (initialisation == true){ModeMenuScreenMMLJ4(); delay(50); break;}
               }
              break;
            }
          case 1015:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }            
          case 1016:
            {             
              lcd.clear();
              while (1) {
                LJ4();
               if (initialisation == true){ModeMenuScreenMMLJ6(); delay(50); break;}
               }
              break;
            }
          case 1017:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }

//////////////////// LE CLASSIQUE - FACILE                                   
          
          case 1020:
            {
              lcd.clear();              
              while (1) {
                CF1();                
               if (initialisation == true){ModeMenuScreenMM0(); delay(500); break;}
               }
              break;
            }           
          case 1021:
            {             
              lcd.clear();
              while (1) {
                CF2();
               if (initialisation == true){ModeMenuScreenMM2(); delay(50); break;}
               }
              break;
            }
          case 1022:
            {             
              lcd.clear();
              while (1) {
                CF3();
               if (initialisation == true){ModeMenuScreenMM4(); delay(50); break;}
               }
              break;
            }
          case 1023:
            {             
              lcd.clear();
              while (1) {
                CF4();
               if (initialisation == true){ModeMenuScreenMM6(); delay(50); break;}
               }
              break;
            }
          case 1024:
            {             
              lcd.clear();
              MenuScreen0();
              break;
            }

//////////////////// LE CLASSIQUE - SEMI-PRO                                   
          
          case 1030:
            {
              lcd.clear();              
              while (1) {
                CSP1();                
               if (initialisation == true){ModeMenuScreenMM10(); delay(50); break;}
               }
              break;
            }           
          case 1031:
            {             
              lcd.clear();
              while (1) {
                CSP2();
               if (initialisation == true){ModeMenuScreenMM12(); delay(50); break;}
               }
              break;
            }
          case 1032:
            {             
              lcd.clear();
              while (1) {
                CSP3();
               if (initialisation == true){ModeMenuScreenMM14(); delay(50); break;}
               }
              break;
            }
          case 1033:
            {             
              lcd.clear();
              while (1) {
                CSP4();
               if (initialisation == true){ModeMenuScreenMM16(); delay(50); break;}
               }
              break;
            }
          case 1034:
            {             
              lcd.clear();
              MenuScreen0();
              break;
            }

//////////////////// LE CLASSIQUE - PRO                                   
          
          case 1040:
            {
              lcd.clear();              
              while (1) {
                CP1();                
               if (initialisation == true){ModeMenuScreenMM20(); delay(50); break;}
               }
              break;
            }           
          case 1041:
            {             
              lcd.clear();
              while (1) {
                CP2();
               if (initialisation == true){ModeMenuScreenMM22(); delay(50); break;}
               }
              break;
            }
          case 1042:
            {             
              lcd.clear();
              while (1) {
                CP3();
               if (initialisation == true){ModeMenuScreenMM24(); delay(50); break;}
               }
              break;
            }
          case 1043:
            {             
              lcd.clear();
              while (1) {
                CP4();
               if (initialisation == true){ModeMenuScreenMM26(); delay(50); break;}
               }
              break;
            }
          case 1044:
            {             
              lcd.clear();
              MenuScreen0();
              break;
            }

//////////////////// LE CLASSIQUE - CHAMPION                                  
          
          case 1050:
            {
              lcd.clear();              
              while (1) {
                CC1();                
               if (initialisation == true){ModeMenuScreenMM30(); delay(50); break;}
               }
              break;
            }           
          case 1051:
            {             
              lcd.clear();
              while (1) {
                CC2();
               if (initialisation == true){ModeMenuScreenMM32(); delay(50); break;}
               }
              break;
            }
          case 1052:
            {             
              lcd.clear();
              while (1) {
                CC3();
               if (initialisation == true){ModeMenuScreenMM34(); delay(50); break;}
               }
              break;
            }
          case 1053:
            {             
              lcd.clear();
              while (1) {
                CC4();
               if (initialisation == true){ModeMenuScreenMM36(); delay(50); break;}
               }
              break;
            }
          case 1054:
            {             
              lcd.clear();
              MenuScreen0();
              break;
            }

//////////////////// LE CLASSIQUE - LEGENDE                                   
          
          case 1060:
            {
              lcd.clear();              
              while (1) {
                CL1();                
               if (initialisation == true){ModeMenuScreenMM40(); delay(50); break;}
               }
              break;
            }           
          case 1061:
            {             
              lcd.clear();
              while (1) {
                CL2();
               if (initialisation == true){ModeMenuScreenMM42(); delay(50); break;}
               }
              break;
            }
          case 1062:
            {             
              lcd.clear();
              while (1) {
                CL3();
               if (initialisation == true){ModeMenuScreenMM44(); delay(50); break;}
               }
              break;
            }
          case 1063:
            {             
              lcd.clear();
              while (1) {
                CL4();
               if (initialisation == true){ModeMenuScreenMM46(); delay(50); break;}
               }
              break;
            }
          case 1064:
            {             
              lcd.clear();
              MenuScreen0();
              break;
            }

//////////////////// Paramètres bande leds

          case 1070:
            {
              lcd.clear();
              lcd1.clear();             
              MenuScreen0();
              break;
            }                                               

//////////////////// ACTIONS DU MODE - CLASSIQUE - FACILE

          case 1100:
            {
              lcd.clear();              
              while (1) {
                CF1();
               if (initialisation == true){ModeMenuScreenMM0(); delay(50); break;}
               }
              break;
            }
          case 1101:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }
          case 1102:
            {
              lcd.clear();              
              while (1) {
                CF2();
               if (initialisation == true){ModeMenuScreenMM2(); delay(50); break;}
               }
              break;
            }
          case 1103:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }            
          case 1104:
            {
              lcd.clear();              
              while (1) {
                CF3();
               if (initialisation == true){ModeMenuScreenMM4(); delay(50); break;}
               }
              break;
            }
          case 1105:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }
          case 1106:
            {
              lcd.clear();              
              while (1) {
                CF4();
               if (initialisation == true){ModeMenuScreenMM6(); delay(50); break;}
               }
              break;
            }
          case 1107:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }

//////////////////// CLASIQUE - SEMI-PRO ////////////////////

          case 1110:
            {
              lcd.clear();              
              while (1) {
                CSP1();
               if (initialisation == true){ModeMenuScreenMM10(); delay(50); break;}
               }
              break;
            }
          case 1111:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }
          case 1112:
            {
              lcd.clear();              
              while (1) {
                CSP2();
               if (initialisation == true){ModeMenuScreenMM12(); delay(50); break;}
               }
              break;
            }
          case 1113:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }            
          case 1114:
            {
              lcd.clear();              
              while (1) {
                CSP3();
               if (initialisation == true){ModeMenuScreenMM14(); delay(50); break;}
               }
              break;
            }
          case 1115:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }
          case 1116:
            {
              lcd.clear();              
              while (1) {
                CSP4();
               if (initialisation == true){ModeMenuScreenMM16(); delay(50); break;}
               }
              break;
            }
          case 1117:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }

//////////////////// CLASIQUE - PRO ////////////////////

          case 1120:
            {
              lcd.clear();              
              while (1) {
                CP1();
               if (initialisation == true){ModeMenuScreenMM20(); delay(50); break;}
               }
              break;
            }
          case 1121:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }
          case 1122:
            {
              lcd.clear();              
              while (1) {
                CP2();
               if (initialisation == true){ModeMenuScreenMM22(); delay(50); break;}
               }
              break;
            }
          case 1123:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }            
          case 1124:
            {
              lcd.clear();              
              while (1) {
                CP3();
               if (initialisation == true){ModeMenuScreenMM24(); delay(50); break;}
               }
              break;
            }
          case 1125:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }
          case 1126:
            {
              lcd.clear();              
              while (1) {
                CP4();
               if (initialisation == true){ModeMenuScreenMM26(); delay(50); break;}
               }
              break;
            }
          case 1127:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }

//////////////////// CLASIQUE - CHAMPION ////////////////////

          case 1130:
            {
              lcd.clear();              
              while (1) {
                CC1();
               if (initialisation == true){ModeMenuScreenMM30(); delay(50); break;}
               }
              break;
            }
          case 1131:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }
          case 1132:
            {
              lcd.clear();              
              while (1) {
                CC2();
               if (initialisation == true){ModeMenuScreenMM32(); delay(50); break;}
               }
              break;
            }
          case 1133:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }            
          case 1134:
            {
              lcd.clear();              
              while (1) {
                CC3();
               if (initialisation == true){ModeMenuScreenMM34(); delay(50); break;}
               }
              break;
            }
          case 1135:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }
          case 1136:
            {
              lcd.clear();              
              while (1) {
                CC4();
               if (initialisation == true){ModeMenuScreenMM36(); delay(50); break;}
               }
              break;
            }
          case 1137:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }

//////////////////// CLASIQUE - LEGENDE ////////////////////

          case 1140:
            {
              lcd.clear();              
              while (1) {
                CL1();
               if (initialisation == true){ModeMenuScreenMM40(); delay(50); break;}
               }
              break;
            }
          case 1141:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }
          case 1142:
            {
              lcd.clear();              
              while (1) {
                CL2();
               if (initialisation == true){ModeMenuScreenMM42(); delay(50); break;}
               }
              break;
            }
          case 1143:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }            
          case 1144:
            {
              lcd.clear();              
              while (1) {
                CL3();
               if (initialisation == true){ModeMenuScreenMM44(); delay(50); break;}
               }
              break;
            }
          case 1145:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }
          case 1146:
            {
              lcd.clear();              
              while (1) {
                CL4();
               if (initialisation == true){ModeMenuScreenMM46(); delay(50); break;}
               }
              break;
            }
          case 1147:
            {
              lcd.clear();
              MenuScreen0();
              break;
            }

        }             
        delay(ButtonDelay);
        break;            
    }

///////////////// FIN DU BOUTON DE SELECTION



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    case btnNONE:
      {
        if (isMainMenu)
        {
/*          if (isBacklightOn)
          {
            if (currentMillis - previousMillis >= interval)
            {
              previousMillis = currentMillis;
              lcd.noBacklight();
              isBacklightOn = true;//false;
              ScreenNumber = 0;
              Serial.println(F("Turn Off LCD Backlight"));             
            }            
          }
*/
        }
       break;
      }           
 }
}



///////////////// FIN DU PROGRAMME DES ACTIONS DES BOUTONS



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////// CODES DES PROGRAMMES DES ACTIONS DES BOUTONS



//Menu Screens -------------------------------------------------------
//Main Menu Start-----------------------------------------------------

void MainScreen()
{   
  isMainMenu = true;
  ScreenNumber = 1;
  lcd.clear();       
  lcd.setCursor(0, 0);
  lcd.print(F("  Depassez-vous !!! "));
  lcd.setCursor(0, 1);
  lcd.print(F("        Mais        "));
  lcd.setCursor(0, 2);
  lcd.print(F("Qui sera le prochain"));
  lcd.setCursor(0, 3);  
  lcd1.clear();     
  lcd1.setCursor(0, 0);
  lcd1.print(F("--------Menu--------"));
  lcd1.setCursor(0, 2);
  lcd1.print(F("   Pour commencer   "));
  lcd1.setCursor(0, 3);  
  lcd1.print(F("    Press Select    "));    
  Serial.print(F("MainScreen -> "));
  Serial.println(ScreenNumber);  
}

//Main Menu End-----------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Menu Start---------------------------------

void MenuScreen0()
{ 
  isMainMenu = false;
  ScreenNumber = 10;    
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print(F("--------Menu--------"));
  lcd.setCursor(0, 1);
  lcd.print(F(" > Le Classique     "));
  lcd.setCursor(0, 2);
  lcd.print(F("   Le Jeu           "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Mode Survi       "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Mode Competition "));
  lcd1.setCursor(0, 1);
  lcd1.print(F("   Page parametres  "));
  lcd1.setCursor(0, 2);
  lcd1.print(F("   Page en cours    "));  
  Serial.print(F("MenuScreen0 -> "));
  Serial.println(ScreenNumber); 
}

void MenuScreen1()
{ 
  myDFPlayer.stop();
  isMainMenu = false;
  ScreenNumber = 11;
  lcd.clear();  
  lcd.setCursor(0, 0);
  lcd.print(F("--------Menu--------"));
  lcd.setCursor(0, 1);
  lcd.print(F("   Le Classique     "));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Le Jeu           "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Mode Survi       "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Mode Competition "));
  lcd1.setCursor(0, 1);
  lcd1.print(F("   Page parametres  "));
  lcd1.setCursor(0, 2);
  lcd1.print(F("   Page en cours    ")); 
  Serial.print(F("MenuScreen1 -> "));
  Serial.println(ScreenNumber);
}

void MenuScreen2()
{
  isMainMenu = false;
  ScreenNumber = 12;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("--------Menu--------"));
  lcd.setCursor(0, 1);
  lcd.print(F("   Le Classique     "));
  lcd.setCursor(0, 2);
  lcd.print(F("   Le Jeu           "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Mode Survi       "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Mode Competition "));
  lcd1.setCursor(0, 1);
  lcd1.print(F("   Page parametres  "));
  lcd1.setCursor(0, 2);
  lcd1.print(F("   Page en cours    "));
  Serial.print(F("MenuScreen2 -> "));
  Serial.println(ScreenNumber);
}

void MenuScreen3()
{
  isMainMenu = false;
  ScreenNumber = 13;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("--------Menu--------"));
  lcd.setCursor(0, 1);
  lcd.print(F("   Le Classique     "));
  lcd.setCursor(0, 2);
  lcd.print(F("   Le Jeu           "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Mode Survi       "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F(" > Mode Competition "));
  lcd1.setCursor(0, 1);
  lcd1.print(F("   Page parametres  "));
  lcd1.setCursor(0, 2);
  lcd1.print(F("   Page en cours    "));
  Serial.print(F("MenuScreen3 -> "));
  Serial.println(ScreenNumber);
}

void MenuScreen4()
{
  isMainMenu = false;
  ScreenNumber = 14;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("--------Menu--------"));
  lcd.setCursor(0, 1);
  lcd.print(F("   Le Classique     "));
  lcd.setCursor(0, 2);
  lcd.print(F("   Le Jeu           "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Mode Survi       "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Mode Competition "));
  lcd1.setCursor(0, 1);
  lcd1.print(F(" > Page parametres  "));
  lcd1.setCursor(0, 2);
  lcd1.print(F("   Page en cours    "));
  Serial.print(F("MenuScreen4 -> "));
  Serial.println(ScreenNumber);
}

void MenuScreen5()
{
  isMainMenu = false;
  ScreenNumber = 15;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("--------Menu--------"));
  lcd.setCursor(0, 1);
  lcd.print(F("   Le Classique     "));
  lcd.setCursor(0, 2);
  lcd.print(F("   Le Jeu           "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Mode Survi       "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Mode Competition "));
  lcd1.setCursor(0, 1);
  lcd1.print(F("   Page parametres  "));
  lcd1.setCursor(0, 2);
  lcd1.print(F(" >  Page en cours   "));
  Serial.print(F("MenuScreen5 -> "));
  Serial.println(ScreenNumber);
}

//Menu---end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Nbjoueurs - Mode Survi

void NbjoueursScreenMS0()
{
 isMainMenu = false;
  ScreenNumber = 100;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F(" > PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));
  Serial.print(F("NbjoueursScreenMS0 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenMS1()
{
 isMainMenu = false;
  ScreenNumber = 101;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F(" > PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));
  Serial.print(F("NbjoueursScreenMS1 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenMS2()
{
 isMainMenu = false;
  ScreenNumber = 102;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F(" > PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));
  Serial.print(F("NbjoueursScreenMS2 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenMS3()
{
 isMainMenu = false;
  ScreenNumber = 103;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F(" > PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));
  Serial.print(F("NbjoueursScreenMS3 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenMSE()
{
  isMainMenu = false;
  ScreenNumber = 104;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F(" > Exit             "));
  Serial.print(F("NbjoueursScreenMSE-> "));
  Serial.println(ScreenNumber);
}

//Nbjoueurs - Mode Survi---end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Nbjoueurs - Le Jeu

void NbjoueursScreenLJ0()
{
 isMainMenu = false;
  ScreenNumber = 110;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F(" > PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenLJ0 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenLJ1()
{
 isMainMenu = false;
  ScreenNumber = 111;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F(" > PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenLJ1 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenLJ2()
{
 isMainMenu = false;
  ScreenNumber = 112;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F(" > PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenLJ2 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenLJ3()
{
 isMainMenu = false;
  ScreenNumber = 113;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F(" > PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenLJ3 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenLJE()
{
  isMainMenu = false;
  ScreenNumber = 114;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F(" > Exit             "));
  Serial.print(F("NbjoueursScreenLJE-> "));
  Serial.println(ScreenNumber);
}

//Nbjoueurs - Le Jeu---end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Levels - Le Classique

void LevelsScreenC0()
{
 isMainMenu = false;
  ScreenNumber = 120;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F(" > Facile           "));
  lcd.setCursor(0, 1);  
  lcd.print(F("   Semi-pro         "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   Pro              "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Champion         ")); 
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Legendaire       "));  
  lcd1.setCursor(0, 1);  
  lcd1.print(F("   Exit             ")); 
  Serial.print(F("Levels1ScreenC0 -> "));
  Serial.println(ScreenNumber);  
}

void LevelsScreenC1()
{
 isMainMenu = false;
  ScreenNumber = 121;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   Facile           "));
  lcd.setCursor(0, 1);  
  lcd.print(F(" > Semi-pro         "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   Pro              "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Champion         ")); 
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Legendaire       "));  
  lcd1.setCursor(0, 1);  
  lcd1.print(F("   Exit             ")); 
  Serial.print(F("Levels1ScreenC1 -> "));
  Serial.println(ScreenNumber);  
}

void LevelsScreenC2()
{
 isMainMenu = false;
  ScreenNumber = 122;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   Facile           "));
  lcd.setCursor(0, 1);  
  lcd.print(F("   Semi-pro         "));  
  lcd.setCursor(0, 2);
  lcd.print(F(" > Pro              "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Champion         ")); 
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Legendaire       "));  
  lcd1.setCursor(0, 1);  
  lcd1.print(F("   Exit             ")); 
  Serial.print(F("Levels1ScreenC2 -> "));
  Serial.println(ScreenNumber);  
}

void LevelsScreenC3()
{
 isMainMenu = false;
  ScreenNumber = 123;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   Facile           "));
  lcd.setCursor(0, 1);  
  lcd.print(F("   Semi-pro         "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   Pro              "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Champion         ")); 
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Legendaire       "));  
  lcd1.setCursor(0, 1);  
  lcd1.print(F("   Exit             "));   
  Serial.print(F("Levels1ScreenC3 -> "));
  Serial.println(ScreenNumber);  
}

void LevelsScreenC4()
{
  isMainMenu = false;
  ScreenNumber = 124;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   Facile           "));
  lcd.setCursor(0, 1);  
  lcd.print(F("   Semi-pro         "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   Pro              "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Champion         ")); 
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F(" > Legendaire       "));  
  lcd1.setCursor(0, 1);
  lcd1.print(F("   Exit             "));
  Serial.print(F("Levels1ScreenC4 -> "));
  Serial.println(ScreenNumber);  
}

void LevelsScreenCE()
{
  isMainMenu = false;
  ScreenNumber = 125;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   Facile           "));
  lcd.setCursor(0, 1);  
  lcd.print(F("   Semi-pro         "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   Pro              "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Champion         ")); 
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Legendaire       "));  
  lcd1.setCursor(0, 1);  
  lcd1.print(F(" > Exit             "));
  Serial.print(F("Levels1ScreenCE -> "));
  Serial.println(ScreenNumber);  
}

//Levels - Le Classique---End
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Selection des Paramètres

void ParametresIL()
{
  isMainMenu = false;
  ScreenNumber = 130;
  Ice();
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F(" > Intensite Leds   "));
  lcd.setCursor(0, 1);
  lcd.print(F("   Son              "));
  lcd.setCursor(0, 2);
  lcd.print(F("   Wifi             "));  
  lcd.setCursor(0, 3);  
  lcd.print(F("   Exit             "));
  Serial.print(F("ParametresIL -> "));
  Serial.println(ScreenNumber); 
}

void ParametresS()
{
  isMainMenu = false;
  ScreenNumber = 131;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   Intensite Leds   "));
  lcd.setCursor(0, 1);
  lcd.print(F(" > Son              "));
  lcd.setCursor(0, 2);
  lcd.print(F("   Wifi             "));  
  lcd.setCursor(0, 3);  
  lcd.print(F("   Exit             "));
  Serial.print(F("ParametresS -> "));
  Serial.println(ScreenNumber); 
}

void ParametresW()
{
  isMainMenu = false;
  ScreenNumber = 132;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   Intensite Leds   "));
  lcd.setCursor(0, 1);
  lcd.print(F("   Son              "));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Wifi             "));  
  lcd.setCursor(0, 3);  
  lcd.print(F("   Exit             "));
  Serial.print(F("ParametresW -> "));
  Serial.println(ScreenNumber); 
}

void ParametresE()
{
  isMainMenu = false;
  ScreenNumber = 133;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   Intensite Leds   "));
  lcd.setCursor(0, 1);
  lcd.print(F("   Son              "));
  lcd.setCursor(0, 2);
  lcd.print(F("   Wifi             "));  
  lcd.setCursor(0, 3);  
  lcd.print(F(" > Exit             "));
  Serial.print(F("ParametresE -> "));
  Serial.println(ScreenNumber); 
}

//Levels - Le Classique---End
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Selection des Paramètres

void AffichageScores()
{
  isMainMenu = false;
  ScreenNumber = 140;
  Ice();
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F(" > Scores           "));  
  lcd.setCursor(0, 1);  
  lcd.print(F("   Exit             "));
  Serial.print(F("AffichageScores -> "));
  Serial.println(ScreenNumber); 
}

void AffichageScoresE()
{
  isMainMenu = false;
  ScreenNumber = 141;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   Scores           ")); 
  lcd.setCursor(0, 1);  
  lcd.print(F(" > Exit             "));
  Serial.print(F("AffichageScoresE -> "));
  Serial.println(ScreenNumber); 
}

//Selection des Paramètres---End
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Mode Competition

void ModeMenuScreenCPT0()
{ 
 isMainMenu = false;
  ScreenNumber = 150;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("--Mode Competition--"));
  lcd.setCursor(0, 1);                  // lcd.print(F("Allez la , retente !"));
  lcd.print(F("Retente ta chance ->")); // lcd.print(F("Vas y , vas retenter"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenCPT0 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenCPTE()
{
  isMainMenu = false;
  ScreenNumber = 151;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-----Mode Competition-----"));
  lcd.setCursor(0, 1);
  lcd.print(F("---Battez votre record--->"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenCPTE -> "));
  Serial.println(ScreenNumber);
}

//Mode Competition---End
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Selection du jeu - Mode Survi

void ModeMenuScreenMMMS0()
{ 
 isMainMenu = false;
  ScreenNumber = 1000;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-----Mode Survi-----"));
  lcd.setCursor(0, 1);
  lcd.print(F("------1 Joueur------"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMMMS0 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMMMS1()
{
  isMainMenu = false;
  ScreenNumber = 1001;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-----Mode Survi-----"));
  lcd.setCursor(0, 1);
  lcd.print(F("------1 Joueur------"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMMMS1 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMMMS2()
{ 
 isMainMenu = false;
  ScreenNumber = 1002;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-----Mode Survi-----"));
  lcd.setCursor(0, 1);
  lcd.print(F("------2 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMMMS0 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMMMS3()
{
  isMainMenu = false;
  ScreenNumber = 1003;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-----Mode Survi-----"));
  lcd.setCursor(0, 1);
  lcd.print(F("------2 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMMMS3 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMMMS4()
{ 
  isMainMenu = false;
  ScreenNumber = 1004;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-----Mode Survi-----"));
  lcd.setCursor(0, 1);
  lcd.print(F("------3 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMMMS4 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMMMS5()
{
  isMainMenu = false;
  ScreenNumber = 1005;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-----Mode Survi-----"));
  lcd.setCursor(0, 1);
  lcd.print(F("------3 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMMMS5 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMMMS6()
{ 
 isMainMenu = false;
  ScreenNumber = 1006;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-----Mode Survi-----"));
  lcd.setCursor(0, 1);
  lcd.print(F("------4 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMMMS6 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMMMS7()
{
  isMainMenu = false;
  ScreenNumber = 1007;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-----Mode Survi-----"));
  lcd.setCursor(0, 1);
  lcd.print(F("------4 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMMMS7 -> "));
  Serial.println(ScreenNumber);
}

//Selection du jeu - Mode Survi---end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Selection du jeu - Le Jeu

void ModeMenuScreenMMLJ0()
{
  isMainMenu = false;
  ScreenNumber = 1010; 
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-------Le jeu-------"));
  lcd.setCursor(0, 1);
  lcd.print(F("------1 Joueur------"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMMLJ0 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMMLJ1()
{
  isMainMenu = false;
  ScreenNumber = 1011;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-------Le jeu-------"));
  lcd.setCursor(0, 1);
  lcd.print(F("------1 Joueur------"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMMLJ1 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMMLJ2()
{
 isMainMenu = false;
  ScreenNumber = 1012;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-------Le jeu-------"));
  lcd.setCursor(0, 1);
  lcd.print(F("------2 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMMLJ2 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMMLJ3()
{
  isMainMenu = false;
  ScreenNumber = 1013;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-------Le jeu-------"));
  lcd.setCursor(0, 1);
  lcd.print(F("------2 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMMLJ3 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMMLJ4()
{
  isMainMenu = false;
  ScreenNumber = 1014;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-------Le jeu-------"));
  lcd.setCursor(0, 1);
  lcd.print(F("------3 Joueur------"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMMLJ4 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMMLJ5()
{
  isMainMenu = false;
  ScreenNumber = 1015;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-------Le jeu-------"));
  lcd.setCursor(0, 1);
  lcd.print(F("------3 Joueur------"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMMLJ5 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMMLJ6()
{
 isMainMenu = false;
  ScreenNumber = 1016;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-------Le jeu-------"));
  lcd.setCursor(0, 1);
  lcd.print(F("------4 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMMLJ6 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMMLJ7()
{
  isMainMenu = false;
  ScreenNumber = 1017;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-------Le jeu-------"));
  lcd.setCursor(0, 1);
  lcd.print(F("------4 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMMLJ7 -> "));
  Serial.println(ScreenNumber);
}

//Selection du jeu - Le Jeu---end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Nbjoueurs - Le Classique - Facile

void NbjoueursScreenCF0()
{
 isMainMenu = false;
  ScreenNumber = 1020;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F(" > PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenCF0 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenCF1()
{
 isMainMenu = false;
  ScreenNumber = 1021;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F(" > PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenCF1 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenCF2()
{
 isMainMenu = false;
  ScreenNumber = 1022;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F(" > PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenCF2 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenCF3()
{
 isMainMenu = false;
  ScreenNumber = 1023;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F(" > PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenCF3 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenCFE()
{
  isMainMenu = false;
  ScreenNumber = 1024;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F(" > Exit             "));
  Serial.print(F("NbjoueursScreenCFE-> "));
  Serial.println(ScreenNumber);
}

//Nbjoueurs - Le Classique - Facile---end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Nbjoueurs - Le Classique - Semi-Pro

void NbjoueursScreenCSP0()
{
 isMainMenu = false;
  ScreenNumber = 1030;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F(" > PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenCSP0 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenCSP1()
{
 isMainMenu = false;
  ScreenNumber = 1031;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F(" > PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenCSP1 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenCSP2()
{
 isMainMenu = false;
  ScreenNumber = 1032;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F(" > PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenCSP2 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenCSP3()
{
 isMainMenu = false;
  ScreenNumber = 1033;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F(" > PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenCSP3 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenCSPE()
{
  isMainMenu = false;
  ScreenNumber = 1034;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F(" > Exit             "));
  Serial.print(F("NbjoueursScreenCSPE-> "));
  Serial.println(ScreenNumber);
}

//Nbjoueurs - Le Classique - Semi-Pro---end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Nbjoueurs - Le Classique - Pro

void NbjoueursScreenCP0()
{
 isMainMenu = false;
  ScreenNumber = 1040;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F(" > PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenCP0 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenCP1()
{
 isMainMenu = false;
  ScreenNumber = 1041;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F(" > PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenCP1 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenCP2()
{
 isMainMenu = false;
  ScreenNumber = 1042;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F(" > PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenCP2 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenCP3()
{
 isMainMenu = false;
  ScreenNumber = 1043;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F(" > PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenCP3 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenCPE()
{
  isMainMenu = false;
  ScreenNumber = 1044;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F(" > Exit             "));
  Serial.print(F("NbjoueursScreenCPE-> "));
  Serial.println(ScreenNumber);
}

//Nbjoueurs - Le Classique - Pro---end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Nbjoueurs - Le Classique - Champion

void NbjoueursScreenCC0()
{
 isMainMenu = false;
  ScreenNumber = 1050;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F(" > PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenCC0 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenCC1()
{
 isMainMenu = false;
  ScreenNumber = 1051;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F(" > PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenCC1 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenCC2()
{
 isMainMenu = false;
  ScreenNumber = 1052;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F(" > PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenCC2 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenCC3()
{
 isMainMenu = false;
  ScreenNumber = 1053;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F(" > PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenCC3 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenCCE()
{
  isMainMenu = false;
  ScreenNumber = 1054;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F(" > Exit             "));
  Serial.print(F("NbjoueursScreenCCE-> "));
  Serial.println(ScreenNumber);
}

//Nbjoueurs - Le Classique - Champion---end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Nbjoueurs - Le Classique - Légende

void NbjoueursScreenCL0()
{
 isMainMenu = false;
  ScreenNumber = 1060;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F(" > PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenCL0 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenCL1()
{
 isMainMenu = false;
  ScreenNumber = 1061;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F(" > PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenCL1 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenCL2()
{
 isMainMenu = false;
  ScreenNumber = 1062;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F(" > PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));  
  Serial.print(F("NbjoueursScreenCL2 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenCL3()
{
 isMainMenu = false;
  ScreenNumber = 1063;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F(" > PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F("   Exit             "));   
  Serial.print(F("NbjoueursScreenCL3 -> "));
  Serial.println(ScreenNumber);  
}

void NbjoueursScreenCLE()
{
  isMainMenu = false;
  ScreenNumber = 1064;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("   PLAYER 1 / 4     ")); 
  lcd.setCursor(0, 1);
  lcd.print(F("   PLAYER 2 / 4     "));  
  lcd.setCursor(0, 2);
  lcd.print(F("   PLAYER 3 / 4     ")); 
  lcd.setCursor(0, 3);
  lcd.print(F("   PLAYER 4 / 4     "));
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(F(" > Exit             "));
  Serial.print(F("NbjoueursScreenCLE-> "));
  Serial.println(ScreenNumber);
}

//Nbjoueurs - Le Classique - Légende---end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Paramètres - Réglage Intensité de la bande leds

void RIL()
{   
  isMainMenu = false;
  ScreenNumber = 1070;
  lcd.setCursor(0,0);
  lcd.print("Page pour le reglage");
  lcd.setCursor(0,1);
  lcd.print("de l'intensite");
  lcd.setCursor(0,2);
  lcd.print("de l'eclairage");
  lcd1.setCursor(0,0);
  lcd1.print("Augmenter / bouton +");
  lcd1.setCursor(0,1);
  lcd1.print("Diminuer  / bouton -");
  lcd1.setCursor(0,3);
  lcd1.print("Pour sortir   --> OK");
  unsigned long currentMillis = millis();   
  ButtonCode = read_LCD_buttons();  
  switch (ButtonCode)
  {
    case btnUP:
      {
        previousMillis = currentMillis;
       if (digitalRead(btnUP == LOW)) {
        brightness = min(brightness + 25, 255); // Augmente la luminosité mais ne dépasse pas 255
        FastLED.setBrightness(brightness); fill_solid(leds, NUM_LEDS, CRGB::White); FastLED.show();
        delay(ButtonDelay);
        break;
      }
    }
    case btnDOWN:
      {
        previousMillis = currentMillis;
       if (digitalRead(btnDOWN == LOW)) {
        brightness = max(brightness - 25, 0); // Diminue la luminosité mais ne descend pas sous 0
        FastLED.setBrightness(brightness); fill_solid(leds, NUM_LEDS, CRGB::White); FastLED.show();
        delay(ButtonDelay);
        break;
      }
    }
  }   
  Serial.print(F("MainScreenRIL -> "));
  Serial.println(ScreenNumber);  
}

//Nbjoueurs - Le Classique - Légende---end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Selection - Mode Menu - Classic Facile

void ModeMenuScreenMM0()
{  
  isMainMenu = false;
  ScreenNumber = 1100;
  lcd1.clear();
  lcd.clear();   
  lcd.setCursor(0, 0);
  lcd.print(F("-Classique - Facile-"));
  lcd.setCursor(0, 1);
  lcd.print(F("------1 Joueur------"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMM0 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM1()
{ 
  isMainMenu = false;
  ScreenNumber = 1101;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-Classique - Facile-"));
  lcd.setCursor(0, 1);
  lcd.print(F("------1 Joueur------"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMM1 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM2()
{  
  isMainMenu = false;
  ScreenNumber = 1102;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-Classique - Facile-"));
  lcd.setCursor(0, 1);
  lcd.print(F("------2 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMM2 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM3()
{
  isMainMenu = false;
  ScreenNumber = 1103;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-Classique - Facile-"));
  lcd.setCursor(0, 1);
  lcd.print(F("------2 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMM3 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM4()
{   
  isMainMenu = false;
  ScreenNumber = 1104;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-Classique - Facile-"));
  lcd.setCursor(0, 1);
  lcd.print(F("------3 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMM4 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM5()
{
  isMainMenu = false;
  ScreenNumber = 1105;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-Classique - Facile-"));
  lcd.setCursor(0, 1);
  lcd.print(F("------3 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMM5 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM6()
{
  isMainMenu = false;
  ScreenNumber = 1106;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-Classique - Facile-"));
  lcd.setCursor(0, 1);
  lcd.print(F("------4 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMM6 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM7()
{
  isMainMenu = false;
  ScreenNumber = 1107;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("-Classique - Facile-"));
  lcd.setCursor(0, 1);
  lcd.print(F("------4 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMM7 -> "));
  Serial.println(ScreenNumber);
}

//Selection---Mode---Menu---Classic---F---end
/////////////////////////////////////////////
//Selection---Mode---Menu---Classic---SP-----

void ModeMenuScreenMM10()
{
  isMainMenu = false;
  ScreenNumber = 1110;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Semi-Pro"));
  lcd.setCursor(0, 1);
  lcd.print(F("------1 Joueur------"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMM10 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM11()
{
  isMainMenu = false;
  ScreenNumber = 1111;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Semi-Pro"));
  lcd.setCursor(0, 1);
  lcd.print(F("------1 Joueur------"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMM11 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM12()
{
  isMainMenu = false;
  ScreenNumber = 1112;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Semi-Pro"));
  lcd.setCursor(0, 1);
  lcd.print(F("------2 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMM12 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM13()
{
  isMainMenu = false;
  ScreenNumber = 1113;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Semi-Pro"));
  lcd.setCursor(0, 1);
  lcd.print(F("------2 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMM13 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM14()
{
  isMainMenu = false;
  ScreenNumber = 1114;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Semi-Pro"));
  lcd.setCursor(0, 1);
  lcd.print(F("------3 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMM14 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM15()
{
  isMainMenu = false;
  ScreenNumber = 1115;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Semi-Pro"));
  lcd.setCursor(0, 1);
  lcd.print(F("------3 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMM15 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM16()
{
  isMainMenu = false;
  ScreenNumber = 1116;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Semi-Pro"));
  lcd.setCursor(0, 1);
  lcd.print(F("------4 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMM16 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM17()
{
  isMainMenu = false;
  ScreenNumber = 1117;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Semi-Pro"));
  lcd.setCursor(0, 1);
  lcd.print(F("------4 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMM17 -> "));
  Serial.println(ScreenNumber);
}

//Selection---Mode---Menu---Classic---SP--end
/////////////////////////////////////////////
//Selection---Mode---Menu---Classic---P------

void ModeMenuScreenMM20()
{
  isMainMenu = false;
  ScreenNumber = 1120;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Pro     "));
  lcd.setCursor(0, 1);
  lcd.print(F("------1 Joueur------"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMM20 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM21()
{
  isMainMenu = false;
  ScreenNumber = 1121;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Pro     "));
  lcd.setCursor(0, 1);
  lcd.print(F("------1 Joueur------"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMM21 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM22()
{
  isMainMenu = false;
  ScreenNumber = 1122;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Pro     "));
  lcd.setCursor(0, 1);
  lcd.print(F("------2 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMM22 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM23()
{
  isMainMenu = false;
  ScreenNumber = 1123;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Pro     "));
  lcd.setCursor(0, 1);
  lcd.print(F("------2 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMM23 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM24()
{
  isMainMenu = false;
  ScreenNumber = 1124;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Pro     "));
  lcd.setCursor(0, 1);
  lcd.print(F("------3 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMM24 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM25()
{
  isMainMenu = false;
  ScreenNumber = 1125;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Pro     "));
  lcd.setCursor(0, 1);
  lcd.print(F("------3 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMM25 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM26()
{
  isMainMenu = false;
  ScreenNumber = 1126;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Pro     "));
  lcd.setCursor(0, 1);
  lcd.print(F("------4 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMM26 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM27()
{
  isMainMenu = false;
  ScreenNumber = 1127;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Pro     "));
  lcd.setCursor(0, 1);
  lcd.print(F("------4 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMM27 -> "));
  Serial.println(ScreenNumber);
}

//Selection---Mode---Menu---Classic---P---end
/////////////////////////////////////////////
//Selection---Mode---Menu---Classic---C------

void ModeMenuScreenMM30()
{
  isMainMenu = false;
  ScreenNumber = 1130;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Champion"));
  lcd.setCursor(0, 1);
  lcd.print(F("------1 Joueur------"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMM30 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM31()
{
  isMainMenu = false;
  ScreenNumber = 1131;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Champion"));
  lcd.setCursor(0, 1);
  lcd.print(F("------1 Joueur------"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMM31 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM32()
{
  isMainMenu = false;
  ScreenNumber = 1132;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Champion"));
  lcd.setCursor(0, 1);
  lcd.print(F("------2 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMM32 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM33()
{
  isMainMenu = false;
  ScreenNumber = 1133;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Champion"));
  lcd.setCursor(0, 1);
  lcd.print(F("------2 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMM33 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM34()
{
  isMainMenu = false;
  ScreenNumber = 1134;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Champion"));
  lcd.setCursor(0, 1);
  lcd.print(F("------3 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMM34 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM35()
{
  isMainMenu = false;
  ScreenNumber = 1135;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Champion"));
  lcd.setCursor(0, 1);
  lcd.print(F("------3 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMM35 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM36()
{
  isMainMenu = false;
  ScreenNumber = 1136;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Champion"));
  lcd.setCursor(0, 1);
  lcd.print(F("------4 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMM36 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM37()
{
  isMainMenu = false;
  ScreenNumber = 1137;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Champion"));
  lcd.setCursor(0, 1);
  lcd.print(F("------4 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMM37 -> "));
  Serial.println(ScreenNumber);
}

//Selection--Mode--Menu--Classic-Champion-end
/////////////////////////////////////////////
//Selection--Mode--Menu--Classic-Légende-----

void ModeMenuScreenMM40()
{
  isMainMenu = false;
  ScreenNumber = 1140;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Legende "));
  lcd.setCursor(0, 1);
  lcd.print(F("------1 Joueur------"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMM40 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM41()
{
  isMainMenu = false;
  ScreenNumber = 1141;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Legende "));
  lcd.setCursor(0, 1);
  lcd.print(F("------1 Joueur------"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMM41 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM42()
{
  isMainMenu = false;
  ScreenNumber = 1142;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Legende "));
  lcd.setCursor(0, 1);
  lcd.print(F("------2 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMM42 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM43()
{
  isMainMenu = false;
  ScreenNumber = 1143;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Legende "));
  lcd.setCursor(0, 1);
  lcd.print(F("------2 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMM43 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM44()
{
  isMainMenu = false;
  ScreenNumber = 1144;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Legende "));
  lcd.setCursor(0, 1);
  lcd.print(F("------3 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMM44 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM45()
{
  isMainMenu = false;
  ScreenNumber = 1145;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Legende "));
  lcd.setCursor(0, 1);
  lcd.print(F("------3 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMM45 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM46()
{
  isMainMenu = false;
  ScreenNumber = 1146;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Legende "));
  lcd.setCursor(0, 1);
  lcd.print(F("------4 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F(" > Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F("   Menu principal   ")); 
  Serial.print(F("ModeMenuScreenMM46 -> "));
  Serial.println(ScreenNumber);
}

void ModeMenuScreenMM47()
{
  isMainMenu = false;
  ScreenNumber = 1147;
  lcd1.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Classique - Legende "));
  lcd.setCursor(0, 1);
  lcd.print(F("------4 Joueurs-----"));
  lcd.setCursor(0, 2);
  lcd.print(F("   Recommencer      "));
  lcd.setCursor(0, 3);
  lcd.print(F(" > Menu principal   "));
  Serial.print(F("ModeMenuScreenMM47 -> "));
  Serial.println(ScreenNumber);
}

//Selection--Mode--Menu--Classic-Légende--end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Code Ok car suite du programme pour lancer le jeux
