/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32f4xx_it.h"

#define BUTTON_STATE_FOR_CLICK1 0
#define BUTTON_STATE_FOR_CLICK2 2

extern int i;
extern uint32_t counter;
extern int n;
extern int j;
extern int k;

uint32_t timer_count = 0;
uint32_t time_bet[4] = {};
uint8_t button_state = 0;
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart2;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

// /**
//   * @brief This function handles TIM1 trigger and commutation interrupts and TIM11 global interrupt.
//   */
// void TIM1_TRG_COM_TIM11_IRQHandler(void)
// {
//   /* USER CODE BEGIN TIM1_TRG_COM_TIM11_IRQn 0 */

//   /* USER CODE END TIM1_TRG_COM_TIM11_IRQn 0 */
//   HAL_TIM_IRQHandler(&htim1);
//   /* USER CODE BEGIN TIM1_TRG_COM_TIM11_IRQn 1 */
//   HAL_UART_Transmit(&huart2, (const uint8_t*)"tick", 4, 100);
//   /* USER CODE END TIM1_TRG_COM_TIM11_IRQn 1 */
// }

void increase_digit() {
  ++counter;
  if (counter >= 10) {
    counter = 0;
  }
  display_digit(counter-1);
  printf("%ld = count\n\r", counter);
}

void decrease_digit() {
  if( counter == 0) {
    counter = 9;
  } else {
    --counter;
  }

  display_digit(counter-1);
  printf("%ld = count\n\r", counter);
}

void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim2);
  ++timer_count;
 //printf("%ld = time\n\r",timer_count);
  if(button_state == 1 && HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == GPIO_PIN_RESET) {
    button_state = 2;
     timer_count = 0;
  
  } 
    else if(button_state == 2 && timer_count  > 10) {
    increase_digit();
    button_state = 0;
      // printf("%ld = time\n\r",timer_count);
  }  

  else if (button_state == 3 && HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == GPIO_PIN_RESET) {
     
    decrease_digit();
    button_state = 0;
  } 

 // HAL_UART_Transmit(&huart2, (const uint8_t*)"hey", 3, 100);
//  if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0)== GPIO_PIN_SET){
//  i++;
//       printf("%d = i\n\r",i);
//   k=0;    
 
//    if (i>=3 && k==0){   
      
//      counter++;
//           k=1;
//             display_digit(counter-1);
//     printf("%ld = count\n\r",counter);}
//       if (counter >= 10) {
//          counter = 0;
//       }

//   } 
//  else {
  
//       k=0;
//       i=0;
//     } 
}

 


/* USER CODE BEGIN 1 */

/* USER CODE END 1 */


void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */

  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  
  if(button_state == BUTTON_STATE_FOR_CLICK1) {
    timer_count = 0;
    // event_timer_count[0] = timer_count;
    button_state = 1;
  } 
   else if(button_state == BUTTON_STATE_FOR_CLICK2) {
    
       button_state = 3;
     }
  } 
  /* USER CODE BEGIN EXTI0_IRQn 1 */

//  if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0)== GPIO_PIN_SET){
     
    //          counter++;
    // display_digit(counter-1);
    // printf("%ld = count\n\r",counter);
    // }

    //   if (counter >= 10) {
    //      counter = 0;
    //   }




