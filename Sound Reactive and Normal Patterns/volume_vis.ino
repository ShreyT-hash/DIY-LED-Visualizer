#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 148
#define decayDELAY 20
#define MicSamples (1024*2)
#define colorDECAY 10
#define SCROLL_SPEED 8
unsigned long lastTIME;
int intervaLL = 14000;
int intervaLL2 = 45000;
int i = 0;
int counter =0;
  int audio = A0;
unsigned long lastUpdate;

#define DATA_PIN 6
CRGB leds[NUM_LEDS];


void setup() {
 delay( 3000 ); // power-up safety delay


FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
FastLED.setBrightness(110);

 for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = CRGB(0, 0, 0);
  FastLED.show();
 pinMode(audio, INPUT);
  Serial.begin(9600);
}


void loop() {
//FastLED.show();
//while (millis() < 20000){
// pulsess();
////
//// 
//pulsess();
//if (millis() - lastTIME >= intervaLL){
//  for (int i = 0; i < NUM_LEDS; i++){
//   leds[i] = CRGB(0, 0, 0);
//  FastLED.show();
// lastTIME = millis();
musicViz();
colorViz();
   
}


  

  


void cascade(int numLED, const struct CRGB &color){
  for (int i=45; i<numLED; i++){
    leds[i] = color; FastLED.show(); FastLED.delay(5);
    }
  for (int i=numLED; i>14; i--){
    
    leds[i] = CRGB::Black; FastLED.show(); FastLED.delay(5);
    }
  }





void musicViz(){
int signalAvg = processAudio();
if (signalAvg>45 && signalAvg<80){
  cascade(61, CRGB::Purple);
  }
else if (signalAvg>80 && signalAvg<110){
  cascade(83, CRGB::Blue);
  
}

else if (signalAvg>110 && signalAvg<150){
  cascade(92, CRGB::Green);
  
}
 else if (signalAvg>150 && signalAvg<170){
  cascade(105, CRGB::HotPink);
}
     
else if (signalAvg>190 && signalAvg<240){
  cascade(120, CRGB::LightCoral);
}
   else if (signalAvg>240 && signalAvg<280) {
       cascade(134, CRGB::PaleVioletRed);
   }
 
   else {
  fill_solid( leds, NUM_LEDS, CRGB::Black);
     FastLED.show();  
  delay(2);
   }
  
 
  }


void colorViz(){
  int signalAvg = processAudio();
if (signalAvg>80 && signalAvg<110){
  fill_solid( leds, NUM_LEDS, CRGB::Red);
   //fill_gradient_RGB( leds, NUM_LEDS, CRGB::Red, CRGB::Green, CRGB::White);
 FastLED.show();  
 FastLED.delay(colorDECAY);


} else if (signalAvg>110 && signalAvg<150) {
   fill_solid( leds, NUM_LEDS, CRGB::Green);
    //fill_gradient_RGB( leds, NUM_LEDS, CRGB::Magenta, CRGB::White, CRGB::Pink);
 FastLED.show();  
 FastLED.delay(colorDECAY);

  }
  else if (signalAvg>150 && signalAvg<190){
     fill_solid( leds, NUM_LEDS, CRGB::White);
 FastLED.show();  
 FastLED.delay(colorDECAY);

      }
     
    
    
    else if (signalAvg>190 && signalAvg<240){
       fill_solid( leds, NUM_LEDS, CRGB::Blue);
 FastLED.show();  
 FastLED.delay(colorDECAY);

      }
   else if (signalAvg>240 && signalAvg<310){
     //  fill_solid( leds, NUM_LEDS, CRGB::Cyan);
      fill_gradient_RGB( leds, NUM_LEDS, CRGB::Green, CRGB::Cyan);
 FastLED.show();  
 FastLED.delay(colorDECAY);}
else {
   fill_solid( leds, NUM_LEDS, CRGB::Black);
     FastLED.show();  
  delay(2);


}}
  
  
  
  




int processAudio(){
  long signalAvg = 0, signalMax = 0, signalMin = 1024, t0 = millis();
    for (int i = 0; i < MicSamples; i++)
    {
        
 int ai = analogRead(audio);
        signalMin = min(signalMin, ai);
        signalMax = max(signalMax, ai);
        signalAvg += ai;
    }
    signalAvg /= (MicSamples * 1.4);
    
return signalAvg;
Serial.println(signalAvg);


  }



void pulse(){
   int signalAvg = processAudio();
   if (signalAvg > 150){
    leds[0] = CRGB::Blue;
   
  for (int i = NUM_LEDS; i>0; i--){
    leds[i] = CRGB::Blue;
   
 leds[i] = leds [i -3];
 
  
 
    FastLED.show();
    delay(400);
    
    }
    
    }
  else{
   fill_solid( leds, NUM_LEDS, CRGB::Black);
     FastLED.show();  
  delay(20);}}
    

// 
// FAST RN
  void pulsess(){
   int signalAvg = processAudio();
  

  if (millis() - lastUpdate > SCROLL_SPEED) {
    lastUpdate += SCROLL_SPEED;
    for (int i = NUM_LEDS - 1; i > 4; i--){
      leds[i] = leds[i - 4];
   
    
  }}

 for(int i = 0; i < 4; i++) {
 

if (signalAvg >= 90 && signalAvg <= 140){
  
    leds[i] = CRGB(153, 255, 153);
  }
  else if (signalAvg >= 141 && signalAvg <= 180){
   // leds[i] = CRGB::Khaki;
      leds[i] = CRGB(51, 127, 255);
    }
 else if (signalAvg >= 181 && signalAvg <= 190){
   //leds[i] = CRGB::HotPink;
   leds[i] = CRGB(17, 44, 184);
  }
  else if (signalAvg >= 191 && signalAvg <= 230){
    leds[i] = CRGB::Cyan;
    }
    else if (signalAvg >= 231 && signalAvg <= 270){
      leds[i]=CRGB::PaleVioletRed;
      }
 
  
  else{
    leds[i] = CRGB::Black;
  }
    
  }
   FastLED.show();
  }
  
  

void juggle() {
  
  // eight colored dots, weaving in and out of sync with each other
 
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
 
  for( int i = 0; i < 8; i++) {
    
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
    
  }}




    void sineMap(){
         int signalAvg = processAudio();
  if (signalAvg > 120 && signalAvg <140){
      if (millis() - lastUpdate > SCROLL_SPEED) {
    lastUpdate += SCROLL_SPEED;
    for (int i = 0; i<NUM_LEDS; i++){
      leds[i] = CRGB::Blue;
      FastLED.show();
      leds[i] = CRGB::Black;
      delay(14);}}}
      
 
  else if  (signalAvg > 190 && signalAvg < 210){
      if (millis() - lastUpdate > SCROLL_SPEED) {
    lastUpdate += SCROLL_SPEED;
     for (int i = 0; i<NUM_LEDS; i++){
      leds[i] = CRGB::HotPink;
      FastLED.show();
      leds[i] = CRGB::Black;
      delay(14);
     }}}

      else if (signalAvg > 190 && signalAvg < 210){
       for (int i = 0; i<NUM_LEDS; i++){
      leds[i] = CRGB::Red;
      FastLED.show();
      leds[i] = CRGB::Black;
      delay(14);
     }
      }
      else if (signalAvg > 230 && signalAvg < 270){
      for (int i = 0; i<NUM_LEDS; i++){
      leds[i] = CRGB::Purple;
      FastLED.show();
      leds[i] = CRGB::Black;
      delay(14);
     }
      }}
    
   
void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( 0, 255, 192);
}
      

 
  
