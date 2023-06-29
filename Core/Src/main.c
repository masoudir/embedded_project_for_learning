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
#include "app_uart_hw1.h"
#include "app_card_reader_spi.h"

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;
SPI_HandleTypeDef hspi2;

osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;

extern bool is_app_game01_running;
extern bool is_app_ledblink_running;
extern bool is_app_uart_hw1_running;
bool mutex_value= false;
extern osMutexId  myMutex01Handle;



/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
void StartDefaultTask(void const * argument)
{
  printf("\r\n task1 started \r\n");
  while(true) {
     
        //if(is_app_game01_running) {game01_task_timer();}
        if(is_app_ledblink_running) {app_ledblink_task1();}

       

        if(is_app_uart_hw1_running) {
           if (xSemaphoreTake(myMutex01Handle, 0) == pdTRUE) {
            {app_uart_hw1_task1();}
                mutex_value = true;
                osDelay(1);
         xSemaphoreGive( myMutex01Handle );    
        }
    }   
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
  while(true) {
    char c = 0;


        // uint16_t tx_data = 0x3100;
        // uint16_t rx_data = 0x00;

        // { // First frame
        //         ACC_SPI_TX_Frame_t tx_frame = {
        //           .DATA = 0,
        //           .ADDR = ACC_REG_DATA_FORMAT,
        //           .MB = ACC_SPI_SINGLE_PACKET,
        //           .WR = ACC_SPI_WRITE_CMD
        //         };

        //         ACC_SPI_RX_Frame_t rx_frame = {0};

                
        //         ACC_SPI_TransmitReceive(&tx_frame, &rx_frame, 100);
        // }

        // { // Second frame
        //         ACC_SPI_TX_Frame_t tx_frame = {
        //           .DATA = 0,
        //           .ADDR = ACC_REG_DEVID,
        //           .MB = ACC_SPI_SINGLE_PACKET,
        //           .WR = ACC_SPI_READ_CMD
        //         };

        //         ACC_SPI_RX_Frame_t rx_frame = {0};

                
        //         ACC_SPI_TransmitReceive(&tx_frame, &rx_frame, 100);

        //         printf("\r\n spi rx=%02X \r\n", rx_frame.DATA_L);
        // }

    // rx_data would be changed after that function


 if (xSemaphoreTake(myMutex01Handle, 0) == pdTRUE){
    if(mutex_value){
    HAL_UART_Receive(&huart2, (uint8_t *)&c, 1, UART_TIMEOUT);
    HAL_UART_Transmit(&huart2, (uint8_t *)&c, 1, UART_TIMEOUT);
    cli_parser(c);
     osDelay(1);
    mutex_value = false;
     }
     xSemaphoreGive( myMutex01Handle );    
 }

        //if(is_app_game01_running) {game01_task02();    
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

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityIdle, 0, 512);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityNormal, 0, 512);
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


