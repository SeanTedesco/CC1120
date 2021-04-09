/****************************************************************************
 * @file 	spi_lib.c
 * @brief 	Implementation file for basic and neccessary functions to communicate over SPI
 */

/******************************************************************************
 * INCLUDES
 */
#include <spi_lib.h>


/******************************************************************************************
 * Local Variables
 */
SPI_HandleTypeDef SPI_Handle;



/******************************************************************************
 * FUNCTIONS
 */
void initCC1120(SPI_HandleTypeDef hspi)
{
	SPI_Handle = hspi;
}



