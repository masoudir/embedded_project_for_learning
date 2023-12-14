#include"badmood.h"
#include <stdio.h>
#include <stdlib.h> 
#include <stdint.h>
// extern int16_t badmoodcount;
// extern uint32_t count0;
// extern int mytime;
// extern int array[7];
// extern LCD_mode lcdmode;
// extern uint8_t hours;
// extern uint8_t minutes;
// extern uint8_t seconds;
// extern char buff[16];
// extern char buff2[16];
// extern RTC_HandleTypeDef hrtc;
// extern RTC_TimeTypeDef gTime;
// extern RTC_DateTypeDef  sDate;


typedef enum {
     LCD_mode_0,//welcome screen
     LCD_mode_1,//home screen
     LCD_mode_2,//setting
} LCD_mode;
// think below is a workspace, other functions can point to this space and work with the var inside. 
typedef struct{
    int count;
    LCD_mode lcdmode;
    int array[7];
    uint8_t seconds;
    RTC_TimeTypeDef gTime;
    RTC_DateTypeDef  sDate;
 
}badmood_t; 


void badmood_init(badmood_t * input){
    input->count=0;
    input->lcdmode=LCD_mode_0;
    input->array[7]={};
    input->seconds=0;

};
//bad mood task: to increase or decrease the count
void badmood_increase_task(badmood_t * input){
     input->count++;
};

void badmood_decrease_task(badmood_t * input){
     input->count--;
};


//bad time task: 
void badmood_time_task(badmood_t * input, RTC_HandleTypeDef *hrtc) {
    HAL_RTC_GetTime(hrtc , &input->gTime , RTC_FORMAT_BIN);
    HAL_RTC_GetDate(hrtc , &input->sDate , RTC_FORMAT_BIN);
};

//bad shift task: to shift to another day