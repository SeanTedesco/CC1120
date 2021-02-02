#include "CC1120_Arduino_SPI.h"
#include "Arduino.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() 
{
    pinMode(CC112X_CHIP_RESET, OUTPUT);          //reset pin --> output
    pinMode(CC112X_SPI_MOSI, OUTPUT);        //mosi pin --> output
    pinMode(CC112X_SPI_MISO, INPUT);          //miso pin --> input
    pinMode(CC112X_SERIAL_CLOCK, OUTPUT);       //sclk pin --> output
    pinMode(CC112X_CHIP_SELECT, OUTPUT);    //ss pin --> output
    digitalWrite(CC112X_CHIP_SELECT,HIGH);  //disable deivce communication
    digitalWrite(CC112X_CHIP_RESET, HIGH);       //reset off

    Serial.begin(9600);              //start Serial
    Serial.println("<start program>");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() 
{
  


}
