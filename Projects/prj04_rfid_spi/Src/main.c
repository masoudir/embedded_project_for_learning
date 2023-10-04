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
#include "app_RFID.h"
#include "MFRC522.h"
#include "app_general.h"



UART_HandleTypeDef huart2;
SPI_HandleTypeDef hspi2;

/**
  * @brief  The application entry point.
  * @retval int
  */


 
 void init_uart(UART_HandleTypeDef* huart, USART_TypeDef* usart, uint32_t baudrate) {

  huart->Instance = usart;
  huart->Init.BaudRate = baudrate;
  huart->Init.WordLength = UART_WORDLENGTH_8B;
  huart->Init.StopBits = UART_STOPBITS_1;
  huart->Init.Parity = UART_PARITY_NONE;
  huart->Init.Mode = UART_MODE_TX_RX;
  huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart->Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(huart) != HAL_OK)
  {
    Error_Handler();
  }

}

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  init_uart(&huart2,USART2,115200);

  RetargetInit(&huart2);

  HAL_UART_Transmit(&huart2, "HI", 2, 100);
  
  printf("hello f");
 
  MFRC522_init();
  while (1)
  {
   printf("hello f");
     void RFID_task1();
   
    
  }
 
}


