#include <16f887.h>
#fuses  intrc_io  // khai bao nay de su dung 2 chan A6,A7 thanh IO 
#use delay(clock=8Mhz)

const unsigned int8 code7seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; 

#define ADJ pin_e0

unsigned int8 level=0;
unsigned int16 speed=0;

void main()
{
   
   
   set_tris_a(0xff);
   set_Tris_c(0);
   set_Tris_d(0);
   
   setup_timer_2(T2_div_by_16,249,1);
   set_timer2(0);
   
   setup_ccp1(ccp_pwm);
   set_pwm1_duty((unsigned int16)0);
 
   while(true)
   {
      if(input(ADJ)==0)
      {
         delay_ms(50);
//!         if(input(pin(ADJ)==0)
//!         {
//!            //cong viec
//!            while(input(pin(ADJ)==0);
//!         }
         level++;
         if(level>9) level=0;
         while(input(ADJ)==0);
      }
      
      speed=level*100;
      set_pwm1_duty(speed);
      output_d(code7seg[level%10]);
   }
   
}
