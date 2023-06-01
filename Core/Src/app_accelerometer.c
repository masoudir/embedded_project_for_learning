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

ACC_SPI_Config_t acc_spi_config = {0};

void ACC_Init() {
    
    acc_spi_config.CS_PORT = GPIOB;
    acc_spi_config.CS_PIN = GPIO_PIN_12;

    GPIO_InitTypeDef gpio_cs = {
        .Pin = acc_spi_config.CS_PIN,
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_HIGH,
        .Alternate = 0
    };

    HAL_GPIO_Init(acc_spi_config.CS_PORT, &gpio_cs);
    
    init_spi(&hspi2);
}

HAL_StatusTypeDef ACC_SPI_TransmitReceive(ACC_SPI_TX_Frame_t* pTxData, ACC_SPI_RX_Frame_t* pRxData, uint32_t Timeout) {
    HAL_StatusTypeDef status;
    HAL_GPIO_WritePin(acc_spi_config.CS_PORT, acc_spi_config.CS_PIN, GPIO_PIN_RESET);
    status = HAL_SPI_TransmitReceive(&hspi2, (uint8_t*)pTxData, (uint8_t*)pRxData, 2, Timeout);
    HAL_GPIO_WritePin(acc_spi_config.CS_PORT, acc_spi_config.CS_PIN, GPIO_PIN_SET);
    return status;
}