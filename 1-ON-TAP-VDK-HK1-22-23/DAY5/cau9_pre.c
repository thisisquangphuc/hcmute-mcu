#include <16f887.h>
#fuses  intrc  // khai bao nay de su dung 2 chan A6,A7 thanh IO 
#use delay(clock=8Mhz)

#use rs232(BAUD=4800,BITS=8,STOP=1,PARITY=N,RCV=PIN_C7,XMIT=PIN_C6) 

#define SEND pin_e0
unsigned int8 rand_num=0;


void main()
{
   set_tris_e(0xff);
   
   while(true)
   {
      for(unsigned int8 i=0; i<10; i++)
      {
         if(input(SEND)==0)
         {
            delay_ms(20);
            if(input(SEND)==0)
            {
               //CONG VIEC
               rand_num=i;
               While(input(SEND)==0);
               //putc(rand_num + 0x30);
               printf("%u\r\n",rand_num);
               break;
            }
         }
      }
      
      
   }
}
