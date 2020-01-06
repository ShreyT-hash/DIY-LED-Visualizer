#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 100
#define decayDELAY 8
#define MicSamples (1024*2)
#define colorDECAY 10
int audio = A0;

#define DATA_PIN 6
CRGB leds[NUM_LEDS];


void setup() {
 delay( 3000 ); // power-up safety delay


FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
FastLED.setBrightness(50);

 for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = CRGB(0, 0, 0);
  FastLED.show();
 pinMode(audio, INPUT);
  Serial.begin(9600);
}

void loop() {

   long signalAvg = 0, signalMax = 0, signalMin = 1024, t0 = millis();
    for (int i = 0; i < MicSamples; i++)
    {
        
 int ai = analogRead(audio);
        signalMin = min(signalMin, ai);
        signalMax = max(signalMax, ai);
        signalAvg += ai;
    }
    signalAvg /= (MicSamples * 1.4);
 
Serial.println(signalAvg);

//  for (int i=0; i<NUM_LEDS; i++){
//
//
//  leds[i] = CRGB::Green; FastLED.show(); delay(2);
//  leds[i+1] = CRGB::Green; FastLED.show(); delay(2);
//  leds[i+2] = CRGB::Green; FastLED.show(); delay(2);
//  leds[i+3] = CRGB::Green; FastLED.show(); delay(2);
//
// 
//    leds[i] =  CRGB::Black;  FastLED.show();  delay(2);
//  leds[i+1] = CRGB::Black;   FastLED.show();}  delay(2);
//  
//}
if (signalAvg>80 && signalAvg<110){
  fill_solid( leds, NUM_LEDS, CRGB::Red);
 FastLED.show();  
 FastLED.delay(colorDECAY);


} else if (signalAvg>110 && signalAvg<150) {
   fill_solid( leds, NUM_LEDS, CRGB::Green);
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
       fill_solid( leds, NUM_LEDS, CRGB::Cyan);
 FastLED.show();  
 FastLED.delay(colorDECAY);}
else {
   fill_solid( leds, NUM_LEDS, CRGB::Black);
     FastLED.show();  
  delay(2);

}
}
 
