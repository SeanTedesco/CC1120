#ifndef _UART_H_
#define _UART_H_

/******************************************************************************************
 * Includes
 */
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "stdio.h"
#include "string.h"

/******************************************************************************************
 * Export Functions
 */
void initUART(UART_HandleTypeDef huart);
void printString(char* string);

void initOBC(UART_HandleTypeDef huart);
void stringToOBC(char* string);
void stringFromOBC(uint8_t* buffer, uint16_t numBytes);

#endif
