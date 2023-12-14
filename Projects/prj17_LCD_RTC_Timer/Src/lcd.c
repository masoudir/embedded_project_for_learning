#include "lcd.h"
#include"main.h"
extern int16_t badmoodcount;
extern uint32_t count0;
extern int mytime;
extern int array[7];
extern uint8_t hours;
extern uint8_t minutes;
extern uint8_t seconds;
extern char buff[16];
extern char buff2[16];


void lcd_init(){
    printf("LCD_2IN4_test Demo\r\n");
    DEV_Module_Init();
    
    printf("LCD_2IN4_ Init and Clear...\r\n");
    LCD_2IN4_Init();
    LCD_2IN4_Clear(WHITE);
    
    printf("Paint_NewImage\r\n");
    Paint_NewImage(LCD_2IN4_WIDTH,LCD_2IN4_HEIGHT, ROTATE_0, WHITE);
    
    printf("Set Clear and Display Funtion\r\n");
    Paint_SetClearFuntion(LCD_2IN4_Clear);
    Paint_SetDisplayFuntion(LCD_2IN4_DrawPaint);
    
    printf("Paint_Clear\r\n");
    Paint_Clear(WHITE);
    DEV_Delay_ms(1000);
    
    printf("Painting...\r\n");
}

void lcd_test(){
    DEV_Delay_ms(50);
    Paint_DrawString_EN (5, 34, "Hello", &Font20,WHITE,BLUE);
    Paint_DrawString_EN (5, 64, "Welcome to", &Font20,WHITE,BLUE);
    Paint_DrawString_EN (5, 94, "Badmoodcounter",&Font20,WHITE,BLUE);
    Paint_DrawString_EN (5, 124,"Please press",&Font20,WHITE,BLUE);
    Paint_DrawString_EN (5, 154, "key2 to continue",&Font20,WHITE,BLUE);
    DEV_Delay_ms(1000);
   
    //DEV_Delay_ms(500);
}