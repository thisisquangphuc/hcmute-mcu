#include <16f887.h>
#fuses intrc   //intrc_io
#use delay(clock=8Mhz)
//khai bao led 7 seg
const unsigned int8 code7seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; 
//khai bau UART neu co 

unsigned int8 count=0;


void main()
{
   set_tris_a(0xff);
   set_tris_b(0);
   set_tris_d(0);
   
   setup_timer_0(t0_ext_L_to_H|t0_div_by_1);
   set_timer0(0);
   
   while(true)
   {
      count=get_timer0();
      if(count>12)
      {
         set_timer0(1);
      }
      output_b(code7seg[count/10%10]);
      output_d(code7seg[count%10]);
   }
}
