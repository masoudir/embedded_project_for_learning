/**
  ******************************************************************************
  * @file           : cli_parser.h
  * @brief          : Header for cli_parser.c file.
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
#ifndef __CLI_PARSER_H
#define __CLI_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "app_general.h"

#define CLI_PARSER_APP_COMMAND "app"
#define CLI_PARSER_READ_COMMAND "read"
#define CLI_PARSER_WRITE_COMMAND "write"

#define CLI_PARSER_ENABLE_COMMAND "enable"
#define CLI_PARSER_DISABLE_COMMAND "disable"
#define CLI_PARSER_ON_COMMAND "on"
#define CLI_PARSER_OFF_COMMAND "off"

#define CLI_PARSER_APP_GAME01_NAME "game01"
#define CLI_PARSER_APP_LEDBLINK_NAME "ledblink"

#define CLI_PARSER_DEV_NAME_ADC "adc"
#define CLI_PARSER_DEV_NAME_GPIO "gpio"


#ifdef __cplusplus
}
#endif

#endif /* __CLI_PARSER_H */