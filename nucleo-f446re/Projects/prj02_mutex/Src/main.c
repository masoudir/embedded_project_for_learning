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
#include "app_ledblink.h"
#include "app_accelerometer.h"

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;
SPI_HandleTypeDef hspi2;

osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;

extern bool is_app_game01_running;
extern bool is_app_ledblink_running;
extern bool is_app_acc_running;

static SemaphoreHandle_t mutex;

char task1_c_array[100+5] = "";
char task2_c_array[100+5] = "";

/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
void StartDefaultTask(void const * argument)
{
  printf("\r\n task1 started \r\n");
  // char c_array[100+5] = "";
  while(true) {

        memset(task1_c_array, 0, 2*sizeof(char));

        if (xSemaphoreTake(mutex, 0) == pdTRUE) {
          printf("\r\n task1 mutex locked \r\n");
          HAL_UART_Receive(&huart2, (uint8_t *)task1_c_array, 2, 1000); //UART_TIMEOUT
          printf("task1: %s \r\n", task1_c_array);
          osDelay(10);
          xSemaphoreGive(mutex);
        }
        //if(is_app_game01_running) {game01_task_timer();}
        // if(is_app_ledblink_running) {app_ledblink_task1();}
        // if(is_app_acc_running) {ACC_task1();}
        osDelay(1);
  }
}

/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
void StartTask02(void const * argument)
//void StartTask02()
{
  printf("\r\n task2 started \r\n");
  // char c_array[100+5] = "";
  while(true) {
    char c = 0;

    memset(task2_c_array, 0, 50*sizeof(char));

    if (xSemaphoreTake(mutex, 0) == pdTRUE) {
          printf("\r\n task2 mutex locked \r\n");
          HAL_UART_Receive(&huart2, (uint8_t *)task2_c_array, 50, 4000); //UART_TIMEOUT
          printf("task2: %s \r\n", task2_c_array);

          uint8_t ii = 0;
          for(ii = 0; task2_c_array[ii] != 0; ++ii) {
            c = task2_c_array[ii];
            cli_parser(c);
          }

          osDelay(10);
          xSemaphoreGive(mutex);
        }
    // HAL_UART_Receive(&huart2, (uint8_t *)&c, 1, UART_TIMEOUT);
    // HAL_UART_Transmit(&huart2, (uint8_t *)&c, 1, UART_TIMEOUT);
    // 
        //if(is_app_game01_running) {game01_task02();    }
    osDelay(1);
  }

}

/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
void StartTask03(void const * argument)
{
  printf("\r\n task3 started \r\n");
  while(true) {
        //if(is_app_game01_running) {game01_task01(); }
    osDelay(1);
  }
}


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
  ACC_Init();

  /* To enable printf() support for UART2 */
  RetargetInit(&huart2);
  cli_parser_init();

  printf("\r\n =============== \r\n Initiating tasks ... \r\n");

  mutex = xSemaphoreCreateMutex();

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityIdle, 0, 1024);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityNormal, 0, 1024);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, StartTask03, osPriorityHigh, 0, 512);
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
    //StartTask02();
  }
 
}


