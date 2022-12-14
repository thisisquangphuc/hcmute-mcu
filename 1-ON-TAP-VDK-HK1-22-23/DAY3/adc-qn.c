#include <16f887.h>
#device adc=10
#fuses intrc   //intrc_io
#use delay(clock=8Mhz)
//khai bao led 7 seg
const unsigned int8 code7seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; 
//khai bau UART neu co 

//khai bao thu vien LCD
//Neu khai bao cac chan LCD khac cau hinh duoi day thi nho dinh nghia lai
//!#define LCD_ENABLE_PIN  PIN_D0                                    ////
//!#define LCD_RS_PIN      PIN_D1                                    ////
//!#define LCD_RW_PIN      PIN_D2                                    ////
//!#define LCD_DATA4       PIN_D4                                    ////
//!#define LCD_DATA5       PIN_D5                                    ////
//!#define LCD_DATA6       PIN_D6                                    ////
//!#define LCD_DATA7       PIN_D7 
#include <lcd.c>              //cho giao tiep lcd 4 duong data

//khai bao interrupt neu co 
//khai nut nhan
#define LED       pin_b0
#define BT_QN     pin_b1
#define BT_ONOFF  pin_b2

//khai bao bien 

unsigned int8 TT_QN=0;
int1 TT_LED=0;
unsigned int8 temp1=0,temp2=0; // gioi han gia tri nhiet do 0-99
unsigned int8 temp_qn=0;


//chuong trinh con neu con 
void HT_LCD();

void main()
{
   set_tris_a(0xff);
   set_tris_b(0xfe); //1111.1110 set_tris_b(0b11111110); 
   set_tris_c(0);
   set_tris_d(0);
   
   lcd_init();
   setup_adc(adc_clock_internal); //su dung dao dong noi
//!   setup_adc(adc_clock_div_32); // neu su dung dao dong ngoai thach anh       
   setup_adc_ports(SAN1|SAN2|SAN3|VSS_VDD); 
   
   //tat LED don 
   output_low(LED);
   
   while(true)
   {
      if(input(BT_QN==0)) 
      {
         delay_ms(20);
         if(input(BT_QN==0)) 
         {
            TT_QN++;
         }
         if(TT_QN>2) TT_QN=0;
         //cho nha phim 
         while(input(BT_QN==0));
      }
      if(input(BT_ONOFF==0)) 
      {
         delay_ms(20);
         if(input(BT_ONOFF==0)) 
         {
            TT_LED=!TT_LED; //TT_LED=~TT_LED;
         }
         //cho nha phim 
         while(input(BT_QN==0));
      }
      
      //docd nhiet do 
      set_adc_channel(1);
      temp1=read_adc()/2.046;
      set_adc_channel(3);
      temp2=read_adc()/2.046;
      //doc gia tri chiet ap 
      set_adc_channel(2);
      temp_qn = read_adc()/10.3;       //k=(2^n-1)/so cap = 1023/99=10.3
      //hien thi 7 daon 
      if(TT_LED==1)
      {
         //bat 7 seg
         output_c(code7seg[TT_QN%10]);
      }
      else
      {
         //tat led
         output_c(0xff);
      }
      
      HT_LCD();
      
   }
}
void HT_LCD()
{
   if(TT_QN==1)   
   {
      if(temp1>temp_qn) output_high(LED);
      else              output_low(LED);    
   }
   if(TT_QN==2)   
   {
      if(temp2>temp_qn) output_high(LED);
      else              output_low(LED);    
   }
   //hien thi gia tri ra LCD
   lcd_gotoxy(1,1);
   printf(lcd_putc,"T1=%02u",temp1);
   lcd_putc(223);lcd_putc('C');
   lcd_gotoxy(1,8);
   printf(lcd_putc,"T2=%02u",temp2);
   lcd_putc(223);lcd_putc('C');
   
   lcd_gotoxy(2,1);
   printf(lcd_putc,"QN=%02u",temp_qn);
   lcd_putc(223);lcd_putc('C');
}

