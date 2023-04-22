/**
  ******************************************************************************
  * @file           : hw_drivers.h
  * @brief          : Header for hw_drivers.c file.
  *                   
  ******************************************************************************
  * @attention
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_DRIVERS_H
#define __HW_DRIVERS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "app_general.h"

void init_system_basic_clock();

void init_gpio_input(GPIO_TypeDef* port, uint32_t pin, uint32_t it_mode);

void init_gpio_output(GPIO_TypeDef* port, uint32_t pin);

void init_uart(UART_HandleTypeDef* huart, USART_TypeDef* usart, uint32_t baudrate);


#ifdef __cplusplus
}
#endif

#endif /* __HW_DRIVERS_H */