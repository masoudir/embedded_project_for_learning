#ifndef __LCD__H
#define __LCD__H

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "GUI_Paint.h"
#include "fonts.h"
#include "image.h"
#include "LCD_Test.h"
#include "LCD_2inch4.h"
#include "DEV_Config.h"

void lcd_init(void);
void lcd_welcome_screen(void);
void lcd_home_screen(void);
void lcd_setting_screen(void);
void print_time_UART_lcd (uint8_t hours,uint8_t minutes,uint8_t seconds);
void print_badmoodcount_lcd (int16_t badmoodcount);
//void LCD_clear_line(uint16_t line_number, sFONT* font_size, UWORD Color);
void welcome_screen_for_UART();
void home_screen_for_UART();
void setting_screen_for_UART();



#endif /* __LCD_H */

