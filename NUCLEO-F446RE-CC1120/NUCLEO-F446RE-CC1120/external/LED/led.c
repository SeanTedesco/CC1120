/*
*   @file: source file for LEDs on STM32 board
*
*/
/********************************************************************
 * INCLUDES
 */
#include "led.h"
#include "uart.h"

/********************************************************************
 * EXPORT FUNCTIONS
 */
void initLED(void)
{
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
}
void setLED(void)
{
	printToScreen("setLED\r\n");
}

void resetLED(void)
{
	printToScreen("resetLED\r\n");
}

