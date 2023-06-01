/**
  ******************************************************************************
  * @file           : app_accelerometer.c
  * @brief          : Accelerometer functions body
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

#include "app_accelerometer.h"

extern SPI_HandleTypeDef hspi2;

HAL_StatusTypeDef ACC_SPI_TransmitReceive(uint16_t* pTxData, uint16_t* pRxData, uint32_t Timeout) {
    HAL_StatusTypeDef status;
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    status = HAL_SPI_TransmitReceive(&hspi2, (uint8_t*)pTxData, (uint8_t*)pRxData, 2, Timeout);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
    return status;
}