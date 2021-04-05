
#include <FastLED.h>

// How many leds do you want to light up?
#define NUM_LEDS 149

// Time it takes for lights to switch off 
#define decayDELAY 20
#define colorDECAY 10

// Audio sampling rate
#define MicSamples (1024*2)

// Speed at which light pulses through
#define SCROLL_SPEED 8

// Declaring time constants
unsigned long lastTIME;
int intervaLL = 14000;

// Data pin that is plugged to arduino
#define DATA_PIN 6

// Declaring an array of NUM_LEDS
CRGB leds[NUM_LEDS];



void setup() {
 delay( 3000 ); // power-up safety delay
 
 FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
 FastLED.setBrightness(230); // set brightness value (0-250)

 for (int i = 0; i < NUM_LEDS; i++){ // clears LEDs at the start
    leds[i] = CRGB(0, 0, 0);
  FastLED.show();
 }            
 
 pinMode(audio, INPUT); taking audio as input to the pin
 Serial.begin(9600); // load up serial monitor
}


void loop() {

pulsess(); // 3 led light pulse 

// clears strip every 14 seconds to prevent overloading input
if (millis() - lastTIME >= intervaLL
  for (int i = 0; i < NUM_LEDS; i++){
   leds[i] = CRGB(0, 0, 0);
  FastLED.show();
 lastTIME = millis();
  }

}


// Goes upto certain light and 'cascades' back down 
void cascade(int numLED, const struct CRGB &color){
  for (int i=15; i<numLED; i++){
    leds[i] = color; FastLED.show(); FastLED.delay(5);
    }
  for (int i=numLED; i>14; i--){
    
    leds[i] = CRGB::Black; FastLED.show(); FastLED.delay(5);
    }
  }





// Got code from online blog, allows me to sample audio and split into different levels (1-250)
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
