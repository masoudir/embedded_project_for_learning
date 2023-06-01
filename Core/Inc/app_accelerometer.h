/**
  ******************************************************************************
  * @file           : app_accelerometer.h
  * @brief          : Header for app_accelerometer.c file.
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
#ifndef __APP_ACC_H
#define __APP_ACC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "app_general.h"

HAL_StatusTypeDef ACC_SPI_TransmitReceive(uint16_t* pTxData, uint16_t* pRxData, uint32_t Timeout);

#ifdef __cplusplus
}
#endif

#endif /* __APP_LEDBLINK_H */