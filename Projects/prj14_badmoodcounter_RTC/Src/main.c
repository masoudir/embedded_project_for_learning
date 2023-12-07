
#include "main.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include"retarget.h"
#include "GPIO.h"
#include "UART.h"
#include "Timer.h"
#include "spi.h"
#include "lcd.h"



char buff[16];
char buff2[16];

RTC_HandleTypeDef hrtc;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
RTC_TimeTypeDef gTime;
RTC_DateTypeDef  sDate;

UART_HandleTypeDef huart2;
uint32_t count0=0;
int mytime=0;
int array[7]={0};
LCD_mode lcdmode = LCD_mode_0;

// void welcome_screen(void){
//   printf("welcome message\r\n");
// };

// void home_screen(void){
//   printf("home screen\r\n");
  
// };

// void setting_screen(void){
//   printf("setting manu\r\n");
  
// };

void SystemClock_Config(void);
void MX_RTC_Init(void);




  /*****************************below code is for button test***********************************/
  // if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12) == GPIO_PIN_RESET) {
  //         //count0++;
  //         //if(count0>=2){
  //     HAL_UART_Transmit(&huart2, (const uint8_t*)"olivia", 7, 100);
  //          // LCD_mode==LCD_mode_1;
  //           //count0=0;
  //         }
  //        //}
  // if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11) == GPIO_PIN_RESET) {
  //         HAL_UART_Transmit(&huart2, (const uint8_t*)"hi", 3, 100); 
  //       }
  // if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10) == GPIO_PIN_RESET) {
  //         HAL_UART_Transmit(&huart2, (const uint8_t*)"great", 6, 100);
  //       }
  // if (HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7) == GPIO_PIN_RESET) {
  //         HAL_UART_Transmit(&huart2, (const uint8_t*)"ok", 3, 100);
  //       }        


int main(void)
{
  
  HAL_Init();
  MX_GPIO_Init();
  MX_USART2_UART_Init();
 
  RetargetInit(&huart2);
  printf("print before RTC");
  MX_RTC_Init();
  printf("print after RTC");
  MX_TIM2_Init();
  MX_TIM3_Init();
  spi_init();
  lcd_init();
  
  
  while (1)
  {
    /* USER CODE END WHILE */
      if(lcdmode==LCD_mode_0){
      Paint_Clear(WHITE);
      lcd_welcome_screen();
      welcome_screen_for_UART();






      }
      if(lcdmode==LCD_mode_1){
       Paint_Clear(WHITE);
       lcd_home_screen();
       home_screen_for_UART();
      }
      if(lcdmode==LCD_mode_2){
      Paint_Clear(WHITE);
      lcd_setting_screen();
       setting_screen_for_UART();
      }
    HAL_Delay(1000);
     printf("-----------------------------------------------------------\r\n");
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */

};

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


void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  RTC_TamperTypeDef sTamper = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  printf("P1 ");

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  printf("P2 ");
  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x11;
  sTime.Minutes = 0x11;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  printf("P3 ");
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the RTC Tamper 2
  */
  sTamper.Tamper = RTC_TAMPER_2;
  sTamper.PinSelection = RTC_TAMPERPIN_POS1;
  sTamper.Trigger = RTC_TAMPERTRIGGER_RISINGEDGE;
  sTamper.Filter = RTC_TAMPERFILTER_DISABLE;
  sTamper.SamplingFrequency = RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV32768;
  sTamper.PrechargeDuration = RTC_TAMPERPRECHARGEDURATION_1RTCCLK;
  sTamper.TamperPullUp = RTC_TAMPER_PULLUP_ENABLE;
  sTamper.TimeStampOnTamperDetection = RTC_TIMESTAMPONTAMPERDETECTION_ENABLE;
  if (HAL_RTCEx_SetTamper_IT(&hrtc, &sTamper) != HAL_OK)
  {
    Error_Handler();
  }
  printf("P4 ");
 
}

/**
  * @brief SPI Initialization 
  * @param None
  * @retval None
  */
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
};

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
