#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 20
#define MicSamples (1024*2)
#define SCROLL_SPEED 20

int audio = A0;
unsigned long rr;

#define DATA_PIN 6
CRGB leds[NUM_LEDS];


void setup() {
delay( 3000 ); // power-up safety delay


FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
FastLED.setBrightness(60);

 for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = CRGB(0, 0, 0);
  FastLED.show();
  Serial.begin(9600);
}

void loop() {
 pulsating();
 

}


void pulsating(){
 rr = millis();
    
  
    leds[0]=CRGB::Red;
    
  for (int i = NUM_LEDS; i>0; i--)
    leds[i] = CRGB::Red;
    
  
  
  

  if (millis() - rr > SCROLL_SPEED) {
    rr += SCROLL_SPEED;
    for (int i = NUM_LEDS - 1; i > 0; i--)
      leds[i] = leds[i - 1];
    FastLED.show();
    delay(200);
  }

}


  

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


  }
