#include "ambient.h"



// BME680 - Ambient Sensor
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME680 bme; // I2C

/******************************************************************/
/******************************************************************/
void bme680_init(void)
{
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms  
}

/******************************************************************/
/******************************************************************/
float bme680_readTemperature(void)
{
  if (! bme.performReading()) 
  {
    Serial.println("Failed to perform reading :(");
  }
  return(bme.temperature);
}


/******************************************************************/
/******************************************************************/
float bme680_readHumidity(void)
{
  if (! bme.performReading()) 
  {
    Serial.println("Failed to perform reading :(");
  }
  return(bme.humidity);

}
