/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "GUI_Paint.h"
#include "fonts.h"
#include "image.h"
#include "LCD_Test.h"

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

SPI_HandleTypeDef hspi2;



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
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
#endif



void init_uart() {
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
}




void Setup() {
 /* MCU Configuration--------------------------------------------------------*/

    /* MCU Configuration--------------------------------------------------------*/
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();


    /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  __HAL_RCC_SPI2_CLK_ENABLE();


  init_uart();


  /* To enable printf() support for UART2 */
  RetargetInit(&huart2);


  printf("\r\n =============== \r\n Initiating tasks ... \r\n");


  // Init GPIO

  {
    GPIO_InitTypeDef gpio_config = {
      .Pin = GPIO_PIN_5,
      .Mode = GPIO_MODE_OUTPUT_PP,
      .Pull = GPIO_NOPULL,
      .Speed = GPIO_SPEED_FREQ_LOW,
      .Alternate = 0
    };

    HAL_GPIO_Init(GPIOA, &gpio_config);
  }

  {
    GPIO_InitTypeDef gpio_config = {
          .Pin = GPIO_PIN_13,
          .Mode = GPIO_MODE_INPUT,
          .Pull = GPIO_NOPULL,
          .Speed = GPIO_SPEED_FREQ_LOW,
          .Alternate = 0
    };

    HAL_GPIO_Init(GPIOC, &gpio_config);
  }

  {
    GPIO_InitTypeDef gpio_config = {
      .Pin = DC_Pin|RST_Pin,
      .Mode = GPIO_MODE_OUTPUT_PP,
      .Pull = GPIO_NOPULL,
      .Speed = GPIO_SPEED_FREQ_LOW,
      .Alternate = 0
    };

    HAL_GPIO_Init(GPIOA, &gpio_config);
  }

  {
    GPIO_InitTypeDef gpio_config = {
      .Pin = CS_Pin,
      .Mode = GPIO_MODE_OUTPUT_PP,
      .Pull = GPIO_NOPULL,
      .Speed = GPIO_SPEED_FREQ_LOW,
      .Alternate = 0
    };

    HAL_GPIO_Init(CS_GPIO_Port, &gpio_config);
  }


    /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, DC_Pin|RST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);

  {
    GPIO_InitTypeDef gpio_config = {
      .Pin = SPI2_MOSI_PIN,
      .Mode = GPIO_MODE_AF_PP,
      .Pull = GPIO_NOPULL,
      .Speed = GPIO_SPEED_FREQ_VERY_HIGH,
      .Alternate = GPIO_AF7_SPI2
    };

    HAL_GPIO_Init(SPI2_MOSI_PORT, &gpio_config);
  }

  {
    GPIO_InitTypeDef gpio_config = {
      .Pin = SPI2_MISO_PIN,
      .Mode = GPIO_MODE_AF_PP,
      .Pull = GPIO_NOPULL,
      .Speed = GPIO_SPEED_FREQ_VERY_HIGH,
      .Alternate = GPIO_AF5_SPI2
    };

    HAL_GPIO_Init(SPI2_MISO_PORT, &gpio_config);
  }  

  {
    GPIO_InitTypeDef gpio_config = {
      .Pin = SPI2_CLK_PIN,
      .Mode = GPIO_MODE_AF_PP,
      .Pull = GPIO_NOPULL,
      .Speed = GPIO_SPEED_FREQ_VERY_HIGH,
      .Alternate = GPIO_AF5_SPI2
    };

    HAL_GPIO_Init(SPI2_CLK_PORT, &gpio_config);
  }    

  hspi2 = (SPI_HandleTypeDef) {
    .Instance = SPI2,
    .Init = {
      .Mode = SPI_MODE_MASTER,
      .Direction = SPI_DIRECTION_2LINES,
      .DataSize = SPI_DATASIZE_8BIT,
      .CLKPolarity = SPI_POLARITY_LOW,
      .CLKPhase = SPI_PHASE_1EDGE,
      .NSS = SPI_NSS_SOFT,
      .BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4,
      .FirstBit = SPI_FIRSTBIT_MSB,
      .TIMode = SPI_TIMODE_DISABLE,
      .CRCCalculation = SPI_CRCCALCULATION_DISABLE,
      .CRCPolynomial = 10
    }
  };

  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }

  LCD_2in4_test();

}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  Setup();
  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  while (1)
  {
    //StartTask02();
  }
 
}


