#ifndef __GPIO__H
#define __GPIO__H

#include <stdio.h>
#include "stm32f4xx_hal.h"

/************for uart pin********************************/
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA


/********************for led and push button pins*************************************/
#define LED_PIN GPIO_PIN_5
#define LED_GPIO_Port GPIOA

#define PUSH_BUTTON_PIN GPIO_PIN_13
#define PUSH_BUTTON_GPIO_Port GPIOC

/********************for LCD related pins*********************************************/
#define DC_PIN GPIO_PIN_8
#define DC_GPIO_Port GPIOA

#define RST_PIN GPIO_PIN_9
#define RST_GPIO_Port GPIOA

#define CS_PIN GPIO_PIN_6
#define CS_GPIO_Port GPIOB

#define SPI2_MOSI_PIN GPIO_PIN_1
#define SPI2_MOSI_PORT GPIOC

#define SPI2_MISO_PIN GPIO_PIN_2
#define SPI2_MISO_PORT GPIOC

#define SPI2_CLK_PIN GPIO_PIN_10
#define SPI2_CLK_PORT GPIOB

/***********************for 4 button pins********************************************/

#define UP_BUTTON GPIO_PIN_12
#define UP_BUTTON_PORT GPIOA

#define DOWN_BUTTON GPIO_PIN_11
#define DOWN_BUTTON_PORT GPIOA

#define SETTING_BUTTON GPIO_PIN_10
#define SETTING_BUTTON_PORT GPIOA

#define RETURN_BUTTON GPIO_PIN_7
#define RETURN_BUTTON_PORT GPIOC

/*
Pin     Description         Type
PA5     LED PIN             output
PC13    PUSH BUTTION PIN    input 
PA8     DC PIN(data/command)output
PA9     RST                 output
PB6     CS                  output
PC1     MOSI                output
PC2     MISO                input
PB10    CLK                 output  
PA12    up button           input
PA11    down button         input
PA10    setting button      input
PC7     return button       input
*/


#endif /* __GPIO_H */

