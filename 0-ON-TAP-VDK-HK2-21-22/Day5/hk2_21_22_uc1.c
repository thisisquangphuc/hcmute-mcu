#include <16f887.h>
#device adc=10
#fuses  intrc_io  // khai bao nay de su dung 2 chan A6,A7 thanh IO 
#use delay(clock=8Mhz)
#use rs232(BAUD=9600,BITS=8,STOP=1,PARITY=N,RCV=PIN_C7,XMIT=PIN_C6) 

const unsigned int8 code7seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; 

#define LED_MODE  pin_e1
#define RUN       pin_b0
#define STOP1     pin_b1

#define LCD_ENABLE_PIN  PIN_D0                                    ////
#define LCD_RS_PIN      PIN_D2                                    ////
#define LCD_RW_PIN      PIN_D1                                    ////
#define LCD_DATA4       PIN_D4                                    ////
#define LCD_DATA5       PIN_D5                                    ////
#define LCD_DATA6       PIN_D6                                    ////
#define LCD_DATA7       PIN_D7 
#include <lcd.c>   //#include <tv_lcd.c>

unsigned int8 SPEED=0;
int1 MODE=0;  //0,1
unsigned int16 POT=0;
unsigned char rx_data=0;

#int_rda
void ngat_nhan()
{
   rx_data = getc();
   if(rx_data == 'S') 
   {
      output_low(LED_MODE);
   }
}

void main()
{
   set_tris_a(0x00);
   set_tris_b(0xff);
   set_tris_c(0x80);
   set_tris_e(0x00);
   
   setup_adc(adc_clock_internal);
   setup_adc_ports(SAN5|VSS_VDD);
   
   enable_interrupts(global);
   enable_interrupts(int_rda);
   lcd_init();
   MODE=0;
   
   while(true)
   {
      if(input(RUN)==0) 
      {
         MODE = 1;
         output_high(LED_MODE);
         putc('R');      
      }
      else if(input(STOP1)==0) 
      {
         MODE = 0;
         output_low(LED_MODE);
         putc('S');
      }
      
      set_adc_Channel(5);
      delay_ms(2);
      POT = read_adc();
      
      //lcd_gotoxy(1,1);
      //lcd_putc(rx_data+48);
      POT = read_adc();
      SPEED = POT/102.3;
      //printf(lcd_putc,"%04Lu   %02u",POT, SPEED);
      
      //putc(POT);
      if(SPEED == 10) 
      {
         output_a(0x8E);  // chu F
         putc('F');
      }
      else 
      {
         output_a(code7seg[SPEED%10]);
         putc(SPEED);
      }
      
   }
}


