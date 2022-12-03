#include <16f887.h>
#fuses  intrc_io  // khai bao nay de su dung 2 chan A6,A7 thanh IO 
#use delay(clock=8Mhz)
#use rs232(BAUD=9600,BITS=8,STOP=1,PARITY=N,RCV=PIN_C7,XMIT=PIN_C6) 

const unsigned int8 code7seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; 

#define UP pin_e0
#define DW pin_e1

signed int8    count=0;

void main()
{
   set_tris_c(0x80);
   set_tris_e(0);
   
   output_b(code7seg[0]);output_d(code7seg[0]);
   
   while(true)
   {
      if(input(UP)==0)
      {
         delay_ms(50);
         
         if(count<=13) count+=2;
         
         while(input(UP)==0);
      }
      if(input(DW)==0)
      {
         delay_ms(50);
         count--;
         if(count<0) count=0;
         while(input(DW)==0);
      }
           
      output_b(code7seg[count/10]);output_d(code7seg[count%10]);
      
   }
}
