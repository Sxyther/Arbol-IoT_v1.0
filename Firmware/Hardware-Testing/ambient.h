#include <arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"




#define AMBIENT_POWER       11
#define AMBIENT_POWER_ON  (digitalWrite(AMBIENT_POWER,HIGH))
#define AMBIENT_POWER_OFF (digitalWrite(AMBIENT_POWER,LOW))

/* Prototypes */
void bme680_init(void);
float bme680_readTemperature(void);
float bme680_readHumidity(void);
