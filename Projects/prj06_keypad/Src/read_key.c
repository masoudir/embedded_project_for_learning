
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
extern char row[4]={GPIO_PIN_6,GPIO_PIN_7,GPIO_PIN_8,GPIO_PIN_9};
extern char col[3]={GPIO_PIN_6,GPIO_PIN_7,GPIO_PIN_8};

char lookup_table[4][3]={
{'1' , '2' , '3'},
{'4' , '5' , '6'},
{'7' , '8' , '9'},
{'*' , '5' , '#'},

};

 void set_row(uint8_t i){
       int j;
      for (j=0; j< 4 ; j++){
         if (j==i){

            HAL_GPIO_WritePin(GPIOA ,row[i], SET);
                 }
         else{

            HAL_GPIO_WritePin(GPIOA, row[i], RESET);
             }
                           }
                         }

  int read_col(){
  
   if (HAL_GPIO_ReadPin( GPIOC,col[0]) ==1 && HAL_GPIO_ReadPin(GPIOC,col[1]) ==0 && HAL_GPIO_ReadPin(GPIOC,col[2]) ==0){
       return 1;}
   if (HAL_GPIO_ReadPin( GPIOC,col[0]) ==0 && HAL_GPIO_ReadPin(GPIOC,col[1]) ==1 && HAL_GPIO_ReadPin(GPIOC,col[2]) ==0){
       return 2;}
   if (HAL_GPIO_ReadPin( GPIOC,col[0]) ==0 && HAL_GPIO_ReadPin(GPIOC,col[1]) ==0 && HAL_GPIO_ReadPin(GPIOC,col[2]) ==1){
       return 3;}
        else{
         return 0;}
                }



 
 void read_keypad(){
       HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,SET);
        int column=0;
        int i;
        char button;
       
           for (i=0; i<4 ;i++)
                {
                   set_row(i);
                   column = read_col();
                     if(column > 0 ){
                         button = lookup_table[i][column-1];
                          printf(" %c pressed ",button);
                       
                                     }
                }


                      }
                      
   