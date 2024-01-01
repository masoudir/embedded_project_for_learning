#ifndef __TIMER__H
#define __TIMER__H

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"



void MX_TIM2_Init(void);
void MX_TIM3_Init(void);

void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);

#endif /* __TIMER__H */

