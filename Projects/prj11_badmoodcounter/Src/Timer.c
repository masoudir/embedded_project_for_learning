#include "timer.h"

TIM_HandleTypeDef htim2;//0.1s
TIM_HandleTypeDef htim3;//1s


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
    htim2.Init.Prescaler   = 1000;
    
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
    htim2.Init.Period = 1600;
        
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
{ static uint8_t hours = 0, minutes = 0, seconds = 0;
 
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

      
        printf("time=%02d:%02d:%02d\r\n", hours, minutes, seconds);
        
  mytime++;
  array[0]=badmoodcount;
  if(mytime==10){ 
      for (int j = 5; j >= 0; j--) {
        array[j+1] = array[j];
      }; 
      badmoodcount=0;
      array[0]=0;
      mytime=0;
  }
  // Display the latest 7 interval numbers
        printf("Latest 7 numbers: ");
        for (int j = 0; j < 7; j++) {
            printf("%d ", array[j]);
        }
        printf("\r\n");
      printf("----------------------------\r\n");
}

void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim2);
  //HAL_UART_Transmit(&huart2, (const uint8_t*)"tick2", 5, 100);
  count0++;
  if(count0<30){
    lcdmode=LCD_mode_0;
  }

  if((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11) == GPIO_PIN_RESET)&&(lcdmode==LCD_mode_0)){
    lcdmode=LCD_mode_1;
    //HAL_UART_Transmit(&huart2, (const uint8_t*) lcdmode, 5, 100);
    //printf("lcdmode=%d\n", lcdmode);
     
  }

  if((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12) == GPIO_PIN_RESET)&&(badmoodcount!=0)){
    badmoodcount--;
    //HAL_UART_Transmit(&huart2, (const uint8_t*) badmoodcount, 5, 100); 
    //printf("badmood=%d\n", badmoodcount);
  }
  
  if((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11) == GPIO_PIN_RESET)&&(lcdmode==LCD_mode_1)){
    badmoodcount++;
    //HAL_UART_Transmit(&huart2, (const uint8_t*) badmoodcount, 5, 100); 
    //printf("badmood=%d\n", badmoodcount);
  }

  if((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10) == GPIO_PIN_RESET)){
    lcdmode=LCD_mode_2;
    //HAL_UART_Transmit(&huart2, (const uint8_t*) lcdmode, 5, 100); 
    //printf("lcdmode=%d\n", lcdmode);
  }

  if((HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7) == GPIO_PIN_RESET)){
         if (lcdmode==LCD_mode_2){
             lcdmode=LCD_mode_1;
         }
        
         if (lcdmode==LCD_mode_1){
             lcdmode=LCD_mode_0;
         }

          //printf("lcdmode=%d\n", lcdmode);
  }
