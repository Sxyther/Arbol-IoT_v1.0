#include <Arduino.h>


#define AUDIO_IN              A3
#define NOISE_SAMPLE_NUMBER   50
#define NOISE_FLOOR           512

void noiseState(void);
int noiseReadValue(void);
void testSensor(void);
