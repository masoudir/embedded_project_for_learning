/**
  ******************************************************************************
  * @file           : app.h
  * @brief          : Header for app.c file.
  *                   
  ******************************************************************************
  * @attention
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_GENERAL_H
#define __APP_GENERAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
// #include <pthread.h>
#include <stdint.h>
#include "main.h"
#include "string.h"
#include "retarget.h"
#include <stdint.h>
#include <string.h>

#define UART_TIMEOUT 100

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);





#ifdef __cplusplus
}
#endif

#endif /* __APP_GAME01_H */