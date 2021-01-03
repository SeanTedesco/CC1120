#include "Arduino.h"
#include "CC1120-arduino-extended.h"

// read register commands
uint8_t read_config_register(CC1120_Registers reg)
{
  uint8_t data;
  digitalWrite(CSN, LOW); // enable the device

  digitalWrite(CSN, HIGH); // disable the device
}

uint8_t read_config_register_extended(CC1120_Registers reg);

//write register commands
void write_config_register(CC1120_Registers reg, uint8_t value);
void write_config_register_extended(CC1120_Registers reg, uint8_t value);
void write_command_strobe(CC1120_Command_Strobes strobe);

// radio commands
void sendData();
uint8_t receiveData();
uint8_t spi_transfer(uint8_t data);
