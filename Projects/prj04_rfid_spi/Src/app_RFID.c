/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : app_RFID.c
  * @brief          :  task
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


#include "app_RFID.h"


#define RFID_SS  10
#define RFID_RST 9

extern SPI_HandleTypeDef hspi2;
//rfid( RFID_SS, RFID_RST );

byte data[MAX_LEN];
byte uid[5];
byte last_uid[5]; 
byte clear_uid[] = {0,0,0,0,0};
char tmp[20];



void RFID_task1(){
printf("hello fary");
  if ( MFRC522_requestTag( MF1_REQIDL, data ) == MI_OK ) {
    printf("hello");
    if ( MFRC522_antiCollision( data ) == MI_OK ) {
      
      memcpy( uid, data, 5 );
      if(memcmp(uid, last_uid,5)!=0){
        memcpy( last_uid, uid, 5 );     
        // Format data for output - HEX
        printf( "\r\n tmp:%02X%02X%02X%02X%02X \r\n" , uid[0], uid[1], uid[2], uid[3], uid[4]);
      
       HAL_Delay(100);
      }  
    }
  }

  }
  
 

 