#include "image.h"
#include "LCD_Test.h"
#include "LCD_2inch4.h"
#include "DEV_Config.h"

void LCD_2in4_test()
{
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
	//Paint_SetRotate(ROTATE_0);
	//Paint_DrawString_EN (5, 10, "DEMO:",        &Font24,    YELLOW,  RED);

/*******************************LCD_mode_0********************************************/

	Paint_DrawString_EN (5, 34, "Hello", &Font20,WHITE,BLUE);
    Paint_DrawString_EN (5, 64, "Welcome to", &Font20,WHITE,BLUE);
	Paint_DrawString_EN (5, 94, "Badmoodcounter",&Font20,WHITE,BLUE);
	Paint_DrawString_EN (5, 124,"Please press",&Font20,WHITE,BLUE);
	Paint_DrawString_EN (5, 154, "key2 to continue",&Font20,WHITE,BLUE);



/*******************************LCD_mode_1********************************************/

    // Paint_DrawString_EN (5, 10, "Date", &Font20,WHITE,BLUE);
    // Paint_DrawString_EN (5, 40, "Current", &Font20,WHITE,BLUE);
	// Paint_DrawString_EN (5, 60, "Badmoodcount:",&Font20,WHITE,BLUE);
	// Paint_DrawString_EN (190, 60, "99",&Font20,WHITE,BLUE);
    // Paint_DrawString_EN (5, 100,"7-day record",&Font20,WHITE,BLUE);
	// Paint_DrawString_EN (5, 120,"date1:",&Font20,WHITE,BLUE);
	// Paint_DrawString_EN (5, 140,"date2:",&Font20,WHITE,BLUE);
	// Paint_DrawString_EN (5, 160,"date3:",&Font20,WHITE,BLUE);
	// Paint_DrawString_EN (5, 180,"date4:",&Font20,WHITE,BLUE);
	// Paint_DrawString_EN (5, 200,"date5:",&Font20,WHITE,BLUE);
	// Paint_DrawString_EN (5, 220,"date6:",&Font20,WHITE,BLUE);
	// Paint_DrawString_EN (5, 240,"date7:",&Font20,WHITE,BLUE);
    






/*******************************LCD_mode_2********************************************/
  //Paint_DrawString_EN (70, 34, "SETTING", &Font20,WHITE,BLUE);


/********************************below is the test code for lcd *****************************************/

//   Paint_DrawFloatNum  (5, 150 ,987.654321,5,  &Font20,    WHITE,   LIGHTBLUE);
//   Paint_DrawString_EN (5,170, "WaveShare",    &Font24,    WHITE,   BLUE);
//   Paint_DrawString_CN (5,190, "΢ѩ����",     &Font24CN,  WHITE,   RED);
  
// 	Paint_DrawRectangle (125, 240, 225, 300,    RED     ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
// 	Paint_DrawLine      (125, 240, 225, 300,    MAGENTA ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
// 	Paint_DrawLine      (225, 240, 125, 300,    MAGENTA ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
  
// 	Paint_DrawCircle(150,100,  25,        BLUE    ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
// 	Paint_DrawCircle(180,100,  25,        BLACK   ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
// 	Paint_DrawCircle(210,100,  25,        RED     ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
// 	Paint_DrawCircle(165,125,  25,        YELLOW  ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
// 	Paint_DrawCircle(195,125,  25,        GREEN   ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
// 	Paint_DrawString_EN (5, 170, "Good morning",  &Font24,    BLUE,    CYAN);
//   Paint_DrawImage(gImage_1,5,70,60,60);
	
  
	DEV_Delay_ms(3000);
	
	printf("quit...\r\n");
	//DEV_Module_Exit();
  
}

