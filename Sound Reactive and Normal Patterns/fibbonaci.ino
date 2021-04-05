// Creates a fibbonacci sequence on the LED Strip 

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
  
}


void fibbonacci(){

int a = 0;
int b = 1;
int sum;

for (int i = 0; i<12; i++){

sum = a + b;
Serial.println(sum);
  fill_solid( leds, sum, CRGB::Cyan);
  // Change the color here (from CYAN to any CRGB value)
delay(400);
FastLED.show();  
a = b;
b = sum;


  }
  
  
  
  }
