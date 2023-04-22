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
#include "cmsis_os.h"
#include "app_game01.h"
#include "app_general.h"
#include "hw_drivers.h"
#include "cli_parser.h"

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;

void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);
void StartTask03(void const * argument);

bool is_app_game01_running = true;

void Setup() {
 /* MCU Configuration--------------------------------------------------------*/

    /* MCU Configuration--------------------------------------------------------*/
  init_system_basic_clock();

  /* Initialize all configured peripherals */
  
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  init_gpio_input(B1_GPIO_Port, B1_Pin, GPIO_MODE_IT_FALLING);
  init_gpio_output(LD2_GPIO_Port, LD2_Pin);

  init_uart(&huart2, USART2, 115200);

  /* To enable printf() support for UART2 */
  RetargetInit(&huart2);

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityIdle, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, StartTask03, osPriorityIdle, 0, 128);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* Start scheduler */
  osKernelStart();
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  Setup();
  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  while (1)
  {
  
  }
 
}




/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
void StartDefaultTask(void const * argument)
{
  while(true) {
        if(is_app_game01_running) {game01_task_timer();}
        
  }
}

/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
void StartTask02(void const * argument)
{
  while(true) {
        if(is_app_game01_running) {game01_task02();    }
  }

}

/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
void StartTask03(void const * argument)
{
  while(true) {
        if(is_app_game01_running) {game01_task01(); }

  }
}
