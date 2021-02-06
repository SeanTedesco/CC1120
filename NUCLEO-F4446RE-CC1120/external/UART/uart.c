/*************************************************************************************
 * INCLUDES
 */
#include "uart.h"

/*************************************************************************************
 * LOCAL VARIABLES
 */
UART_HandleTypeDef *huart2 = 0x0;
//UART_HandleTypeDef *huart3 = 0x0;

/*************************************************************************************
 * EXPORT FUNCTIONS
 */
/*************************************************************************************
 * @brief: 	provides the source file with access to the UART
 * 			handle as initialized in main.c
 *
 * @param: 	UARTHandle - the UART handle as initialized in main.c
 *
 * @return: void
 */
void CC_UART_Init(UART_HandleTypeDef *UARTHandle1){
	// provides the UART handle for source file
	huart2 = UARTHandle1;
}
/*************************************************************************************
 * @brief: 	prints a string to the serial port as specified
 * 			by the initial UART handle
 *
 * @param: 	str - string literal that will be sent through UART
 *
 * @return: void
 */
void printToTerminal(char *str)
{
	char buf[50];
	uint8_t length = sprintf(buf, str);
	HAL_UART_Transmit(&huart2, (uint8_t*)buf, length, 100);
}
/*************************************************************************************
 * @brief: 	receives a string from the TX/RX pins
 *
 * @param: 	buf - pointer to buffer that will hold data
 * @param: 	len - the amount of data to be received from UART pins
 *
 * @return: void
 */
void receiveFromTerminal(uint8_t* buf, uint8_t len)
{
	if(HAL_UART_Receive(huart2, buf, len, 100) != HAL_OK){
		printToTerminal("nothing received yet...");
	}
}
