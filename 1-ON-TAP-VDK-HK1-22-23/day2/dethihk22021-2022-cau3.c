#include <16f887.h>
#device adc=10
#fuses  intrc_io
#use delay(clock=8Mhz)


#define LCD_ENABLE_PIN  PIN_D0                                    ////
#define LCD_RS_PIN      PIN_D1                                    ////
#define LCD_RW_PIN      PIN_D2                                    ////
#define LCD_DATA4       PIN_D4                                    ////
#define LCD_DATA5       PIN_D5                                    ////
#define LCD_DATA6       PIN_D6                                    ////
#define LCD_DATA7       PIN_D7  
#include <lcd.c>

unsigned int8 nd;


void main()
{
   set_Tris_e(0xff);set_Tris_d(0);set_Tris_a(0xff);
   
   lcd_init();
   setup_Adc(adc_clock_internal);
   setup_adc_ports(SAN5|VREF_VREF);
   set_Adc_channel(5);
   
   while(true)
   {
   
      nd=read_Adc();
      nd=nd/3.1;
      lcd_gotoxy(1,1);
      printf(lcd_putc,"LM35:%02u",nd);
      lcd_putc(223); //lcd_putc(0xdf); 
      lcd_putc('C'); 
   }
}
