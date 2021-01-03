#include <CC1120-arduino-extended.h>
#include "SPI.h"

/******************* HARDWARE PIN CONNECTIONS ***************************
*************************************************************************  
  MISO = 12,
  MOSI = 11,
  CSN = 10,
  RESET = 9,
  SCKL = 3
*/

void setup()
{
  Serial.begin(9600);
  SPI.begin();

  pinMode(CSN, OUPUT);
  pinMode(RESET, OUPUT);
  digitalWrite(CSN, HIGH);
  digitalWrite(RESET, HIGH);

  Serial.println("CC1120 Program Start")
}

void loop()
{
  Serial.println("Hello");
  delay(1000);
}
