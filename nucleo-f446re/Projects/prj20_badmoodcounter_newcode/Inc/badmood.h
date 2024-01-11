#ifndef __BADMOOD_H
#define __BADMOOD_H


#include <stdio.h>
#include <stdlib.h> 
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "retarget.h"
#include <string.h>
#include "timer.h"


typedef enum {
     LCD_mode_0,//welcome screen
     LCD_mode_1,//home screen
     LCD_mode_2,//setting
} LCD_mode;
// imagine below is a workspace, other functions can point to this space and work with the vars inside. 
typedef struct{
    int badmoodcount;
    LCD_mode lcdmode;
    int array[7];
    uint8_t seconds;
    RTC_TimeTypeDef gTime;
    RTC_DateTypeDef  sDate;
    bool Is_shifting_count_happened;
 
}badmood_t; 



void badmood_init(badmood_t * input);
void badmood_increase_task(badmood_t * input);
void badmood_decrease_task(badmood_t * input);
void badmood_update_time_and_date(badmood_t * input, RTC_HandleTypeDef *hrtc_ptr);
void badmood_update_UART_screen(badmood_t *input, UART_HandleTypeDef *huart);
void badmood_day_shift(badmood_t*input,UART_HandleTypeDef *huart);
bool badmood_is_right_time_to_save_count(badmood_t*input);

#endif /* __BADMOOD_H */
