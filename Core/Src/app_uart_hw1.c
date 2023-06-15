/**
  ******************************************************************************
  * @file           : app_uart_hw1.c
  * @brief          : Some uart functions body
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
 #include "app_uart_hw1.h"

 
 uint8_t received_char;

 extern UART_HandleTypeDef huart2;

 void app_uart_hw1_task1() {
    
   // Wait until a character is received
     (HAL_UART_Receive(&huart2, &received_char, 1, HAL_MAX_DELAY) != HAL_OK);
    
    // Echo the received character back
       HAL_UART_Transmit(&huart2, &received_char, 1, HAL_MAX_DELAY);
  }

    

  

 
