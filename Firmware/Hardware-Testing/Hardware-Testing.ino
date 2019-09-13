#include "NOX.h"
#include "noise.h"
#include "sigfox.h"
#include "pmSensor.h"
#include "ambient.h"


#define WAKEUP_MILLS_VALUE  30000
#define ENABLE_5V           13


typedef struct tFrameType0
{
    unsigned char tFrameType:2;
    unsigned int tHumidity:10;
    unsigned int tTemperature:10;
    unsigned int tNoise:10;
    float pm2_5;
    float pm10;
};

typedef struct tFrameType1
{
    unsigned char tFrameType:2;
    unsigned int tNH3:10;
    unsigned int tNO2:10;
    unsigned int tCO:10;
    unsigned char tReserved[8];
};




union{
  tFrameType0 protocol0;
  tFrameType1 protocol1;
  unsigned char  dataBuffer[12];
}pruebaUnion;



/* Global environmental variables */
unsigned int  gu32Noise=0;
float  gu32Temperature=0;
float  gu32Humidity=0;
float  gu32NH3=0;
float  gu32NO2=0;
float  gu32CO=0;

float gfPM2_5=0;
float gfPM10=0;

unsigned long GlobalsysTick=0;




/******************************************************************/
/******************************************************************/
void build_and_Send_SigfoxFrame(unsigned char u8FrameType) 
{
    unsigned char u8LocalCounter=0;
  
    if(u8FrameType == 0)
    {
        // Build Frame Type one from Global environmental Variables
        pruebaUnion.protocol0.tFrameType =0;
        pruebaUnion.protocol0.tNoise = gu32Noise;
        pruebaUnion.protocol0.tHumidity = gu32Humidity;
        pruebaUnion.protocol0.tTemperature = gu32Temperature;
        pruebaUnion.protocol0.pm2_5 = gfPM2_5;
        pruebaUnion.protocol0.pm10 = gfPM10;  
    }


    if(u8FrameType == 1)
    {
        // Build Frame Type one from Global environmental Variables
        pruebaUnion.protocol1.tFrameType =1;
        pruebaUnion.protocol1.tNH3 = gu32NH3;
        pruebaUnion.protocol1.tNO2 = gu32NO2;
        pruebaUnion.protocol1.tCO = gu32CO;

        for(u8LocalCounter=0;u8LocalCounter<8;u8LocalCounter++)
        {
          pruebaUnion.dataBuffer[u8LocalCounter]=0;
        }
      
    }
    // Print - Just for debug
    PrintHex8(pruebaUnion.dataBuffer,12); 
    Serial.println(" ");
    // Send Frame over Sigfox Network
    sigfox_sendMessage(pruebaUnion.dataBuffer,12);
}



/******************************************************************/
/******************************************************************/
void setup() 
{

  pinMode(LED_BUILTIN,OUTPUT);  // on board LED as output
  Serial.begin(9600);           // Debug Serial USB 
  
  delay(5000);                  // Delay to make Sure USB is enumerated and working

  Serial.println("[[[[[[[[[[[[]]]]]]]]]]]]]");
  Serial.println("[    Arbol IoT v0.1     ]");
  Serial.println("[[[[[[[[[[[[]]]]]]]]]]]]]");

  //General purpose IO configuration
  pinMode(ENABLE_5V,OUTPUT);      //
  digitalWrite(ENABLE_5V,LOW);    // 

  digitalWrite(ENABLE_5V,HIGH);    // 


  // Temporal configuration
  // NOX sensor
  nOX_SensorInit();
  NOX_POWER_ON;


  // Ambient
    AMBIENT_POWER_ON;

  bme680_init();

  
  
  Serial.println("\r\n- Configuracion Arbol IoT... OK! ");
  Serial.println("----------------------------------");
  GlobalsysTick =  millis();








}





unsigned char flag=0;










/******************************************************************/
/******************************************************************/
void loop() 
{
  int dummy=0;
  Serial.println("================================");
  
  ////////////////////
  // NOX sensor
  ///////////////////
  // Need to wait for 5 min before ew can read correct GAS values
  gu32NH3 = nOX_get_NH3();
  gu32CO = nOX_get_OX();
  gu32NO2 = nOX_get_RED();
  
  Serial.println("------- NOX Sensor ---------");
  Serial.print("NH3:\t\t");
  Serial.print(gu32NH3);
  Serial.println(" v");

  Serial.print("OX:\t\t");
  Serial.print(gu32CO);
  Serial.println(" v");

  Serial.print("RED:\t\t");
  Serial.print(gu32NO2);
  Serial.println(" v");
  Serial.println();
  
  //NOX_POWER_OFF;
  
  ////////////////////
  // PM sensor
  ///////////////////

  unsigned char u8localCounter=0;
  
  Serial.println("-------  PM Sensor ---------");
  pmSensorInit();

  //for(u8localCounter=0;u8localCounter<10;u8localCounter++)
  while(!pmSensor_getData());
  
  Serial.println();
  PM_POWER_OFF;

  ////////////////////
  // Ambient Sensor
  ////////////////////
 // leave sensor ON for 1 minute before we can measure correctly
  Serial.println("------ Ambient Sensor ---------");

  gu32Temperature = bme680_readTemperature();
  Serial.print("Temperature=\t");
  Serial.print(gu32Temperature);
  Serial.println(" *C");
  
  gu32Humidity = bme680_readHumidity();
  Serial.print("Humidity=\t");
  Serial.print(gu32Humidity);
  Serial.println(" %");
  
  //AMBIENT_POWER_OFF;



  
  ////////////////////
  // Noise Sensor
  ////////////////////
  //AMBIENT_POWER_ON;
  gu32Noise = noiseReadValue();
  Serial.print("Noise:\t\t");
  Serial.println(gu32Noise);
  Serial.println();
  
  //AMBIENT_POWER_OFF;



  
  /*
  unsigned long LocalsysTick=0;
    //(void)pmSensor_getData();
    
  gu32Noise= 0x3FF;
  gu32Temperature= 0x3FF;
  gu32Humidity= 0x3FF;
  gfPM10 = 0;
  gfPM2_5= 0;

  LocalsysTick = millis();

  delay(300000);
  //if((LocalsysTick - GlobalsysTick) > WAKEUP_MILLS_VALUE)
  {
    Serial.println("Sending Sigfox Data");
    build_and_Send_SigfoxFrame(0);
    GlobalsysTick = millis();
  }
  */
  /*
  if(flag == 0)
  {
    Serial.println("Sending Sigfox Data");
    build_and_Send_SigfoxFrame(0);
    flag=1;
  }
*/

  delay(2000);
  // put your main code here, to run repeatedly:

}
