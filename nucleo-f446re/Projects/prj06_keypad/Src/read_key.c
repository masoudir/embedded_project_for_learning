
 /* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : read_key.c
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
/* Includes -------------------------------------------------------------*/
 #include "read_key.h"
 extern UART_HandleTypeDef huart2;
extern uint16_t row[4];
extern uint16_t col[3];

char lookup_table[4][3]={
{'1' , '2' , '3'},
{'4' , '5' , '6'},
{'7' , '8' , '9'},
{'*' , '0' , '#'},

};

 void set_row(uint8_t i) {

  uint8_t j;

   for (j=0; j< 4 ; j++) {

     if (j==i) {

        HAL_GPIO_WritePin(GPIOA ,row[i], GPIO_PIN_SET);

        }

     else{

        HAL_GPIO_WritePin(GPIOA, row[j],GPIO_PIN_RESET);

       } 

       //printf(" %d = i\n\r ",j);
       // HAL_Delay(1000);
      }
  }

  int read_col(){
    bool col[3] = {};
    col[0] = HAL_GPIO_ReadPin( GPIOC,GPIO_PIN_6);
    col[1] = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7);
    col[2] = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_8);

    printf("%d %d %d \r\n", col[0], col[1], col[2]);
    //if ((HAL_GPIO_ReadPin( GPIOC,col[0]) ==GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(GPIOC,col[1]) ==GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(GPIOC,col[2]) == GPIO_PIN_RESET) ){ 
      // return 0;}
   if ((col[0] ==GPIO_PIN_SET) && (col[1] ==GPIO_PIN_RESET)  &&( col[2] == GPIO_PIN_RESET) ){ 
       return 1;}
   else if ((col[0] ==GPIO_PIN_RESET) && (col[1] == GPIO_PIN_SET) && (col[2] == GPIO_PIN_RESET )){
       return 2;}
   else if ((col[0] ==GPIO_PIN_RESET)  && (col[1] == GPIO_PIN_RESET)  && (col[2] == GPIO_PIN_SET)){
       return 3;}

       return 0;
                }



 
 void read_keypad(){
       
    int column=0;
    uint8_t i;
    char button;
       
   for (i=0; i<4 ;i++)
    {
                     
     set_row(i);
     column = read_col();
                  //printf(" %d = COLUMN\n\r ",column);
                      //    HAL_Delay(500);
     if(column > 0 ){
                        
     button = lookup_table[i][column-1];
     printf(" %c pressed \n\r",button);
      HAL_Delay(100);
      }
    }  
     /* HAL_GPIO_WritePin(GPIOA , GPIO_PIN_7, GPIO_PIN_SET);
      read_col();
        column = read_col();
printf(" %d COLUMN\n\r ",column); */
  }
                      
   