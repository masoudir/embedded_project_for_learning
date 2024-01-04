
#include "badmood.h"
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


void badmood_init(badmood_t * input){
    input->count=0;
    input->lcdmode=LCD_mode_0;
   // input->array = (int*){0,0,0,0,0,0,0};
   memset(input->array,0,7*sizeof(int)); // pay attention to the size of intO
    input->seconds=0;

};
//bad mood task: to increase or decrease the count
void badmood_increase_task(badmood_t * input){
     input->count++;
};

void badmood_decrease_task(badmood_t * input){
     input->count--;
};


//bad time task: HAL_StatusTypeDef HAL_RTC_GetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, uint32_t Format);

void badmood_time_task(badmood_t * input, RTC_HandleTypeDef *hrtc_ptr) {
    HAL_RTC_GetTime(hrtc_ptr , &input->gTime , RTC_FORMAT_BIN);
    HAL_RTC_GetDate(hrtc_ptr , &input->sDate , RTC_FORMAT_BIN);
};

//bad shift task: to shift to another day