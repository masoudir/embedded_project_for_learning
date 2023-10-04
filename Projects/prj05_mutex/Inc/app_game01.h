/* USER CODE BEGIN Header */
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
#ifndef __APP_GAME01_H
#define __APP_GAME01_H

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
#include "cmsis_os.h"
#include "retarget.h"

#define GAME_WALL_PATTERN_PERIOD_SECOND     10
#define GAME_LENGTH                         20
#define GAME_WALL_CHAR                      'I'
#define GAME_USER_CORRECT_CHAR              'o'
#define GAME_USER_FAIL_CHAR                 'x'

void game01_task01();
void game01_task02();
void game01_task_wait(unsigned int ms);
void game01_task_timer();

#ifdef __cplusplus
}
#endif

#endif /* __APP_GAME01_H */