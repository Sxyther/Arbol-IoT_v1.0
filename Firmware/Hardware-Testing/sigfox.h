#include <Arduino.h>


#define SIGFOX_SHUTDOWN 5
#define SIGFOX_RESET    6
#define SIGFOX_POWER    9


#define AUDIO_IN  A0
#define NOISE_SAMPLE_NUMBER 10
// Prototypes
int tarara(void);



// Prototypes
void sigfox_init(void);
String sigfox_getID(void);
String sigfox_getPAC(void);
void sigfox_blink();
void sigfox_sendMessage(byte msg[], int size);
