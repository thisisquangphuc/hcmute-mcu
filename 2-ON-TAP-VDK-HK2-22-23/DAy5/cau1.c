#include <16f887.h>
#fuses intrc
#use delay(clock=4M)

const unsigned int8 code7seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

unsigned int8 value=0x00;   
unsigned int8 pos=0;         
 
void main()
{
   set_tris_a(0xff);
   set_tris_c(0);   
   set_tris_d(0);   
   
   while (true)
   {
       output_d(code7seg[pos+1]);   // L1-L8
       //xu ly trang thai led 
       value = 0x01 << pos;
       //xuat ra gpio
       output_c(value);  
       delay_ms(500);
       pos++;
       if(pos>=8) pos=0;
   }
}


