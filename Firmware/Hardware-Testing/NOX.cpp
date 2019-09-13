#include "NOX.h"



/**********************************************/
void nOX_SensorInit(void)
{
  pinMode(SENSOR_POWER,OUTPUT);  
}

/**********************************************/
float nOX_get_NH3(void) 
{
  return(analogRead(NOX_NH3)*3.3/1023);  
}

/**********************************************/
float nOX_get_OX(void) 
{
  return(analogRead(NOX_OX)*3.3/1023);  
}

/**********************************************/
float nOX_get_RED(void) 
{
  return(analogRead(NOX_RED)*3.3/1023);  
}
