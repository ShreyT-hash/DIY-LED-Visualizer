const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
unsigned long lastUpdate;
#define NUM_LEDS    148

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

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
   //double volts = (peakToPeak * 5.0) / 1024;  // convert to volts
   int val = map(peakToPeak, 0, 1024, 0, NUM_LEDS); // maps peak values to # b/w 0 and NUM_LEDS 
  //Serial.println(val);
  return val;
  
  
  }
