
#include "main.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include"retarget.h"
I2C_HandleTypeDef hi2c1;
TIM_HandleTypeDef htim2;//0.1s
TIM_HandleTypeDef htim3;//1s
UART_HandleTypeDef huart2;
uint32_t count0=0;
int16_t badmoodcount=0;

LCD_mode lcdmode = LCD_mode_0;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM2_Init(void);

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
    printf("lcdmode=%d\n", lcdmode);
     
  }

  if((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12) == GPIO_PIN_RESET)&&(badmoodcount!=0)){
    badmoodcount--;
    //HAL_UART_Transmit(&huart2, (const uint8_t*) badmoodcount, 5, 100); 
    printf("badmood=%d\n", badmoodcount);
  }
  
  if((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11) == GPIO_PIN_RESET)&&(lcdmode==LCD_mode_1)){
    badmoodcount++;
    //HAL_UART_Transmit(&huart2, (const uint8_t*) badmoodcount, 5, 100); 
      printf("badmood=%d\n", badmoodcount);
  }

  if((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10) == GPIO_PIN_RESET)){
    lcdmode=LCD_mode_2;
    //HAL_UART_Transmit(&huart2, (const uint8_t*) lcdmode, 5, 100); 
     printf("lcdmode=%d\n", lcdmode);
  }

  if((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9) == GPIO_PIN_RESET)){
         if (lcdmode==LCD_mode_2){
             lcdmode=LCD_mode_1;
         }
        
         if (lcdmode==LCD_mode_1){
             lcdmode=LCD_mode_0;
         }

          printf("lcdmode=%d\n", lcdmode);
  }










  /*****************************below code is for button test***********************************/
  if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12) == GPIO_PIN_RESET) {
          //count0++;
          //if(count0>=2){
      HAL_UART_Transmit(&huart2, (const uint8_t*)"olivia", 7, 100);
           // LCD_mode==LCD_mode_1;
            //count0=0;
          }
         //}
  if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11) == GPIO_PIN_RESET) {
          HAL_UART_Transmit(&huart2, (const uint8_t*)"hi", 3, 100); 
        }
  if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10) == GPIO_PIN_RESET) {
          HAL_UART_Transmit(&huart2, (const uint8_t*)"great", 6, 100);
        }
  if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9) == GPIO_PIN_RESET) {
          HAL_UART_Transmit(&huart2, (const uint8_t*)"ok", 3, 100);
        }        
}

void TIM3_IRQHandler(void)
{ static uint8_t hours = 0, minutes = 0, seconds = 0;
  HAL_TIM_IRQHandler(&htim3);// timer 1s
        system("clear"); 
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

      char time_str[20];
        snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d\n", hours, minutes, seconds);
        HAL_UART_Transmit(&huart2, (uint8_t*)time_str, sizeof(time_str), 100);
      printf("\n");


}


static void MX_TIM3_Init(void)
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

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  HAL_Init();

  MX_GPIO_Init();
 
  MX_USART2_UART_Init();
  RetargetInit(&huart2);
  MX_TIM2_Init();
  MX_TIM3_Init();
  
  HAL_UART_Transmit(&huart2, (const uint8_t*)"hi", 2, 100);
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}


/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
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

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  // /*Configure GPIO pin : PB12 */
  // GPIO_InitStruct.Pin = GPIO_PIN_12;
  // GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  // GPIO_InitStruct.Pull = GPIO_NOPULL;
  // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  //HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


  GPIO_InitStruct.Pin = GPIO_PIN_12;// up button
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


  GPIO_InitStruct.Pin = GPIO_PIN_11;//down button
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


  GPIO_InitStruct.Pin = GPIO_PIN_10;//setting
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


  GPIO_InitStruct.Pin = GPIO_PIN_9;//return 
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);




/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
