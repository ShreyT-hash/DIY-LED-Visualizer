#include <FastLED.h>

// Combination of coded sound reactive patterns and non sound reactive patterns
// Code to cycle through patterns and some of the patterns are courtesy of
// Mark Kriegsman, December 2014

// Current patterns include 
#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    6
//#define CLK_PIN   4
#define LED_TYPE    NEOPIXEL
#define COLOR_ORDER GRB
#define NUM_LEDS    148
#define MicSamples (1024*2)

#define brightness 235 
#define SCROLL_SPEED 8
#define cChange 70
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
unsigned long lastUpdate;

int audio = A0;

CRGB leds[NUM_LEDS];


#define BRIGHTNESS          110
#define FRAMES_PER_SECOND  120

uint8_t paletteIndex = 0;
// Gradient to create a christmas color 
DEFINE_GRADIENT_PALETTE( christmas_candy_gp ) {
    0, 255,255,255,
   25, 255,  0,  0,
   51, 255,255,255,
   76,   0, 55,  0,
  102, 255,255,255,
  127, 255,  0,  0,
  153, 255,255,255,
  178,   0, 55,  0,
  204, 255,255,255,
  229, 255,  0,  0,
  255, 255,255,255};

// Gradient to create a sunset color
DEFINE_GRADIENT_PALETTE( Sunset_Real_gp ) {
    0, 120,  0,  0,
   22, 179, 22,  0,
   51, 255,104,  0,
   85, 167, 22, 18,
  135, 100,  0,103,
  198,  16,  0,130,
  255,   0,  0,160};
 



DEFINE_GRADIENT_PALETTE( bhw1_28_gp ) {
    0,  75,  1,221,
   30, 252, 73,255,
   48, 169,  0,242,
  119,   0,149,242,
  170,  43,  0,242,
  206, 252, 73,255,
  232,  78, 12,214,
  255,   0,149,242};


  CRGBPalette16 xmas = christmas_candy_gp;
  
  CRGBPalette16 coolP = bhw1_28_gp;

  CRGBPalette16 sunset = Sunset_Real_gp;
  
void setup() {
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  
 FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
 

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { pulsess,xmasPalette, coolPalette, rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( 220 ) { nextPattern(); } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}


void xmasPalette(){
 
 fill_palette(leds, NUM_LEDS, paletteIndex, 255 / NUM_LEDS, xmas, 150, LINEARBLEND);
  
  EVERY_N_MILLISECONDS(30){
    paletteIndex++;
  }


 
}


void coolPalette(){
 
 fill_palette(leds, NUM_LEDS, paletteIndex, 255 / NUM_LEDS, coolP, 150, LINEARBLEND);
  
  EVERY_N_MILLISECONDS(30){
    paletteIndex++;
  }


 
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 5, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 32;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

  





int audioSample(){
  unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   //Serial.println(peakToPeak);
   double volts = (peakToPeak * 5.0) / 1024;  // convert to volts
   int val = map(peakToPeak, 0, 1024, 0, NUM_LEDS);
  //Serial.println(val);
  return val;
  
  
  }
// Every 50 ms, based on audio level, led [i] to led[i-4] is fed a gradient of colors from a pallette,
// and this set pulsates through the strip
void pulsess(){
   int signalAvg = audioSample();
  

  if (millis() - lastUpdate > SCROLL_SPEED) {
    lastUpdate += SCROLL_SPEED;
    for (int i = NUM_LEDS - 1; i > 4; i--){
      leds[i] = leds[i - 4];
   
    
  }}

 for(int i = 0; i < 4; i++) {
 

if (signalAvg >= 20 && signalAvg <= 45){
  
  //  leds[i] = CHSV(gHue, 100, 235);
  leds[i] = ColorFromPalette(sunset, gHue);
    EVERY_N_MILLISECONDS(cChange){
      gHue++;
      }
  }
  else if (signalAvg >= 45 && signalAvg <= 65){
   //   leds[i] = CHSV(gHue+40, 100, 235);
      leds[i] = ColorFromPalette(sunset, gHue+30);
      EVERY_N_MILLISECONDS(cChange){
      gHue++;
      }
    }
 else if (signalAvg >= 66 && signalAvg <= 85){
   //leds[i] = CRGB::HotPink;
 //  leds[i] = CHSV(gHue+80, 100, 235);
 leds[i] = ColorFromPalette(sunset, gHue+60);
   EVERY_N_MILLISECONDS(cChange){
      gHue++;
      }
  }
  else if (signalAvg >= 86 && signalAvg <= 106){
   // leds[i] = CHSV(gHue+120, 100, 235);
    leds[i] = ColorFromPalette(sunset, gHue+90);
    EVERY_N_MILLISECONDS(cChange){
      gHue++;
      }
   }
    else if (signalAvg >= 107 && signalAvg <= 147){
     // leds[i]=CHSV(gHue+160, 100, 235);
     leds[i] = ColorFromPalette(sunset, gHue+120);
       EVERY_N_MILLISECONDS(cChange){
      gHue++;
      }
      }
 
  
  else{
    leds[i] = CRGB::Black;
  }
    
  }
   FastLED.show();

   EVERY_N_SECONDS(9){
   
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  }
    }
 
  
  
  
