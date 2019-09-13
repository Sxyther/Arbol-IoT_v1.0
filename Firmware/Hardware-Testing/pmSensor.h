#include <Arduino.h>


#define PM_POWER            7
#define PM_POWER_ON       (digitalWrite(PM_POWER,HIGH))
#define PM_POWER_OFF      (digitalWrite(PM_POWER,LOW))



#define PM_BUFFER_SIZE 65
#define DELAY_BETWEEN_FRAMES  4000





typedef struct 
{
  char header;
  unsigned char address;
  unsigned char cmd0;
  unsigned char state;
  unsigned char ln;
  
  float mass1;
  float mass2_5;
  float mass4;
  float mass10;
  float number0_5;
  float number1;
  float number2_5;
  float number4;
  float number10;
  float typSize;
  
  char checksum;
  char footer;
}pmData;


void pmSensorInit(void);
unsigned char pmSensor_getData(void);
void PrintHex8(uint8_t *data, uint8_t length); // prints 8-bit data in hex with leading zeroes
