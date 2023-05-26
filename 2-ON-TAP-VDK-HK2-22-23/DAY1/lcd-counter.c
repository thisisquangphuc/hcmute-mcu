#include <16f887.h>
#fuses intrc 
#use delay(clock=8M)

#DEFINE  LCD_RS_PIN      PIN_D0
#DEFINE  LCD_RW_PIN      PIN_D1
#DEFINE  LCD_ENABLE_PIN  PIN_D2
#DEFINE  LCD_DATA4     PIN_D4
#DEFINE  LCD_DATA5     PIN_D5
#DEFINE  LCD_DATA6     PIN_D6
#DEFINE  LCD_DATA7     PIN_D7
#include <lcd.c>


#define START pin_b0
#define STOP pin_b1

unsigned int8 product=0;

void main()
{
    set_tris_a(0);
    set_tris_b(0b00000011);
    set_tris_d(0);
    
    lcd_init();
    setup_timer_1(T1_external|T1_DIV_BY_1);
    set_timer1(0);

    lcd_goto_xy(1,1);
    lcd_putc("NHAN START");
    lcd_goto_xy(2,1);
    lcd_putc("DE KHOI DONG");

    //CHO NHAN NUT START
    WHILE(INPUT(START)==1);  

    while(true)
    {
        if(input(STOP)==0)  setup_timer_1(T1_disabled);
        if(input(START)==0)  setup_timer_1(T1_external);

        product=get_timer1();
        if (product == 30)
        {
            setup_timer_1(T1_disabled);
        }

        //hien thi lcd
        lcd_goto_xy(1,1);
        lcd_putc("DEM SAN PHAM");
        lcd_goto_xy(2,1);
        printf(lcd_putc,"SAN PHAN: %02U", product);
    }
}


