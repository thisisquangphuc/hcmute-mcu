#include <16f887.h>
#fuses   intrc_io  // khai bao nay de su dung 2 chan A6,A7 thanh IO 
#use     delay(clock=8Mhz)
#use     rs232(BAUD=9600,BITS=8,STOP=1,PARITY=N,RCV=PIN_C7,XMIT=PIN_C6) 

const unsigned int8 code7seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; 

unsigned char data_rx;
unsigned int8 value=0;

#int_rda
void ngat_uart()
{
   data_rx=getc();
   if(data_rx >= 0 && data_rx <= 9)
   {
      value=data_rx;
   }
   if(data_rx=='A')
   {
      putc(value);
   }
   else if (data_rx=='S')
   {
      value=0;
   }
   clear_interrupt(int_rda);
}

void main()
{
   set_tris_d(0x03);  //0b000.0011
   set_tris_c(0x80);
   
   enable_interrupts(global);
   enable_interrupts(int_rda);
   
   while(true)
   {
      output_b(code7seg[value]);
   }
}
