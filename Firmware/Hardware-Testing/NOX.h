#include <Arduino.h>



#define SENSOR_POWER        8
#define NOX_POWER_OFF     (digitalWrite(SENSOR_POWER,LOW))
#define NOX_POWER_ON      (digitalWrite(SENSOR_POWER,HIGH))

/* defines */
#define NOX_RED A3
#define NOX_NH3 A2
#define NOX_OX  A1



/* Prototyes */
void nOX_SensorInit(void);
float nOX_get_NH3(void);
float nOX_get_OX(void);
float nOX_get_RED(void);
