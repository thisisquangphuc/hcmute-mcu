#include <16f887.h>
#fuses hs,put,noprotect,nowdt   //intrc_io
#use delay(clock=10Mhz)

#bit TMR1IF =0x0c.0
#define PULSE pin_e0

unsigned int8 count=0;


void main ()
{
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_4);
   set_timer1(64911);
   while (true)
   {
      if(TMR1IF==1) //Tr�n 
      {
         //du 1ms
         set_timer1(64911);  
         TMR1IF=0;      //xoa co tran
         count++;
      }
      if(count<1)      output_high(PULSE);
      else if(count<4)  output_low(PULSE);
      else count=0;
   }
}
