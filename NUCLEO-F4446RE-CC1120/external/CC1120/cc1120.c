/*************************************************************************************
 * INCLUDES
 */
#include "cc1120.h"
#include "stm32f4xx_hal_spi.h"


/*************************************************************************************
 * LOCAL VARIABLES
 */
SPI_HandleTypeDef *hspi = 0x0;


/*************************************************************************************
 * EXPORT FUNCTIONS
 */
void CC_SPI_Init(SPI_HandleTypeDef *SPIHandle){
	// initialize all registers in the transceiver
	hspi = 	SPIHandle;
}


uint8_t writeToRegister(CC1120_Registers reg, uint8_t TXData){

}


void writeToRegisterExtended(CC1120_Registers reg, uint8_t value){
	// write one byte to a specified configuration register in the extended address space

}


void readFromRegister(CC1120_Registers reg){
	// read one byte from a specified configuration register

}


void readFromRegisterExtended(CC1120_Registers reg){
	// read one byte from a specified configuration register in the extended address space

}
