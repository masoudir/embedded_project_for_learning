#include "hw_drivers.h"



void init_system_basic_clock() {
    
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  
  /* Configure the system clock */
//  SystemClock_Config();


    /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

void init_gpio_input(GPIO_TypeDef* port, uint32_t pin, uint32_t it_mode) {

    GPIO_InitTypeDef gpio = {
        .Pin = pin,
        .Mode = it_mode,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_LOW,
        .Alternate = 0
    };

    HAL_GPIO_Init(port, &gpio);
}

void init_gpio_output(GPIO_TypeDef* port, uint32_t pin) {

     GPIO_InitTypeDef gpio = {
        .Pin = pin,
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_LOW,
        .Alternate = 0
    };

    HAL_GPIO_Init(port, &gpio);
}

// void init_total_system() {
    
//   /* MCU Configuration--------------------------------------------------------*/
//   init_system_basic_clock();

//   /* Initialize all configured peripherals */
  
//   /*Configure GPIO pin Output Level */
//   HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

//   init_gpio_input(B1_GPIO_Port, B1_Pin, GPIO_MODE_IT_FALLING);
//   init_gpio_output(LD2_GPIO_Port, LD2_Pin);

//   init_uart(&huart2, USART2, 115200);
// }


void init_uart(UART_HandleTypeDef* huart, USART_TypeDef* usart, uint32_t baudrate) {

  huart->Instance = usart;
  huart->Init.BaudRate = baudrate;
  huart->Init.WordLength = UART_WORDLENGTH_8B;
  huart->Init.StopBits = UART_STOPBITS_1;
  huart->Init.Parity = UART_PARITY_NONE;
  huart->Init.Mode = UART_MODE_TX_RX;
  huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart->Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(huart) != HAL_OK)
  {
    Error_Handler();
  }

}



