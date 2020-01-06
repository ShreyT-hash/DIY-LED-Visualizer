#include <FastLED.h>
#define NUM_LEDS 150
#define DATA_PIN 6
#define counter = 0;


CRGB leds[NUM_LEDS];


void setup() {
   delay( 3000 ); // power-up safety delay

FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
FastLED.setBrightness(20);

 for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = CRGB(0, 0, 0);
  FastLED.show();
  Serial.begin(9600);

}

void loop() {
//  fibbonacci();
//  
//fill_solid( leds, 1, CRGB::Blue);
//delay(400);
//FastLED.show();
//fill_solid( leds, 3, CRGB::Red);
//delay(700);
//FastLED.show();
//fill_solid( leds, 5, CRGB::Green);
//delay(700);
//FastLED.show();
//fill_solid( leds, 8, CRGB::HotPink);
//delay(700);
//FastLED.show();
//fill_solid( leds, 13, CRGB::Cyan);
//delay(700);
//FastLED.show();
//fill_solid( leds, 21, CRGB::SpringGreen);
//delay(700);
//FastLED.show();
//fill_solid( leds, 34, CRGB::Violet);
//delay(700);
//FastLED.show();
//fill_solid( leds, 55, CRGB::MidnightBlue);
//delay(700);
//FastLED.show();
//fill_solid( leds, 88, CRGB::MediumOrchid);
//delay(700);
//FastLED.show();
  
}


void fibbonacci(){

int a = 0;
int b = 1;
int sum;

for (int i = 0; i<12; i++){

sum = a + b;
Serial.println(sum);
  fill_solid( leds, sum, CRGB::Cyan);
  
delay(400);
FastLED.show();  
a = b;
b = sum;


  }
  
  
  
  }
