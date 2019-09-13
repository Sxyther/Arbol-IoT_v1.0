#include "noise.h"


/******************************************************************/
/******************************************************************/
int noiseReadValue(void)
{
  unsigned char u8LocalCounter;
  int u32sample=0;
  int u32Acumulated=0;

  for(u8LocalCounter=0;u8LocalCounter<NOISE_SAMPLE_NUMBER;u8LocalCounter++)
  {
    u32sample = (analogRead(AUDIO_IN)-512);
    u32Acumulated += abs(u32sample);    
    delay(50);
  }
  u32Acumulated = u32Acumulated/NOISE_SAMPLE_NUMBER;
  
  return(u32Acumulated);
}


/******************************************************************/
/******************************************************************/
void testSensor(void)
{
  int Sample=0;
  int absolute=0;
  Sample = (analogRead(AUDIO_IN)-512);
  absolute = abs(Sample);
  Serial.println(absolute);  
}
