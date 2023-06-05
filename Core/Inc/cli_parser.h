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
#if STM32_ENV==1
#include "app.h"
#else
#include "app_general.h"
#endif

#define CLI_PARSER_APP_COMMAND "app"
#define CLI_PARSER_READ_COMMAND "read"
#define CLI_PARSER_WRITE_COMMAND "write"
#define CLI_PARSER_HELP_COMMAND "help"

#define CLI_PARSER_ENABLE_TAG "enable"
#define CLI_PARSER_DISABLE_TAG "disable"
#define CLI_PARSER_ON_TAG "on"
#define CLI_PARSER_OFF_TAG "off"
#define CLI_PARSER_LIST_TAG "list"

#define CLI_PARSER_APP_GAME01_NAME "game01"
#define CLI_PARSER_APP_LEDBLINK_NAME "ledblink"
#define CLI_PARSER_APP_UART_NAME "uart_hw1"

#define CLI_PARSER_DEV_NAME_ADC "adc"
#define CLI_PARSER_DEV_NAME_GPIO "gpio"

#define CLI_PARSER_MAX_LENGTH_FOR_CMD 100
#define CLI_PARSER_MAX_NUMBER_OF_WORDS 3

#define CLI_PARSER_MAX_NUMBER_OF_APPS 10
#define CLI_PARSER_MAX_NUMBER_OF_CMDS 10
#define CLI_PARSER_MAX_NUMBER_OF_TAGS 10

void cli_parser(char c);
void cli_parser_init();

typedef struct {
    char            buf[CLI_PARSER_MAX_LENGTH_FOR_CMD + 5]; // array of chars
    unsigned int    length; //max stored of characters
} cli_parser_words_t;


// enumeration
typedef enum {
    CLI_PARSER_MAX_LENGTH_REACHED = 0,
    CLI_PARSER_SPECIAL_CHAR_DETECTED = 1,
    CLI_PARSER_CHAR_ADDED_SUCCESSFULLY = 2,
    CLI_PARSER_ERROR = 3
} cli_parser_return_t;

// enumeration
typedef enum {
    CLI_PARSER_TAG_ENABLE_INDEX = 0,
    CLI_PARSER_TAG_DISABLE_INDEX = 1,
    CLI_PARSER_TAG_ON_INDEX = 2,
    CLI_PARSER_TAG_OFF_INDEX = 3,
    CLI_PARSER_TAG_LIST_INDEX = 4
} cli_parser_tag_index_t;

typedef enum {
    CLI_PARSER_APP_LEDBLINK_INDEX = 0,
    CLI_PARSER_APP_GAME01_INDEX = 1,
    CLI_PARSER_APP_UART_INDEX = 2
} cli_parser_app_index_t;

typedef enum {
    CLI_PARSER_CMD_APP_INDEX = 0,
    CLI_PARSER_CMD_READ_INDEX = 1,
    CLI_PARSER_CMD_WRITE_INDEX = 2,
    CLI_PARSER_CMD_HELP_INDEX = 3
} cli_parser_cmd_index_t;

typedef enum {
    CLI_PARSER_CMP_TEXT_EQUAL = 0,
    CLI_PARSER_CMP_TEXT_DIFFERENT = 1
} cli_parser_compare_word_output_t;




#ifdef __cplusplus
}
#endif

#endif /* __CLI_PARSER_H */