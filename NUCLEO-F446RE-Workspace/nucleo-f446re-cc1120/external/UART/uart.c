#include "uart.h"

/******************************************************************************************
 * Local Variables
 */
UART_HandleTypeDef UART_Handle;
UART_HandleTypeDef OBC_Handle;


/******************************************************************************************
 * Export Functions
 */
void initUART(UART_HandleTypeDef huart)
{
	UART_Handle = huart;
}

void initOBC(UART_HandleTypeDef huart)
{
	OBC_Handle = huart;
}

void printString(char* string)
{
	uint8_t buf[strlen(string)];
	strcpy((char*)buf, string);
	HAL_UART_Transmit(&UART_Handle, buf, strlen((char*)buf), HAL_MAX_DELAY);
}

void stringToOBC(char* string)
{
	uint8_t buf[strlen(string)];
	strcpy((char*)buf, string);
	HAL_UART_Transmit(&OBC_Handle, buf, strlen((char*)buf), HAL_MAX_DELAY);
}

void stringFromOBC(uint8_t* buffer, uint16_t numBytes)
{
	HAL_UART_Receive(&OBC_Handle, buffer, numBytes, HAL_MAX_DELAY);
}