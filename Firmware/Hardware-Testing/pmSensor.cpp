#include <Arduino.h>
#include "wiring_private.h"
#include "pmSensor.h"

char PM_START_MEASUREMENTS[]={0x7E,0x00,0x00,0x02,0x01,0x03,0xF9,0x7E}; // Start measurements
char AUTOCLEANING[]={0x7E,0x00,0x80,0x01,0x00,0x7D,0x5E,0x7E};            // Autocleaning interval
char Frame1[]={0x7E,0x00,0xD1,0x00,0x2E,0x7E};
char READ_PM_DATA[]={0x7E,0x00,0x03,0x00,0xFC,0x7E};



Uart pmSensor (&sercom3, 3, 4, SERCOM_RX_PAD_1, UART_TX_PAD_0); // Create the new UART instance 



unsigned char pm_buffer[PM_BUFFER_SIZE];
unsigned long milis_base;
unsigned char inCounter=0;
pmData datos;


/*********************************************************************************/
void PrintHex8(uint8_t *data, uint8_t length) // prints 8-bit data in hex with leading zeroes
{
       Serial.print("0x"); 
       for (int i=0; i<length; i++) { 
         if (data[i]<0x10) {Serial.print("0");} 
         Serial.print(data[i],HEX); 
         Serial.print(" "); 
       }
}




/***********************************************************/
void pmSensorInit(void)
{
  
  pinMode(PM_POWER,OUTPUT);       //
  PM_POWER_ON;
  
  // Adding a HW serial port for PM sensor
  pmSensor.begin(115200);         // PM sensor Serial port
  pinPeripheral(3, PIO_SERCOM); //Assign RX function to pin 0
  pinPeripheral(4, PIO_SERCOM); //Assign TX function to pin 1 

  delay(200);
  pmSensor.write(PM_START_MEASUREMENTS,sizeof(PM_START_MEASUREMENTS));
  delay(DELAY_BETWEEN_FRAMES);
  
  delay(500);
  pmSensor.write(AUTOCLEANING,sizeof(AUTOCLEANING));
  delay(DELAY_BETWEEN_FRAMES);
   
  delay(200);
}


  
/***********************************************************/
unsigned char pmSensor_getData(void)
{
  pmData datos;
  unsigned long current_mills;
  unsigned char u8LocalCounter=0;
  int checksum=0;  
  float temp=0;

 
 union {
        uint32_t i;
        float f;
    }data;

 
  if(pmSensor.available()) 
  {
    pm_buffer[inCounter] = pmSensor.read();
    inCounter++;
  }


  
  current_mills=millis();
  
  if((current_mills-milis_base)>DELAY_BETWEEN_FRAMES)
  {
    //datos = (pmData*)pm_buffer;

    for(u8LocalCounter=1;u8LocalCounter<45;u8LocalCounter++)
    {
      checksum+=pm_buffer[u8LocalCounter];
    }
    checksum = (~checksum)&0xFF;


    
    
    /*
    Serial.println("--------------------------------");
    Serial.print(checksum,HEX);
    Serial.print("\t");
    Serial.print(datos->checksum,HEX);
    Serial.print("\t");
    Serial.print(pm_buffer[45],HEX);
    Serial.print("\t");
    
    PrintHex8(pm_buffer,50); Serial.print("\n");
*/

    if(checksum == pm_buffer[45])
    {
    

        Serial.print("Mass Concentration 1.0:    ");
        data.i = (pm_buffer[5]<<24);
        data.i += (pm_buffer[6]<<16);
        data.i += (pm_buffer[7]<<8);
        data.i +=  pm_buffer[8];
        datos.mass1 = data.f;
        Serial.println(datos.mass1);
        
        Serial.print("Mass Concentration 2.5:    ");
        data.i = (pm_buffer[9]<<24);
        data.i += (pm_buffer[10]<<16);
        data.i += (pm_buffer[11]<<8);
        data.i +=  pm_buffer[12];
        datos.mass2_5 = data.f;
        Serial.println(datos.mass2_5);
    
        Serial.print("Mass Concentration 4.0:    ");
        data.i = (pm_buffer[13]<<24);
        data.i += (pm_buffer[14]<<16);
        data.i += (pm_buffer[15]<<8);
        data.i +=  pm_buffer[16];
        datos.mass4 = data.f;
        Serial.println(datos.mass4);
    
        Serial.print("Mass Concentration 10 :    ");
        data.i = (pm_buffer[17]<<24);
        data.i += (pm_buffer[18]<<16);
        data.i += (pm_buffer[19]<<8);
        data.i +=  pm_buffer[20];
        datos.mass10 = data.f;
        Serial.println(datos.mass10);
    
        Serial.print("Number Concentration 0.5 : ");
        data.i = (pm_buffer[21]<<24);
        data.i += (pm_buffer[22]<<16);
        data.i += (pm_buffer[23]<<8);
        data.i +=  pm_buffer[24];
        datos.number0_5 = data.f;
        Serial.println(datos.number0_5);
    
        Serial.print("Number Concentration 1.0 : ");
        data.i = (pm_buffer[25]<<24);
        data.i += (pm_buffer[26]<<16);
        data.i += (pm_buffer[27]<<8);
        data.i +=  pm_buffer[28];
        datos.number1 = data.f;
        Serial.println(datos.number1);
    
        Serial.print("Number Concentration 2.5 : ");
        data.i = (pm_buffer[29]<<24);
        data.i += (pm_buffer[30]<<16);
        data.i += (pm_buffer[31]<<8);
        data.i +=  pm_buffer[32];
        datos.number2_5 = data.f;
        Serial.println(datos.number2_5);
    
        Serial.print("Number Concentration 4.0 : ");
        data.i = (pm_buffer[33]<<24);
        data.i += (pm_buffer[34]<<16);
        data.i += (pm_buffer[35]<<8);
        data.i +=  pm_buffer[36];
        datos.number4 = data.f;
        Serial.println(datos.number4);
    
        Serial.print("Number Concentration 10  : ");
        data.i = (pm_buffer[37]<<24);
        data.i += (pm_buffer[38]<<16);
        data.i += (pm_buffer[37]<<8);
        data.i +=  pm_buffer[39];
        datos.number10 = data.f;
        Serial.println(datos.number10);

        /*
        Serial.print("Typical Size             : ");
        data.i = (pm_buffer[40]<<24);
        data.i += (pm_buffer[41]<<16);
        data.i += (pm_buffer[42]<<8);
        data.i +=  pm_buffer[43];
        datos.typSize = data.f;
        Serial.println(datos.typSize);
        */
        return(1);
    }

    //Serial.print(pm_buffer,HEX);
    //Serial.println();
    inCounter=0;

    for(u8LocalCounter=0;u8LocalCounter<PM_BUFFER_SIZE;u8LocalCounter++)
    {
      pm_buffer[u8LocalCounter]=0;
    }

    pmSensor.write(READ_PM_DATA,sizeof(READ_PM_DATA));
    milis_base = millis();
  } 
  return(0);
}

/*************************************************************/
void SERCOM3_Handler()
{
  pmSensor.IrqHandler();
}
