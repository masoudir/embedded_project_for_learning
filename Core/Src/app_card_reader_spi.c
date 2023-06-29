 
 /**
  ******************************************************************************
  * @file           : app_card_reader_spi.c
  * @brief          : RFID functions body
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
 
 
// #include <app_card_reader_spi.h>
// #include <MFRC522.h>

// #define RFID_SS  10
// #define RFID_RST 9

// MFRC522 rfid( RFID_SS, RFID_RST );

// byte data[MAX_LEN];
// byte uid[5];
// byte last_uid[5]; 
// byte clear_uid[] = {0,0,0,0,0};
// char tmp[20];

// int led = 3;

// unsigned long currentTime;
// unsigned long cloopTime;

// void setup() {
//   SPI.begin();
//   Serial.begin(9600);
//   rfid.begin();
//   currentTime = millis();
//   cloopTime = currentTime;  
//   pinMode(led, OUTPUT);  
// }

// void loop() {

//   if ( rfid.requestTag( MF1_REQIDL, data ) == MI_OK ) {
//     if ( rfid.antiCollision( data ) == MI_OK ) {
//       memcpy( uid, data, 5 );
//       if(memcmp(uid, last_uid,5)!=0){
//         memcpy( last_uid, uid, 5 );     
//         // Format data for output - HEX
//         sprintf( tmp, "%02X%02X%02X%02X%02X" , uid[0], uid[1], uid[2], uid[3], uid[4]);
//         Serial.println(tmp);
//         digitalWrite(led, HIGH);
//         cloopTime = millis();
//       }  
//     }
//   } 
  
//   // Timeout functions
//   currentTime = millis();
//   if(currentTime >= (cloopTime + (500)))
//   {
//     // Turn off LED after 500ms
//     digitalWrite(led, LOW);
//   }   
//   if(currentTime >= (cloopTime + (2000)))
//   {
//     // Clear last used tag id after 2s so it can be swiped again
//      memcpy( last_uid, clear_uid, 5 );
//   }   
  
// }
 