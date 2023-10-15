/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : read.keypad.c
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
#include read.keypad.h

char key;
char keypadLayout[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};
char readKeypad(void) {
   GPIO_PinState rowPins[ROWS]= {GPIO_PIN_RESET};
   GPIO_PinState colsPins[COLS]= {GPIO_PIN_RESET};

     for (int i = 0; i < ROWS; i++) {
 
       HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 << i, SET);

         for (int j = 0; j < COLS; j++) {

            if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == GPIO_PIN_SET ||
                 HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_SET ||
                  HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == GPIO_PIN_SET) {
                     rowPins[i] = GPIO_PIN_SET;
                }
             }
         }  
         
         for (int i = 0; i < ROWS; i++) {
           if (rowPins[i] == GPIO_PIN_SET) {
               for (int j = 0; j < COLS; j++) {
                if (colPins[j] == GPIO_PIN_SET) {
          
          return keypadLayout[i][j];
        }
       }
     }
   }
    return 0;
 }
     
