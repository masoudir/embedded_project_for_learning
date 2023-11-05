
#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include"stm32f4xx_hal_spi.h"
#include <stdbool.h>

typedef enum {
     LCD_mode_0,//welcome screen
     LCD_mode_1,//home screen
     LCD_mode_2,//setting
} LCD_mode;

void Error_Handler(void);



#endif /* __MAIN_H */
