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



typedef struct {
    GPIO_TypeDef *CS_PORT;  // PORT NAME OF CS
    uint16_t CS_PIN;        // PIN NAME OF CS
} ACC_SPI_Config_t;

typedef struct {
  uint8_t DATA : 8; // (bit7-bit0)
  uint8_t ADDR : 6; // (bit13-bit8)
  bool MB : 1; // (bit14)
  bool WR : 1; // Write=0, Read=1  (bit15)
} ACC_SPI_TX_Frame_t; // (16bits)

typedef struct {
  uint8_t DATA_L : 8; // (bit7-bit0)
  uint8_t DATA_H : 8; // (bit15-bit8)
} ACC_SPI_RX_Frame_t; // (16bits)

typedef enum {
  ACC_SPI_WRITE_CMD = 0,
  ACC_SPI_READ_CMD = 1
} ACC_SPI_WR_BIT_t;

typedef enum {
  ACC_SPI_SINGLE_PACKET = 0
} ACC_SPI_MB_BIT_t;

typedef enum {
  ACC_RES_10bits = 0,
  ACC_RES_13bits = 1
} ACC_RES_t;

typedef enum {
  ACC_REG_DEVID = 0x00,
  ACC_REG_THRESH_TAP = 0x1D,
  ACC_REG_OFSX = 0x1E,
  ACC_REG_DATA_FORMAT = 0x31,
  ACC_REG_DATAX0 = 0x32,
  ACC_REG_DATAX1 = 0x33
} ACC_SPI_REG_ADDR_t;

typedef struct {
  uint8_t RANGE : 2; // (bit1-bit0)
  bool JUSTIFY : 1; // (bit2)
  bool FULL_RES : 1; // (bit3)
  bool RESERVED : 1; // (bit4)
  bool INT_INVERT : 1; // (bit5)
  bool SPI : 1; // (bit6)
  bool SELF_TEST : 1; // (bit7)
} ACC_REG_DATA_FORMAT_t; // (8bits)

void ACC_Init();
HAL_StatusTypeDef ACC_SPI_TransmitReceive(ACC_SPI_TX_Frame_t* pTxData, ACC_SPI_RX_Frame_t* pRxData, uint32_t Timeout);

void ACC_SPI_ConfigFullDuplexMode();
void ACC_SPI_GetDevID();
void ACC_SPI_GetAccX0();
void ACC_SPI_GetAccX1();

#ifdef __cplusplus
}
#endif

#endif /* __APP_LEDBLINK_H */