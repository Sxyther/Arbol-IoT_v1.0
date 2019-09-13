#include "sigfox.h"


/***********************************************************************/
//Get Sigfox ID
void sigfox_init(void)
{
  String pac = "";

  Serial1.begin(9600);          // Sigfox Radio Serial port
  delay(100);
  
  pinMode(SIGFOX_SHUTDOWN,OUTPUT);
  digitalWrite(SIGFOX_SHUTDOWN,LOW);

  pinMode(SIGFOX_RESET,OUTPUT);
  digitalWrite(SIGFOX_RESET,LOW);

  pinMode(SIGFOX_POWER,OUTPUT);
  digitalWrite(SIGFOX_POWER,LOW);


  // Get and Show Sigfox radio Information  
  delay(100);
  pac = sigfox_getID();
  Serial.print("Sigfox ID:  ");
  Serial.print(pac);
  
  delay(100);
  pac = sigfox_getPAC();
  Serial.print("Sigfox PAC: ");
  Serial.print(pac);
  delay(100);
  
}


/***********************************************************************/
//Get Sigfox ID
String sigfox_getID(void)
{
  String id = "";
  char output;

  Serial1.print("AT$I=10\r");
  while (!Serial1.available()){
     sigfox_blink();
  }

  while(Serial1.available()){
    output = Serial1.read();
    id += output;
    delay(10);
  }

  return(id);
}

/***********************************************************************/
//Get PAC number
String sigfox_getPAC(void)
{
  String pac = "";
  char output;

  Serial1.print("AT$I=11\r");
  while (!Serial1.available()){
     sigfox_blink();
  }

  while(Serial1.available()){
    output = Serial1.read();
    pac += output;
    delay(10);
  }
  return (pac);
}
/***********************************************************************/
void sigfox_blink()
{
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);    
}

/***********************************************************************/
//Send Sigfox Message
void sigfox_sendMessage(byte msg[], int size)
{

  String status = "";
  char output;

  Serial1.print("AT$SF=");
  for(int i= 0;i<size;i++)
  {
    Serial1.print(String(msg[i], HEX));
    Serial.print("Byte:");
    Serial.println(msg[i], HEX);
  }

  Serial1.print("\r");

  while (!Serial1.available())
  {
     sigfox_blink();
  }
  
  while(Serial1.available())
  {
    output = (char)Serial1.read();
    status += output;
    delay(10);
  }
  
  Serial.println();
  Serial.print("Status \t");
  Serial.println(status);
}
