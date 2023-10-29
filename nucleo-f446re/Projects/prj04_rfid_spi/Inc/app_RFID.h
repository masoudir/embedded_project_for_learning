/**
 ******************************************************************************
 * @file           : app_RFID.h
 * @brief          : Header for app_RFID.c file.
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
#ifndef __APP_RFID_H
#define __APP_RFID_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <MFRC522.h>
#include "app_general.h"

  void RFID_task1();
  void RFID_setup();
#ifdef __cplusplus
}
#endif

#endif /* __APP_RFID_H */