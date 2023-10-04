/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app.c
  * Description        : Code for app applications
  ******************************************************************************
  * @attention
  *
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_game01.h"

extern UART_HandleTypeDef huart2;

unsigned int time_1s_counter = 0;

unsigned int user_pos = GAME_LENGTH / 2;

char buf[GAME_LENGTH + 5] = "";

void create_wall() {
    unsigned int i;
    unsigned int free_space = 0;
    unsigned int imin, imax;

    if(time_1s_counter%GAME_WALL_PATTERN_PERIOD_SECOND == 0) {
        free_space = 4;
    } else {
        free_space = 6;
    }
    
    imin = ((GAME_LENGTH - free_space) / 2) - 1;
    imax = GAME_LENGTH - imin + 1;
    
    for(i = 0; i < GAME_LENGTH; i++) {
        if(i != user_pos && (i <= imin || i >= imax)) {
            buf[i] = GAME_WALL_CHAR;    
        }
        else if(i == user_pos && (user_pos <= imin || user_pos >= imax)) {
            buf[i] = GAME_USER_FAIL_CHAR;
        }
        else if(i == user_pos && (user_pos > imin && user_pos < imax)) {
            buf[i] = GAME_USER_CORRECT_CHAR;
        }
        else {
            buf[i] = ' ';
        }
        
    }
}


void game01_task01() {
    create_wall();
    printf("%s\r\n", buf);
    // buf[GAME_LENGTH - 2] = '\r';
    // buf[GAME_LENGTH - 1] = '\n';
    // HAL_UART_Transmit_IT(&huart2, (const uint8_t *)buf, GAME_LENGTH);
    game01_task_wait(1000);
}

void game01_task02() {
    char c = 0;
    HAL_UART_Receive_IT(&huart2, (uint8_t *)&c, 1);
    // c = getchar();
    if(c == 'a') {
        ++user_pos;
    } else if(c == 'd') {
        --user_pos;
    }
    //printf("received=%c %d\n", c, c);
}

void game01_task_wait(unsigned int ms) {
    // sleep((1.0f / 1000.0f) * ms);
    osDelay(ms);
}

void game01_task_timer() {
    game01_task_wait(1000);
    ++time_1s_counter;
}
