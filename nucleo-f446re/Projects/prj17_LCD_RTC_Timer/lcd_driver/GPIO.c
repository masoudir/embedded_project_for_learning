
#include "GPIO.h"

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void MX_GPIO_LCD_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  

  // PUSH BUTTON PIN
  GPIO_InitStruct.Pin = PUSH_BUTTON_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(PUSH_BUTTON_GPIO_Port, &GPIO_InitStruct);

  //led_Pin 
  GPIO_InitStruct.Pin = LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);



// up button
  GPIO_InitStruct.Pin = UP_BUTTON;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(UP_BUTTON_PORT, &GPIO_InitStruct);

//down button
  GPIO_InitStruct.Pin = DOWN_BUTTON;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DOWN_BUTTON_PORT, &GPIO_InitStruct);

//setting
  GPIO_InitStruct.Pin = SETTING_BUTTON;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SETTING_BUTTON_PORT, &GPIO_InitStruct);

//return 
  GPIO_InitStruct.Pin = RETURN_BUTTON;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RETURN_BUTTON_PORT, &GPIO_InitStruct);

 // Init LCD GPIO

  {
    GPIO_InitTypeDef gpio_config = {
      .Pin = LED_PIN,
      .Mode = GPIO_MODE_OUTPUT_PP,
      .Pull = GPIO_NOPULL,
      .Speed = GPIO_SPEED_FREQ_LOW,
      .Alternate = 0
    };

    HAL_GPIO_Init(LED_GPIO_Port, &gpio_config);
  }

//PC13

  {
    GPIO_InitTypeDef gpio_config = {
          .Pin = PUSH_BUTTON_PIN,
          .Mode = GPIO_MODE_INPUT,
          .Pull = GPIO_NOPULL,
          .Speed = GPIO_SPEED_FREQ_LOW,
          .Alternate = 0
    };

    HAL_GPIO_Init(PUSH_BUTTON_GPIO_Port, &gpio_config);
  }


//PA8
  {
    GPIO_InitTypeDef gpio_config = {
      .Pin = DC_PIN,
      .Mode = GPIO_MODE_OUTPUT_PP,
      .Pull = GPIO_NOPULL,
      .Speed = GPIO_SPEED_FREQ_LOW,
      .Alternate = 0
    };

    HAL_GPIO_Init(DC_GPIO_Port, &gpio_config);
  }
//PA9
  {
    GPIO_InitTypeDef gpio_config = {
      .Pin = RST_PIN,
      .Mode = GPIO_MODE_OUTPUT_PP,
      .Pull = GPIO_NOPULL,
      .Speed = GPIO_SPEED_FREQ_LOW,
      .Alternate = 0
    };

    HAL_GPIO_Init(RST_GPIO_Port, &gpio_config);
  }
//PB6
  {
    GPIO_InitTypeDef gpio_config = {
      .Pin = CS_PIN,
      .Mode = GPIO_MODE_OUTPUT_PP,
      .Pull = GPIO_NOPULL,
      .Speed = GPIO_SPEED_FREQ_LOW,
      .Alternate = 0
    };

    HAL_GPIO_Init(CS_GPIO_Port, &gpio_config);
  }






    /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(DC_GPIO_Port, DC_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(RST_GPIO_Port, RST_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(CS_GPIO_Port, CS_PIN, GPIO_PIN_SET);
  //HAL_GPIO_WritePin(SPI2_MOSI_PORT, SPI2_MOSI_PIN, GPIO_PIN_RESET);
  //HAL_GPIO_WritePin(SPI2_CLK_PORT, SPI2_CLK_PIN, GPIO_PIN_RESET);
     /*Configure GPIO pin Input Level */
  // HAL_GPIO_ReadPin(PUSH_BUTTON_GPIO_Port,PUSH_BUTTON_PIN);
  // HAL_GPIO_ReadPin(SPI2_MISO_PORT,SPI2_MISO_PIN);
  // HAL_GPIO_ReadPin(UP_BUTTON_PORT,UP_BUTTON);
  // HAL_GPIO_ReadPin(DOWN_BUTTON_PORT,DOWN_BUTTON);
  // HAL_GPIO_ReadPin(SETTING_BUTTON_PORT,SETTING_BUTTON);
  // HAL_GPIO_ReadPin(RETURN_BUTTON_PORT,RETURN_BUTTON);
    
  };


/*
Pin     Description         Type
PA5     LED PIN             output
PC13    PUSH BUTTION PIN    input 
----------lcd--------------------
PA8     DC PIN(data/command)output
PA9     RST                 output
PB6     CS                  output
PC1     MOSI                output
PC2     MISO                input
PB10    CLK                 output  

------------4 buttons------------------
PA12    up button           input
PA11    down button         input
PA10    setting button      input
PC7     return button       input
*/
