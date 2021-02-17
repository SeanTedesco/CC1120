/****************************************************************************
 * @file 	cc112x_spi.c
 * @brief 	Implementation file for basic and neccessary functions
 * 			to communicate with CC112X over SPI
 */

/******************************************************************************
 * INCLUDES
 */
#include "cc112x_spi.h"

/******************************************************************************
 * LOCAL VARIABLES
 */
SPI_HandleTypeDef SPI_Handle;

/******************************************************************************
 * FUNCTIONS
 */
void initCC1120(SPI_HandleTypeDef hspi)
{
	SPI_Handle = hspi;
}

void readWriteSingleBurst(uint8 addr, uint8 *pDataSI, uint8 *pDataSO, uint16 len)
{
	uint16 i;


	// send out the address
	HAL_SPI_TransmitReceive(&SPI_Handle, (uint8*) addr, pDataSO, 1, HAL_MAX_DELAY);

	if(addr & RADIO_READ_ACCESS)
	{
		if(addr & RADIO_BURST_ACCESS)
		{

			for (i = 0; i < len; i++)
			{
				HAL_SPI_TransmitReceive(&SPI_Handle, pDataSI, pDataSO, 1, HAL_MAX_DELAY);
				pDataSO++;
			}
		}
		else
		{
			HAL_SPI_TransmitReceive(&SPI_Handle, pDataSI, pDataSO, 1, HAL_MAX_DELAY);
		}
	}
	else
	{
		if(addr & RADIO_BURST_ACCESS)
		{
		  for (i = 0; i < len; i++)
		  {
			  HAL_SPI_TransmitReceive(&SPI_Handle, pDataSI, pDataSO, 1, HAL_MAX_DELAY);
			  pDataSI++;
		  }
		}
		else
		{
			HAL_SPI_TransmitReceive(&SPI_Handle, pDataSI, pDataSO, 1, HAL_MAX_DELAY);
		}
	}
	return;
}
