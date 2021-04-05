#include <FastLED.h>

// How many leds in your strip?
#define LED_COUNT 30

int r=252;
int g=0;
int b=0;
#define NUM_LEDS 60
#define decayDELAY 8
#define MicSamples (1024*2)
#define colorDECAY 10
int audio = A0;
#define SCROLL_SPEED 50
#define DATA_PIN 6
CRGB leds[NUM_LEDS];


void setup() {
 delay( 3000 ); // power-up safety delay


FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
FastLED.setBrightness(200);

 for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = CRGB(0, 0, 0);
  FastLED.show();
 pinMode(audio, INPUT);
  Serial.begin(9600);
}



void loop() {
   int s = processAudio();
   if (s>110){
fill_solid( leds[20], 4, CRGB::Red);
 FastLED.show();  
 FastLED.delay(colorDECAY);}

}



  
 void fill_solid( struct CRGB * leds, int numToFill, const struct CRGB& color)


void cascadeF(int numLED, const struct CRGB &color){
  for (int i=1; i<numLED+5; i++){
    leds[i] = color; FastLED.show(); FastLED.delay(5);
    }
  for (int i=numLED+5; i>0; i--){
    
    leds[i] = CRGB::Black; FastLED.show(); FastLED.delay(5);
    }
  }


void cascadeB(int numLED, const struct CRGB &color){
int tillR = NUM_LEDS - numLED;
   for (int i=NUM_LEDS; i>tillR-5; i--){
       leds[i] = color; FastLED.show(); FastLED.delay(5);
   
    }
  for (int i=tillR-5; i<NUM_LEDS; i++){
  leds[i] = CRGB::Black; FastLED.show(); FastLED.delay(5);
    }

  }



void musicViz(){
int signalAvg = processAudio();
if (signalAvg>45 && signalAvg<80){
  cascadeF(5, CRGB::Violet);
   cascadeB(5, CRGB::Blue);
  }
else if (signalAvg>80 && signalAvg<110){
  cascadeF(10, CRGB::PaleVioletRed);
  cascadeB(10, CRGB::Green);
  
}

else if (signalAvg>110 && signalAvg<150){
  cascadeF(15, CRGB::MistyRose);
  cascadeB(15, CRGB::MidnightBlue);

  
}
 else if (signalAvg>150 && signalAvg<190){
  cascadeF(20, CRGB::HotPink);
   cascadeB(20, CRGB::Red);
}
     
else if (signalAvg>190 && signalAvg<240){
  cascadeF(22, CRGB::Pink);
  cascadeB(22, CRGB::Purple);
}
   else if (signalAvg>240 && signalAvg<310) {
       cascadeF(25, CRGB::Red);
        cascadeB(25, CRGB::Green);
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



 void lup(){
      int s = processAudio();

     if((s>=110)&&(s<=180))
  {
    leds[29]=CRGB (20, 135, 217);
    leds[30]=CRGB (20, 135, 217);
     leds[31]=CRGB (20, 135, 217);
    
  }
  else if((s>=190)&&(s<=240))
   {
     leds[29]=CRGB (20, 217, 30);
    leds[30]=CRGB (20, 217, 30);
     leds[31]=CRGB (20, 217, 30);
   }
 
  
    else {
   leds[29] = CRGB ( r,g,b);
     leds[30] = CRGB ( r,g,b);
    
    
    
    }
    FastLED.show();
    delay(25);
}
