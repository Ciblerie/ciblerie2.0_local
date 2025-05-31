
// Code à copier dans chaque cible pour l'animation ///////////////////////////

// ✅ Modification de CodeLedAleatoire() pour ne fonctionner que si disableLedAnimation est faux
void CodeLedAleatoire() {
  if (disableLedAnimation) { // Ne fait rien si désactivé
    return; 
  }
  if (disableSonAnimation) { // Ne fait rien si désactivé
    return; 
  }
  int lamp_aleatoire;
  lamp_aleatoire = random(0 , 3);
  switch (lamp_aleatoire) {

  case 0:
    if(millis()-Time3S>=Period3S){
      Ice();
      FastLED.show();
      Time3S=millis();}
  case 1:
    if(millis()-Time3S>=Period3S){
      XYMatrix();
      FastLED.show();
      Time3S=millis();}
  case 2:    
    if(millis()-Time3S>=Period3S){      
      Pride();
      FastLED.show();
      Time3S=millis();}
/*
  case 3:    
    if(millis()-Time3S>=Period3S){      
      //mp3_play(20);
      Time3S=millis();}
  case 4:    
    if(millis()-Time3S>=Period3S){      
      //mp3_play(21);
      Time3S=millis();}
  case 5:    
    if(millis()-Time3S>=Period3S){     
      //mp3_play(23);
      Time3S=millis();}
  case 6:    
    if(millis()-Time3S>=Period3S){      
      //mp3_play(24);
      Time3S=millis();}
*/
  }  
}


void Ice()
{
  EVERY_N_MILLISECONDS(50) {    
    // Create a new HSV color for led[0]
    leds[0] = CHSV(160, random8(), random8(brightness, brightness)); //100 & 255   
    // Copy each pixel to the next one, starting at the far end
    // thereby 'moving' the pattern along the strip
    for (int i = NUM_LEDS - 1; i > 0; i--) {
      leds[i] = leds[i - 1];
    }
  }  
  FastLED.show();
}


void XYMatrix()
{
  static uint8_t hue = 0;
  Serial.print("x");
  //First slide the led in one direction
  for(int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red 
    leds[i] = CHSV(hue++, brightness, brightness); // 255 & 255
    // Show the leds
    FastLED.show(); 
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
  Serial.print("x");
  // Now go in the other direction.  
  for(int i = (NUM_LEDS)-1; i >= 0; i--) {   
    // Set the i'th led to red 
    leds[i] = CHSV(hue++, brightness, brightness); // 255 & 255
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
}


void Pride() 
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
  
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;
  
  for( uint16_t i = 0 ; i < NUM_LEDS; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    CRGB newcolor = CHSV( hue8, sat8, bri8);
    
    uint16_t pixelnumber = i;
    pixelnumber = (NUM_LEDS-1) - pixelnumber;
    
    nblend( leds[pixelnumber], newcolor, 64);
  }
}

