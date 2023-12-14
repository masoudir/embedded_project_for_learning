#ifndef __LCD__H
#define __LCD__H

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "fonts.h"
#include "image.h"
#include "LCD_2inch4.h"


void lcd_init(void);

void lcd_test();

#endif /* __LCD_H */

