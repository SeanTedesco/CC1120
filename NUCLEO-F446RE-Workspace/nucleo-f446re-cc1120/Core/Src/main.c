/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include <uart_lib.h>
#include <spi_lib.h>
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* Extended Configuration Registers */
const uint16 CC112X_MARCSTATE =           		0x2F73;
/* Command strobe registers */
const uint8 CC112X_SRES =                    0x30;      /*  SRES    - Reset chip. */
const uint8 CC112X_SFSTXON =                 0x31;      /*  SFSTXON - Enable and calibrate frequency synthesizer. */
const uint8 CC112X_SXOFF =                   0x32;      /*  SXOFF   - Turn off crystal oscillator. */
const uint8 CC112X_SCAL =                    0x33;      /*  SCAL    - Calibrate frequency synthesizer and turn it off. */
const uint8 CC112X_SRX =                     0x34;      /*  SRX     - Enable RX. Perform calibration if enabled. */
const uint8 CC112X_STX =                     0x35;      /*  STX     - Enable TX. If in RX state, only enable TX if CCA passes. */
const uint8 CC112X_SIDLE =                   0x36;      /*  SIDLE   - Exit RX / TX, turn off frequency synthesizer. */
const uint8 CC112X_SWOR =                    0x38;      /*  SWOR    - Start automatic RX polling sequence (Wake-on-Radio) */
const uint8 CC112X_SPWD =                    0x39;      /*  SPWD    - Enter power down mode when CSn goes high. */
const uint8 CC112X_SFRX =                    0x3A;      /*  SFRX    - Flush the RX FIFO buffer. */
const uint8 CC112X_SFTX =                    0x3B;      /*  SFTX    - Flush the TX FIFO buffer. */
const uint8 CC112X_SWORRST =                 0x3C;      /*  SWORRST - Reset real time clock. */
const uint8 CC112X_SNOP =                    0x3D;      /*  SNOP    - No operation. Returns status byte. */
const uint8 CC112X_AFC =                     0x37;      /*  AFC     - Automatic Frequency Correction */
/* Chip states returned in status byte */
const uint8 CC112X_STATE_IDLE =			0x00;
const uint8 CC112X_STATE_RX =           0x10;
const uint8 CC112X_STATE_TX =			0x20;
const uint8 CC112X_STATE_FSTXON =    	0x30;
const uint8 CC112X_STATE_CALIBRATE =  	0x40;
const uint8 CC112X_STATE_SETTLING =     0x50;
const uint8 CC112X_STATE_RXFIFO_ERROR = 0x60;
const uint8 CC112X_STATE_TXFIFO_ERROR = 0x70;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
void tx_strobe(void);
void rx_strobe(void);
void idle_strobe(void);
void flush_tx(void);
void flush_rx(void);
void std_fifo_write(void);
void std_fifo_read(void);
void direct_tx_fifo_read(void);
void tx_pointers_read(void);
void write_settings(void);
void tx_buff_size_read(void);
void read_marcstate(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	//uint8 i2c_buf[32];
	//uint8 spi_buf[32];
	//char uart_buf[32];

	//uint8 uart_buf_len;

	//HAL_StatusTypeDef ret;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_SPI2_Init();
  MX_USART3_UART_Init();
  MX_I2C1_Init();

  /* USER CODE BEGIN 2 */
  // set up connection to serial monitor
  initUART(huart2);
  // bring CSN high
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
  // tell obc that comms is working
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
  //tell user we're about to begin
  printString("<BEGIN PROGRAM>\r\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  tx_strobe();
	  read_marcstate();
	  HAL_Delay(1000);

	  rx_strobe();
	  read_marcstate();
	  HAL_Delay(1000);

	  //printString("...\r\n");
	  //HAL_Delay(1000);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB2 PB12 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
/*************************************************************************************************/
/***************************************************
  * @ brief Write to the TX strobe command register
  * @ param None
  * @ retval None
  */
void tx_strobe(void)
{
	printString("called tx_strobe()\r\n");

	uint8 tempRxData = 0x0;

	// bring CSN low to begin communication
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

	// write out the command
	HAL_SPI_Transmit(&hspi2, (uint8_t*)(&CC112X_STX), 1, HAL_MAX_DELAY);

	//receive the register status on the miso line
	HAL_SPI_Receive(&hspi2, &tempRxData, 1, HAL_MAX_DELAY);

	// bring CSN high to end communication
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);


	// print out the state
	printString("RETURN: ");
	HAL_UART_Transmit(&huart2, tempRxData, strlen((char*) tempRxData), HAL_MAX_DELAY);
	printString("\r\n");
}

/***************************************************
  * @ brief Write to the RX strobe command register
  * @ param None
  * @ retval None
  */
void rx_strobe(void)
{
	printString("called rx_strobe()\r\n");

	uint8* state = 0x0;

	// bring CSN low to begin communication
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

	// write out the command
	HAL_SPI_Transmit(&hspi2, (uint8_t*)(&CC112X_SRX), 1, HAL_MAX_DELAY);

	//receive the register status on the miso line
	HAL_SPI_Receive(&hspi2, &state, 1, HAL_MAX_DELAY);

	// bring CSN high to end communication
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

	// print out the state
	printString("RETURN: ");
	HAL_UART_Transmit(&huart2, &state, strlen((char*) state), HAL_MAX_DELAY);
	printString("\r\n");
}

/****************************************************
  * @ brief Write to the IDLE strobe command register
  * 		must be done before transmitting or receiving
  * @ param None
  * @ retval None
  */
void idle_strobe(void)
{
	printString("called idle_strobe()\r\n");
}

/***************************************************
  * @ brief remove all current bytes in the TX_FIFO Buffer,
  * 		does not re-adjust FIFO pointers.
  * @ param None
  * @ retval None
  */
void flush_tx(void)
{
	printString("called flush_tx()\r\n");
}

/***************************************************
  * @ brief remove all current bytes in the RX_FIFO Buffer,
  * 		does not re-adjust FIFO pointers.
  * @ param None
  * @ retval None
  */
void flush_rx(void)
{
	printString("called flush_rx()\r\n");
}

/***************************************************
  * @ brief Write the packet to the TX FIFO on the radio
  * @ param None
  * @ retval None
  */
void std_fifo_write(void)
{
	printString("called std_fifo_write()\r\n");
}

/***************************************************
  * @ brief Read the packet in the RX FIFO on the radio
  * @ param None
  * @ retval None
  */
void std_fifo_read(void)
{
	printString("called std_fifo_read()\r\n");
}

/***************************************************
  * @ brief Transmit packet using Direct Memory Access
  * @ param None
  * @ retval None
  */
void direct_tx_fifo_read(void)
{
	printString("called direct_tx_fifo_read()\r\n");
}

/***************************************************
  * @ brief Read the pointer location in the TX FIFO
  * @ param None
  * @ retval None
  */
void tx_pointers_read(void)
{
	printString("called tx_pointers_read()\r\n");
}

/***************************************************
  * @ brief Write the settings defined in preferredSettings array,
  * 		calls radios register config function.
  * @ param None
  * @ retval None
  */
void write_settings(void)
{
	printString("called write_settings()\r\n");
}

/***************************************************
  * @ brief Read How many bytes are in the TX FIFO
  * @ param None
  * @ retval None
  */
void tx_buff_size_read(void)
{
	printString("called tx_buff_size_read()\r\n");


}

/***************************************************
  * @ brief read the current state of the transceiver
  * @ param None
  * @ retval None
  */
void read_marcstate(void)
{
	//let user know what function we're using
	printString("called read_marcstate()\r\n");

	uint8 tempExt  = (CC112X_MARCSTATE>>8);
	uint8 tempAddr = (CC112X_MARCSTATE & 0x00FF);
	uint8 tempTxData = 0x00;
	uint8* tempRxData = 0x0;

	// bring CSN low to begin communication
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

	// begin access to extended register
	HAL_SPI_Transmit(&hspi2, (uint8*)&tempExt, 1, HAL_MAX_DELAY);

	// next byte needs to be the address of the marcstate register
	HAL_SPI_Transmit(&hspi2, (uint8*)&tempAddr, 1, HAL_MAX_DELAY);

	// read a value by sending all zeros on the mosi line
	HAL_SPI_Transmit(&hspi2, (uint8*)&tempTxData, 1, HAL_MAX_DELAY);

	//receive the register status on the miso line
	HAL_SPI_Receive(&hspi2, &tempRxData, 1, HAL_MAX_DELAY);

	// bring CSN high to end communication
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

	// print out the state
	printString("MARCSTATE: ");
	HAL_UART_Transmit(&huart2, tempRxData, strlen((char*) tempRxData), HAL_MAX_DELAY);
	printString("\r\n");
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET); // tell obc that comms isn't working
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
