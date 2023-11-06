
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
extern char row[4];
extern char col[3];

char lookup_table[4][3]={
{'1' , '2' , '3'},
{'4' , '5' , '6'},
{'7' , '8' , '9'},
{'*' , '0' , '#'},

};

 void set_col(uint8_t i){
     int j;
    for (j=0; j< 4 ; j++){
       if (j==i) {

        HAL_GPIO_WritePin(GPIOC ,col[i], SET);
                 }
       else{
            HAL_GPIO_WritePin(GPIOC, col[i], RESET);
             } 
      //  printf(" %d ist i\n\r",i);
                           }
                         }


  int read_row(){
  //if ((HAL_GPIO_ReadPin( GPIOA,row[0]) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(GPIOA,row[1]) ==GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(GPIOA,row[2]) ==GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(GPIOA,row[3]) ==GPIO_PIN_RESET)){ 
      // return 0;}
   if ((HAL_GPIO_ReadPin( GPIOA,row[0]) == GPIO_PIN_SET) && (HAL_GPIO_ReadPin(GPIOA,row[1]) ==GPIO_PIN_RESET)  &&( HAL_GPIO_ReadPin(GPIOA,row[2]) ==GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(GPIOA,row[3]) ==GPIO_PIN_RESET)){ 
       return 1;}
   else if ((HAL_GPIO_ReadPin( GPIOA,row[0]) == GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(GPIOA,row[1]) ==GPIO_PIN_SET) && (HAL_GPIO_ReadPin(GPIOA,row[2]) ==GPIO_PIN_RESET ) && (HAL_GPIO_ReadPin(GPIOA,row[3]) ==GPIO_PIN_RESET)){
       return 2;}
   else if ((HAL_GPIO_ReadPin( GPIOA,row[0]) == GPIO_PIN_RESET)  && (HAL_GPIO_ReadPin(GPIOA,row[1]) ==GPIO_PIN_RESET)  && (HAL_GPIO_ReadPin(GPIOA,row[2]) ==GPIO_PIN_SET) && (HAL_GPIO_ReadPin(GPIOA,row[3]) ==GPIO_PIN_RESET)){
       return 3;}
   else if ((HAL_GPIO_ReadPin( GPIOA,row[0]) == GPIO_PIN_RESET)  && (HAL_GPIO_ReadPin(GPIOA,row[1]) ==GPIO_PIN_RESET)  && (HAL_GPIO_ReadPin(GPIOA,row[2]) ==GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(GPIOA,row[3]) ==GPIO_PIN_SET)){
       return 4;} 
        return 0;  
                }



 
 void read_keypad(){
       //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,SET);
   int column=0;
   int i;
   char button;
       
    for (i=0; i<4 ;i++)
      {
       set_col(i);
       column = read_row();
                  printf(" %d COLUMN\n\r ",column);
                   // HAL_UART_Transmit(&huart2, (const uint8_t*)"hey1", 3, 100);
                          //HAL_Delay(500);
         if(column > 0 ){
                        
             button = lookup_table[column-1][i];
             printf(" %c pressed ",button);
             HAL_Delay(10);
          }
      }
 }
                      
   