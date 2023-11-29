#include "lcd.h"
#include "Timer.h"
extern int16_t badmoodcount;
extern uint32_t count0;
extern int mytime;
extern int array[7];
extern LCD_mode lcdmode;
extern uint8_t hours;
extern uint8_t minutes;
extern uint8_t seconds;



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
/*******************************welcome_screen********************************************/
void lcd_welcome_screen(){
    DEV_Delay_ms(50);
    Paint_DrawString_EN (5, 34, "Hello", &Font20,WHITE,BLUE);
    Paint_DrawString_EN (5, 64, "Welcome to", &Font20,WHITE,BLUE);
    Paint_DrawString_EN (5, 94, "Badmoodcounter",&Font20,WHITE,BLUE);
    Paint_DrawString_EN (5, 124,"Please press",&Font20,WHITE,BLUE);
    Paint_DrawString_EN (5, 154, "key2 to continue",&Font20,WHITE,BLUE);
    DEV_Delay_ms(1000);
   
    //DEV_Delay_ms(500);
}
/*******************************home_screen********************************************/
void lcd_home_screen(){
    
    // time_t current_time;
    // time(&current_time);
    // // Using a buffer for thread safety
    // char time_buffer[26];
    // ctime_r(&current_time, time_buffer);
    // // extracting year,month,date from the time_buffer
    // int year, month, day;

    // sscanf(time_buffer,"%*s %*s %d %*d %d %d", &month, &day,&year);
    // char buffer_date[50]={0};
    // sprintf(buffer_date,"Date:%d,%02d,%02d\r\n", year, month, day);
    // printf("buffer_date:%s\r\n", buffer_date);
    // Paint_DrawString_EN (5, 10,buffer_date, &Font20,WHITE,BLUE);
    
    time_t current_time;
    time(&current_time);
    
    // Using a buffer for thread safety
    char time_buffer[26];
    ctime_r(&current_time, time_buffer);
       Paint_DrawString_EN (5, 10,time_buffer, &Font20,WHITE,BLUE);

       print_badmoodcount_lcd (badmoodcount);
    
    
    // // extracting year, month, date from the time_buffer
    // int year, month, day;

    // // Corrected sscanf format string to properly extract date information
    // sscanf(time_buffer, "%*s %*s %d %*d %d %d", &month, &day, &year);

    // char buffer_date[50] = {0};
    
    // // Corrected sprintf format string to properly format the date
    // sprintf(buffer_date, "Date: %d,%02d,%02d\r\n", year, month, day);
    
    // // Printing the formatted date
    // printf("%s", buffer_date);
    
    // // Simulating Paint_DrawString_EN function
    // // This function should display the formatted date
    // // Here, it's replaced with a print statement for demonstration purposes
    // printf("Display: %s", buffer_date);
    // Paint_DrawString_EN (5, 10,buffer_date, &Font20,WHITE,BLUE);

    // //DEV_Delay_ms(50);
    // //Paint_DrawString_EN (5, 10, "Date", &Font20,WHITE,BLUE);
    // //Paint_DrawString_EN (20, 10, time_buffer, &Font20,WHITE,BLUE);

    Paint_DrawString_EN (5, 40, "Current", &Font20,WHITE,BLUE);
    //Paint_DrawString_EN (190, 60, "99",&Font20,WHITE,BLUE);
    //Paint_DrawString_EN (5, 100,"7-day record",&Font20,WHITE,BLUE);
    // Paint_DrawString_EN (5, 120,"date1:",&Font20,WHITE,BLUE);
    // Paint_DrawString_EN (5, 140,"date2:",&Font20,WHITE,BLUE);
    // Paint_DrawString_EN (5, 160,"date3:",&Font20,WHITE,BLUE);
    // Paint_DrawString_EN (5, 180,"date4:",&Font20,WHITE,BLUE);
    // Paint_DrawString_EN (5, 200,"date5:",&Font20,WHITE,BLUE);
    // Paint_DrawString_EN (5, 220,"date6:",&Font20,WHITE,BLUE);
    // Paint_DrawString_EN (5, 240,"date7:",&Font20,WHITE,BLUE);
    DEV_Delay_ms(50000);
  
}

/*******************************setting_screen********************************************/

void lcd_setting_screen(){
     //Paint_Clear(WHITE);
     DEV_Delay_ms(50);
     Paint_DrawString_EN (70, 34, "SETTING", &Font20,WHITE,BLUE);
     DEV_Delay_ms(50000);
    
}


void print_time_UART_lcd (uint8_t hours,uint8_t minutes,uint8_t seconds){
    char buffer[50]={0};
    sprintf(buffer,"time=%02d:%02d:%02d\r\n", hours, minutes, seconds);
    printf("%s", buffer);
    Paint_DrawString_EN (5, 10,buffer, &Font20,WHITE,BLUE);
}

void print_badmoodcount_lcd (int16_t badmoodcount){
    char badmoodcount_buffer[20]={0};
    //LCD_clear_line(60, WHITE);
    sprintf(badmoodcount_buffer,"%d", badmoodcount);
    printf("Badmoodcount:%s", badmoodcount_buffer);
    Paint_DrawString_EN (0, 60,badmoodcount_buffer, &Font20,WHITE,BLUE);
}

void LCD_clear_line(uint16_t line_number, sFONT* font_size, UWORD Color)

{
    UWORD i,j;
    LCD_2IN4_SetWindow(0, line_number, 0 + LCD_2IN4_WIDTH, line_number + font_size->Height);
	DEV_Digital_Write(DEV_DC_PIN, 1);
	for(i = 0; i < LCD_2IN4_WIDTH; i++){
		for(j = 0; j < font_size->Height; j++){
			LCD_2IN4_WriteData_Word(Color);
		}
	 }
}

/***************************************************************************/
void welcome_screen_for_UART(){
    if(lcdmode==LCD_mode_0){
        printf("hi, welcome to badmoodcounter, please press key2 to continue\r\n");
    } 
}

void home_screen_for_UART() {
    if(lcdmode==LCD_mode_1) {
        printf(" home screen current time \r\n");
        printf("Badmoodcounter now:%d \r\n", badmoodcount);
        printf("time=%02d:%02d:%02d\r\n", hours, minutes, seconds);
        for(int i=0; i<7;i++) {
          printf("The %d of 7days record %d\r\n", i, array[i]);
        }
       
    } 
}


void setting_screen_for_UART(){

   if(lcdmode==LCD_mode_2){
        printf("This is setting screen\r\n");
    } 
}


