
#include "spi.h"
#include "main.h"
#include "GPIO.h"
SPI_HandleTypeDef hspi2;
/* Private variables ---------------------------------------------------------*/
void spi_init(void){

  __HAL_RCC_SPI2_CLK_ENABLE();

hspi2 = (SPI_HandleTypeDef) {
    .Instance = SPI2,
    .Init = {
      .Mode = SPI_MODE_MASTER,
      .Direction = SPI_DIRECTION_2LINES,
      .DataSize = SPI_DATASIZE_8BIT,
      .CLKPolarity = SPI_POLARITY_LOW,
      .CLKPhase = SPI_PHASE_1EDGE,
      .NSS = SPI_NSS_SOFT,
      //.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4,
      .BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2,
      .FirstBit = SPI_FIRSTBIT_MSB,
      .TIMode = SPI_TIMODE_DISABLE,
      .CRCCalculation = SPI_CRCCALCULATION_DISABLE,
      .CRCPolynomial = 10
    }
  };


//PC1
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

//PC2
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

  //PB10

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

  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }



}