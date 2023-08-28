/**
 ******************************************************************************
 * @file           : app_accelerometer.c
 * @brief          : Accelerometer functions body
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

#include "app_accelerometer.h"

extern SPI_HandleTypeDef hspi2;

ACC_SPI_Config_t acc_spi_config = {
  .cs = {
    .port = GPIOB,
    .pin = GPIO_PIN_12
  },
  .mosi = {
    .port = GPIOC,
    .pin = GPIO_PIN_1
  },
  //.miso = {
    //.port = GPIOC,
    //.pin = GPIO_PIN_2
  //},
  .clk = {
    .port = GPIOB,
    .pin = GPIO_PIN_10
  }
};

int acc_output_x = 0;
int acc_output_y = 0;
int acc_output_z = 0;


//void ACC_SPI_ConfigFullDuplexMode()
void ACC_SPI_halfDuplexMode()
{

  ACC_REG_DATA_FORMAT_t data_format = {
      .B = {
          .RANGE = 0,
          .JUSTIFY = 0,
          .FULL_RES = ACC_RES_13bits,
          .RESERVED = 0,
          .INT_INVERT = 0,
          .SPI = 1,
          .SELF_TEST = 0}};

  ACC_SPI_TX_Frame_t tx_frame = {
      .B = {
          .DATA = data_format.R,
          .ADDR = ACC_REG_DATA_FORMAT,
          .MB = ACC_SPI_SINGLE_PACKET,
          .WR = ACC_SPI_WRITE_CMD}};

  ACC_SPI_RX_Frame_t rx_frame = {0};
  ACC_SPI_TransmitReceive(&tx_frame, &rx_frame, 100);
}

uint8_t ACC_SPI_GetDevID()
{
  ACC_SPI_TX_Frame_t tx_frame = {
      .B = {
          .DATA = 0,
          .ADDR = ACC_REG_DEVID,
          .MB = ACC_SPI_SINGLE_PACKET,
          .WR = ACC_SPI_READ_CMD}};

  ACC_SPI_RX_Frame_t rx_frame = {0};

  ACC_SPI_TransmitReceive(&tx_frame, &rx_frame, 100);

  printf("\r\n spi rx=%02X \r\n", rx_frame.B.DATA_L);

  return rx_frame.B.DATA_L;
}

void ACC_SPI_GetAccX0()
{
  ACC_SPI_TX_Frame_t tx_frame = {.B = {
                                     .DATA = 0,
                                     .ADDR = ACC_REG_DATAX0,
                                     .MB = ACC_SPI_SINGLE_PACKET,
                                     .WR = ACC_SPI_READ_CMD}};

  ACC_SPI_RX_Frame_t rx_frame = {0};

  ACC_SPI_TransmitReceive(&tx_frame, &rx_frame, 100);

  printf("\r\n spi x0=%d \r\n", rx_frame.R);
}

void ACC_SPI_GetAccX1()
{
  ACC_SPI_TX_Frame_t tx_frame = {.B = {
                                     .DATA = 0,
                                     .ADDR = ACC_REG_DATAX1,
                                     .MB = ACC_SPI_SINGLE_PACKET,
                                     .WR = ACC_SPI_READ_CMD}};

  ACC_SPI_RX_Frame_t rx_frame = {0};

  ACC_SPI_TransmitReceive(&tx_frame, &rx_frame, 100);

  printf("\r\n spi x1=%d \r\n", rx_frame.R);
}







int ACC_CalculateOutputToIntegerFormat(uint16_t input, uint8_t number_of_bits) {
    uint16_t mask = 1 << (number_of_bits - 1);  // 0b100
    int output = 0;
    
    if((input & mask) != 0) {
        output = input & (~(mask));
        
        output -= (1 << (number_of_bits - 1));
    } else {
        output = input;
    }
    return output;
}



void ACC_SPI_GetAccX() {

  ACC_SPI_TX_Frame_t tx_frame = {.B = {
                                     .DATA = 0,
                                     .ADDR = ACC_REG_DATAX0,
                                     .MB = ACC_SPI_SINGLE_PACKET,
                                     .WR = ACC_SPI_READ_CMD}};

  ACC_SPI_RX_Frame_t data_x0 = {0};
  ACC_SPI_RX_Frame_t data_x1 = {0};

  ACC_SPI_TransmitReceive(&tx_frame, &data_x0, 100);

  tx_frame.B.ADDR = ACC_REG_DATAX1;
  ACC_SPI_TransmitReceive(&tx_frame, &data_x1, 100);

  uint16_t output = ((data_x1.R << 8) | data_x0.R) & 0x1fff;

  int final_output = ACC_CalculateOutputToIntegerFormat(output, 13);

  acc_output_x = final_output;

}

void ACC_SPI_GetAccY() {

  ACC_SPI_TX_Frame_t tx_frame = {.B = {
                                     .DATA = 0,
                                     .ADDR = ACC_REG_DATAY0,
                                     .MB = ACC_SPI_SINGLE_PACKET,
                                     .WR = ACC_SPI_READ_CMD}};

  ACC_SPI_RX_Frame_t data_y0 = {0};
  ACC_SPI_RX_Frame_t data_y1 = {0};

  ACC_SPI_TransmitReceive(&tx_frame, &data_y0, 100);

  tx_frame.B.ADDR = ACC_REG_DATAY1;
  ACC_SPI_TransmitReceive(&tx_frame, &data_y1, 100);

  uint16_t output = ((data_y1.R << 8) | data_y0.R) & 0x1fff;

  int final_output = ACC_CalculateOutputToIntegerFormat(output, 13);

  acc_output_y = final_output;

}

void ACC_SPI_GetAccZ() {

  ACC_SPI_TX_Frame_t tx_frame = {.B = {
                                     .DATA = 0,
                                     .ADDR = ACC_REG_DATAZ0,
                                     .MB = ACC_SPI_SINGLE_PACKET,
                                     .WR = ACC_SPI_READ_CMD}};

  ACC_SPI_RX_Frame_t data_z0 = {0};
  ACC_SPI_RX_Frame_t data_z1 = {0};

  ACC_SPI_TransmitReceive(&tx_frame, &data_z0, 100);

  tx_frame.B.ADDR = ACC_REG_DATAZ1;
  ACC_SPI_TransmitReceive(&tx_frame, &data_z1, 100);

  uint16_t output = ((data_z1.R << 8) | data_z0.R) & 0x1fff;

  int final_output = ACC_CalculateOutputToIntegerFormat(output, 13);

  acc_output_z = final_output;
  

}




void ACC_printData() {
  printf("\r\n ACC x=%d y=%d z=%d \r\n", acc_output_x, acc_output_y, acc_output_z);
}








void ACC_SPI_EnableMeasurement()
{
  ACC_SPI_TX_Frame_t tx_frame = {.B = {
                                     .DATA = 0b00001000,
                                     .ADDR = ACC_REG_POWER_CTL,
                                     .MB = ACC_SPI_SINGLE_PACKET,
                                     .WR = ACC_SPI_WRITE_CMD}};

  ACC_SPI_RX_Frame_t rx_frame = {0};

  ACC_SPI_TransmitReceive(&tx_frame, &rx_frame, 100);
}

void ACC_SPI_PinsConfig() {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_SPI2_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();


    /**SPI2 GPIO Configuration
    PC1     ------> SPI2_MOSI
    PC2     ------> SPI2_MISO
    PB10     ------> SPI2_SCK
    PB12     ------> SPI2_NSS
    */
    //GPIO_InitStruct.Pin = acc_spi_config.mosi.pin;
    //GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    //GPIO_InitStruct.Pull = GPIO_NOPULL;
    //GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    //GPIO_InitStruct.Alternate = GPIO_AF7_SPI2;
    //HAL_GPIO_Init(acc_spi_config.mosi.port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = acc_spi_config.miso.pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(acc_spi_config.miso.port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = acc_spi_config.clk.pin;//GPIO_PIN_10|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(acc_spi_config.clk.port, &GPIO_InitStruct);
}


void ACC_Init()
{

  GPIO_InitTypeDef gpio_cs = {
      .Pin = acc_spi_config.cs.pin,
      .Mode = GPIO_MODE_OUTPUT_PP,
      .Pull = GPIO_NOPULL,
      .Speed = GPIO_SPEED_FREQ_HIGH,
      .Alternate = 0};

  HAL_GPIO_Init(acc_spi_config.cs.port, &gpio_cs);

  hspi2 = (SPI_HandleTypeDef) {
    .Instance = SPI2,
    .Init = {
      .Mode = SPI_MODE_MASTER,
      .Direction = SPI_DIRECTION_1LINES,
      .DataSize = SPI_DATASIZE_16BIT,
      .CLKPolarity = SPI_POLARITY_HIGH,
      .CLKPhase = SPI_PHASE_2EDGE,
      .NSS = SPI_NSS_HARD_OUTPUT,
      .BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128,
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

  ACC_SPI_ConfigFullDuplexMode();

  if(ACC_SPI_GetDevID() == ACC_ADXL345_DEV_ID) {
      ACC_SPI_EnableMeasurement();
  }

  
}


HAL_StatusTypeDef ACC_SPI_TransmitReceive(ACC_SPI_TX_Frame_t *pTxData, ACC_SPI_RX_Frame_t *pRxData, uint32_t Timeout)
{
  HAL_StatusTypeDef status;
  HAL_GPIO_WritePin(acc_spi_config.cs.port, acc_spi_config.cs.pin, GPIO_PIN_RESET);
  status = HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)pTxData, (uint8_t *)pRxData, 2, Timeout);
  HAL_GPIO_WritePin(acc_spi_config.cs.port, acc_spi_config.cs.pin, GPIO_PIN_SET);
  return status;
}

void ACC_task1() {
    ACC_SPI_GetAccX();
    ACC_SPI_GetAccY();
    ACC_SPI_GetAccZ();
    ACC_printData();
}