#include <16f887.h>
#fuses hs          
#use delay(clock=20M)    

const unsigned int8 code7seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
  
  
unsigned int8 product=0;
unsigned int16 box;  


void main()
{     
   set_tris_a(0xff);          
   set_tris_c(0);       
   set_tris_d(0);  
   
   setup_timer_0(t0_ext_L_to_H|t0_div_1);
   set_timer0(0);  //ghi so 0 vaof timer 0

   while(true)
   {       
       product = get_timer0();
       if(product==12)             
       {
         set_timer0(0);           
         box++;
         output_high(pin_e0);
         delay_ms(5);
       }
       output_low(pin_e0);
   }
   

}
