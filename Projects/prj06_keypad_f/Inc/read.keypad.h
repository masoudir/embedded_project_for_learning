/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : read.keypad.h
  * @brief          : Header for read.keypad.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __READ.KEYPAD_H
#define __READ.KEYPAD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"


char readKeypad(void);

/* Private defines -----------------------------------------------------------*/
#define ROWS 4
#define COLS 3

#ifdef __cplusplus
}
#endif

#endif /* __REAS.KEYPAD_H */
