/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"
#include "FLASH_PAGE_F1.h"

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

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
uint8_t rsp3[200];
uint8_t rsp2[200];
uint8_t rsp22[200];
uint8_t cmd[] = "AT+QMTPUBEX=0,0,0,0,\"nhanhung/gateway2/sensor1\",57\r\n";
uint8_t cmdd[] = "AT+QMTPUBEX=0,0,0,0,\"nhanhung/gateway2/sensor2\",57\r\n";
uint8_t cmddd[] = "AT+QMTPUBEX=0,0,0,0,\"nhanhung/gateway2/sensor3\",57\r\n";
uint8_t state;
int count = 0;
char string[250];
uint32_t Rx_Data[250];
uint8_t chua[250];

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USART2_UART_Init(void);
void dan(int count);
/* USER CODE BEGIN PFP */

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
  MX_USART3_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
	HAL_Delay(400);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_Delay(5000);																																//Set up
	
	uint8_t cmd5[] = "AT+QMTCFG=\"recv/mode\",0,0,1\r\n";
	for (int i=0;i<=1;i++) {
	HAL_UART_Transmit(&huart3,cmd5, sizeof(cmd5), 1000);
	HAL_UART_Receive(&huart3,rsp3, sizeof(rsp3), 1000);
	HAL_Delay(500);
	}
	
	uint8_t cmd6[] = "AT+QMTOPEN=?\r\n";
	for (int i=0;i<=4;i++) {
	HAL_UART_Transmit(&huart3,cmd6, sizeof(cmd6), 1000);
	HAL_UART_Receive(&huart3,rsp3, sizeof(rsp3), 1000);
	HAL_Delay(500);
	}
	
	uint8_t cmd7[] = "AT+QMTOPEN=0,\"210.86.239.240\",8080\r\n";
	for (int i=0;i<=0;i++) {
	HAL_UART_Transmit(&huart3,cmd7, sizeof(cmd7), 1000);
	HAL_UART_Receive(&huart3,rsp3, sizeof(rsp3), 1000);
	HAL_Delay(500);
	}
	
	uint8_t cmd8[] = "AT+QMTOPEN?\r\n";
	for (int i=0;i<=0;i++) {
	HAL_UART_Transmit(&huart3,cmd8, sizeof(cmd8), 1000);
	HAL_UART_Receive(&huart3,rsp3, sizeof(rsp3), 1000);
	HAL_Delay(500);
	}
	
	uint8_t cmd9[] = "AT+QMTCONN=?\r\n";
	for (int i=0;i<=4;i++) {
	HAL_UART_Transmit(&huart3,cmd9, sizeof(cmd9), 1000);
	HAL_UART_Receive(&huart3,rsp3, sizeof(rsp3), 1000);
	HAL_Delay(500);
	}
	
	uint8_t cmd10[] = "AT+QMTCONN=0,\"nhanhung123\",\"\",\"\"\r\n";
	for (int i=0;i<=4;i++) {
	HAL_UART_Transmit(&huart3,cmd10, sizeof(cmd10), 1000);
	HAL_UART_Receive(&huart3,rsp3, sizeof(rsp3), 1000);
	HAL_Delay(500);
	}
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		HAL_UART_Receive(&huart2,rsp2, 59, 1000);
//		HAL_Delay(1000);
		if (memcmp(rsp2,"{\"id\": \"device1b",16) == 0) {
			HAL_UART_Transmit(&huart3, cmd, sizeof(cmd), 1000);
			HAL_Delay(500);
			HAL_UART_Transmit(&huart3, rsp2, 57, 1000);
			HAL_Delay(500);
			HAL_UART_Transmit(&huart3,(uint8_t*)"\x1A", 1, 1000);
			HAL_Delay(500);
			HAL_UART_Transmit(&huart3,(uint8_t*)"\x1A", 1, 1000);
			dan(count);
			count += 57;
		}
		
		if (memcmp(rsp2,"{\"id\": \"device2b",16) == 0) {
			HAL_UART_Transmit(&huart3, cmdd, sizeof(cmdd), 1000);
			HAL_Delay(500);
			HAL_UART_Transmit(&huart3, rsp2, 57, 1000);
			HAL_Delay(500);
			HAL_UART_Transmit(&huart3,(uint8_t*)"\x1A", 1, 1000);
			HAL_Delay(500);
			HAL_UART_Transmit(&huart3,(uint8_t*)"\x1A", 1, 1000);
			dan(count);
			count += 57;
		}
		
		if (memcmp(rsp2,"{\"id\": \"device3b",16) == 0) {
			HAL_UART_Transmit(&huart3, cmddd, sizeof(cmddd), 1000);
			HAL_Delay(500);
			HAL_UART_Transmit(&huart3, rsp2, 57, 1000);
			HAL_Delay(500);
			HAL_UART_Transmit(&huart3,(uint8_t*)"\x1A", 1, 1000);
			HAL_Delay(500);
			HAL_UART_Transmit(&huart3,(uint8_t*)"\x1A", 1, 1000);
			dan(count);
			count += 57;
		}

		if (count == 228) {
			int numofwords = (sizeof(chua)/4)+((sizeof(chua)%4)!=0);
			Flash_Write_Data(0x08004810, (uint32_t *)chua, numofwords);
			Flash_Read_Data(0x08004810, Rx_Data, numofwords);
			Convert_To_Str(Rx_Data, string);
			count = 0;
			}
		}
	}
  /* USER CODE END 3 */
	
void dan(int count) {
	for (int i = 0, j = count; i < 57; i++) {
		chua[j] = rsp2[i];
		j++;
		}
	memset(rsp2, 0, sizeof(rsp2));
	}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB0 PB1 PB3 PB4
                           PB5 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PC6 PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
  while (1)
  {
  }
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
