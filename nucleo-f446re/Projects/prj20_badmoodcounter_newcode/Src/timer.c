#include "timer.h"
#include "GPIO.h"
#include "badmood.h"
#include "main.h"
#include "badmood.h"
extern badmood_t badmood_env;

TIM_HandleTypeDef htim2;//0.1s
TIM_HandleTypeDef htim3;//1s


uint32_t count0;

int mytime;

 uint8_t hours = 0, minutes = 0, seconds = 0;

void MX_TIM2_Init(void)
{

  /* 
        Enable clock to Timer-2 
        
        NOTE: This is lagacy Macro. The better approach is the
        use of HAL_TIM_ConfigClockSource function.
    */
    __HAL_RCC_TIM2_CLK_ENABLE();
    
    /*
        From STM32F407 datasheet, Timer2 is clocked from
        APB1 bus (42Mhz max). In default configuration
        Timer-2 is receiving 16Mhz (HSI) bus clock.
    */        
    
    /***************************************************
                   Timer-2 Configuration:
    ****************************************************/
    
    /* Select Timer-2 for further configuration */
    htim2.Instance = TIM2;
    
    /*
        Divide the timer-2 input frequency (16Mhz)
        by a factor of 1000 (16,000,000/1,000 = 16,000 = 16Khz) 
    */
    htim2.Init.Prescaler   = 5000;
    
    #if (UP_COUNTER)
     /* Up-Counter mode*/
     htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    #else 
      htim2.Init.CounterMode = TIM_COUNTERMODE_DOWN;        
    #endif

    /*
        We want the time count to be 500msec (half a second).
        As the input frequency is 16khz so the total
        counts required for 500msec delay:
        new 0.1s
        
        total counts = 100msec * f
                     = (.1sec) * 16,000
                     = 1600
                     = 0x1F40
    */
    htim2.Init.Period = 3200;
        
    /*
        Finally initialize Timer-2
    */
    while (HAL_TIM_Base_Init(&htim2)!= HAL_OK);

    /*
        Enable timer-2 IRQ interrupt
    */
    HAL_TIM_Base_Start_IT(&htim2);

    /* Enable interrupt at IRQ-Level */
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
    
    /*
        Start the timer
    */
    HAL_TIM_Base_Start(&htim2);
}


void MX_TIM3_Init(void)
{

  /* 
        Enable clock to Timer-2 
        
        NOTE: This is lagacy Macro. The better approach is the
        use of HAL_TIM_ConfigClockSource function.
    */
    __HAL_RCC_TIM3_CLK_ENABLE();
    
    /*
        From STM32F407 datasheet, Timer2 is clocked from
        APB1 bus (42Mhz max). In default configuration
        Timer-2 is receiving 16Mhz (HSI) bus clock.
    */        
    
    /***************************************************
                   Timer-2 Configuration:
    ****************************************************/
    
    /* Select Timer-2 for further configuration */
    htim3.Instance = TIM3;
    
    /*
        Divide the timer-2 input frequency (16Mhz)
        by a factor of 1000 (16,000,000/1,000 = 16,000 = 16Khz) 
    */
    htim3.Init.Prescaler   = 1000;
    
    #if (UP_COUNTER)
     /* Up-Counter mode*/
     htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    #else 
      htim3.Init.CounterMode = TIM_COUNTERMODE_DOWN;        
    #endif

    /*
        We want the time count to be 500msec (half a second).
        As the input frequency is 16khz so the total
        counts required for 500msec delay:
        new 0.1s
        
        total counts = 1000msec * f
                     = (1sec) * 16,000
                     = 16000
                     
    */
    htim3.Init.Period = 16000;
        
    /*
        Finally initialize Timer-3
    */
    while (HAL_TIM_Base_Init(&htim3)!= HAL_OK);

    /*
        Enable timer-2 IRQ interrupt
    */
    HAL_TIM_Base_Start_IT(&htim3);

    /* Enable interrupt at IRQ-Level */
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
    
    /*
        Start the timer
    */
    HAL_TIM_Base_Start(&htim3);
}

void TIM3_IRQHandler(void)
{
 
  HAL_TIM_IRQHandler(&htim3);// timer 1s
      //  system("clear"); 
        seconds++;
        if (seconds == 60) {
            seconds = 0;
            minutes++;
            if (minutes == 60) {
                minutes = 0;
                hours++;
                if (hours == 24) {
                    hours = 0;
                }
            }
        }

     badmood_increase_task(&badmood_env);
     badmood_decrease_task(&badmood_env);

 
     
        
  mytime++;
  badmood_env.array[0]=badmood_env.badmoodcount;
  if(mytime==50){ 
      for (int j = 5; j >= 0; j--) {
        badmood_env.array[j+1] = badmood_env.array[j];
      }; 
   
      badmood_env.badmoodcount=0;
      badmood_env.array[0]=0;
      mytime=0;
  }

}

void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim2);
 
  count0++;
  if(count0<30){
   
  }

  if((HAL_GPIO_ReadPin(DOWN_BUTTON_PORT,DOWN_BUTTON) == GPIO_PIN_RESET)&&(badmood_env.lcdmode==LCD_mode_0)){
    badmood_env.lcdmode=LCD_mode_1;    
  }

  if((HAL_GPIO_ReadPin(UP_BUTTON_PORT,UP_BUTTON) == GPIO_PIN_RESET)&&(badmood_env.badmoodcount!=0)){
    badmood_env.badmoodcount--;  
  }
  
  if((HAL_GPIO_ReadPin(DOWN_BUTTON_PORT,DOWN_BUTTON) == GPIO_PIN_RESET)&&((badmood_env.lcdmode)==LCD_mode_1)){
    badmood_env.badmoodcount++;
  }

  if((HAL_GPIO_ReadPin(SETTING_BUTTON_PORT,SETTING_BUTTON) == GPIO_PIN_RESET)){
    badmood_env.lcdmode=LCD_mode_2;
  }

  if((HAL_GPIO_ReadPin(RETURN_BUTTON_PORT,RETURN_BUTTON) == GPIO_PIN_RESET)){
         if (badmood_env.lcdmode==LCD_mode_2){
             badmood_env.lcdmode=LCD_mode_1;
         }
        
         else if (badmood_env.lcdmode==LCD_mode_1){
             badmood_env.lcdmode=LCD_mode_0;
         }        
  }
}