/**
  ******************************************************************************
  * @file           : app_ledblink.c
  * @brief          : Some LED blink functions body
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

#include "app_ledblink.h"

/* Private variables ---------------------------------------------------------*/
extern UART_HandleTypeDef huart2;

bool app_ledblink_status = false;

void app_ledblink_task1() {
  if(app_ledblink_status) {
     HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
  } else {
     HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
  }
  app_ledblink_status = !app_ledblink_status;
  osDelay(1000);
}