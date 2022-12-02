#include <16f887.h>
#fuses  hs  // khai bao nay de su dung 2 chan A6,A7 thanh IO 
#use delay(clock=20Mhz)

unsigned int16 speed1=0, speed2=0;
unsigned int16 maxduty=1000;
void main()
{
   set_Tris_c(0);
   
   setup_timer_2(T2_div_by_16,249,1);
   set_timer2(0);
   
   setup_ccp1(ccp_pwm);
   set_pwm1_duty((unsigned int16)0);
   setup_ccp2(ccp_pwm);
   set_pwm2_duty((unsigned int16)0);
 
   while(true)
   {
      
      speed1=50/100*maxduty;
      speed2=10/100*maxduty;
      set_pwm1_duty(speed1);
      set_pwm2_duty(speed2);
   }
   
}
