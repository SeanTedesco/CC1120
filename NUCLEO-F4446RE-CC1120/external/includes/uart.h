#ifndef _UART_H_
#define _UART_H_


/*************************************************************************************
 * INCLUDES
 */
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"


/*************************************************************************************
 * EXPORT FUNCTIONS
 */
void CC_UART_Init(UART_HandleTypeDef* UARTHandle1);
void printToTerminal(char* str);
void receiveFromTerminal(uint8_t* buf, uint8_t len);

#endif
