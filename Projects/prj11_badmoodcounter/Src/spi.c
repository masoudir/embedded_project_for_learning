
#include "spi.h"
#include "main.h"
SPI_HandleTypeDef hspi2;
/* Private variables ---------------------------------------------------------*/
void spi_init(void){
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



}