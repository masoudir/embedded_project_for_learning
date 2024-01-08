
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

extern RTC_HandleTypeDef hrtc;
extern badmood_t badmood_env;


void badmood_init(badmood_t * input){
    input->badmoodcount=0;
    input->lcdmode=LCD_mode_0;
   // input->array = (int*){0,0,0,0,0,0,0};
   memset(input->array,0,7*sizeof(int)); // pay attention to the size of intO
    input->seconds=0;
    input->Is_shifting_count_happened=false;

};
//bad mood task: to increase or decrease the count
void badmood_increase_task(badmood_t * input){
     input->badmoodcount++;
};

void badmood_decrease_task(badmood_t * input){
     input->badmoodcount--;
};

void badmood_update_time_and_date(badmood_t * input, RTC_HandleTypeDef *hrtc_ptr) {
    HAL_RTC_GetTime(hrtc_ptr , &input->gTime , RTC_FORMAT_BIN);
    HAL_RTC_GetDate(hrtc_ptr , &input->sDate , RTC_FORMAT_BIN);
};

void badmood_update_UART_screen(badmood_t *input, UART_HandleTypeDef *huart){
   if(input->lcdmode==LCD_mode_0){
    char BUFFER_welcome[100]={0};
    sprintf(BUFFER_welcome, "hi, welcome to badmoodcounter, please press key2 to continue\r\n");
    HAL_UART_Transmit(huart, (const uint8_t*)BUFFER_welcome, 100, 1000);
// show the time 
    char BUFFER_time[16]={0};
    char BUFFER_date[16]={0};

    HAL_RTC_GetTime(&hrtc , &input->gTime , RTC_FORMAT_BIN);// input->gTime
    sprintf (BUFFER_time,"%2.2d:%2.2d:%2.2d \r\n",input->gTime.Hours,input->gTime.Minutes,input->gTime.Seconds);
    HAL_UART_Transmit(huart, (const uint8_t*)BUFFER_time, 16, 1000);

    HAL_RTC_GetDate(&hrtc , &input->sDate , RTC_FORMAT_BIN);
    sprintf (BUFFER_date,"20%2.2d.%2.2d.%2.2d\r\n", input->sDate.Year, input->sDate.Month, input->sDate.Date);
    HAL_UART_Transmit(huart, (const uint8_t*)BUFFER_date, 16, 1000);              
    
    HAL_Delay(1000);


//  show the separat line
  

    char BUFFER_line[100]={0};
    sprintf(BUFFER_line, "-----------------------------------------------------------------\r\n");
    HAL_UART_Transmit(huart, (const uint8_t*)BUFFER_line, 100, 1000);
   }



   if(input->lcdmode==LCD_mode_1) {

    char BUFFER_homescreen[30]={0};
    sprintf(BUFFER_homescreen, "home screen current time \r\n");
    HAL_UART_Transmit(huart, (const uint8_t*)BUFFER_homescreen, 30, 1000);


    // show the time and date
    char BUFFER_time[16]={0};
    char BUFFER_date[16]={0};

    HAL_RTC_GetTime(&hrtc , &input->gTime , RTC_FORMAT_BIN);// input->gTime
    sprintf (BUFFER_time,"%2.2d:%2.2d:%2.2d \r\n",input->gTime.Hours,input->gTime.Minutes,input->gTime.Seconds);
    HAL_UART_Transmit(huart, (const uint8_t*)BUFFER_time, 16, 1000);

    HAL_RTC_GetDate(&hrtc , &input->sDate , RTC_FORMAT_BIN);
    sprintf (BUFFER_date,"20%2.2d.%2.2d.%2.2d\r\n", input->sDate.Year, input->sDate.Month, input->sDate.Date);
    HAL_UART_Transmit(huart, (const uint8_t*)BUFFER_date, 16, 1000);              
    
    HAL_Delay(1000);

    // show current badmoodcount

        char BUFFER_badmoodwords[50]={0};
        sprintf(BUFFER_badmoodwords, "current badmood is %d\r\n", input->badmoodcount);
        HAL_UART_Transmit(huart, (const uint8_t*)BUFFER_badmoodwords, 50, 1000);


   
     // show late seven days records

        char BUFFER_7days[100]={0};


        sprintf(BUFFER_7days, "last 7days record:%d %d %d %d %d %d %d\r\n", input->array[0], input->array[1],input->array[2],input->array[3],input->array[4],input->array[5],input->array[6]);
        HAL_UART_Transmit(huart, (const uint8_t*)BUFFER_7days, 100, 1000);

        char BUFFER_line[100]={0};
        sprintf(BUFFER_line, "-----------------------------------------------------------------\r\n");
        HAL_UART_Transmit(huart, (const uint8_t*)BUFFER_line, 100, 1000);
  
    } 




     

  if(input->lcdmode==LCD_mode_2){
        char BUFFER_settingscreen[100]={0};
        sprintf(BUFFER_settingscreen, "This is setting screen\r\n");
        HAL_UART_Transmit(huart, (const uint8_t*)BUFFER_settingscreen, 100, 1000);
        
        char BUFFER_line[100]={0};
        sprintf(BUFFER_line, "-----------------------------------------------------------------\r\n");
        HAL_UART_Transmit(huart, (const uint8_t*)BUFFER_line, 100, 1000);

   } 
}


void badmood_day_shift(badmood_t*input){
  
  input->array[0]=input->badmoodcount;

      for (int j = 5; j >= 0; j--) {
        input->array[j+1] = input->array[j];
      }; 
   
      input->badmoodcount=0;
      input->array[0]=0;
      //mytime=0;
  
}
bool badmood_is_right_time_to_save_count(badmood_t*input, RTC_HandleTypeDef*hrtc){

}