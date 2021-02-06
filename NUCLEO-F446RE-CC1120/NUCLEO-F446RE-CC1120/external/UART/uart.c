/*
*   @file:  source file for UART 
*
*/
/********************************************************************
 * INCLUDES
 */
#include "stdio.h"

/********************************************************************
 * EXPORT FUNCTIONS
 */
void printToScreen(char* string)
{
    printf("printToScreen\r\n");
    printf(string);
}
