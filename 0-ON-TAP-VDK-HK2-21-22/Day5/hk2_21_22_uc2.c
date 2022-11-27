#include <16f887.h>
#device adc=10
#fuses  intrc_io  // khai bao nay de su dung 2 chan A6,A7 thanh IO 
#use delay(clock=8Mhz)
#use rs232(BAUD=9600,BITS=8,STOP=1,PARITY=N,RCV=PIN_C7,XMIT=PIN_C6) 

#define STOP2     pin_b0


unsigned int8 SPEED=0;
int1 MODE=0;  //0,1
unsigned int16 duty=0;
unsigned char rx_data=0;

#int_rda
void ngat_nhan()
{
   rx_data = getc();
   if(rx_data == 'S')         MODE = 0;
   else if (rx_data == 'R')   MODE = 1;
   else if (rx_data == 'F')   SPEED = 10;
   else if (rx_data >= 0x30 && rx_data <= 0x39 )   
   {
      SPEED = rx_data-0x30;
   }
}

void main()
{
   set_tris_b(0xff);
   set_tris_c(0x80);
  
   enable_interrupts(global);
   enable_interrupts(int_rda);
   
   
   setup_timer_2(t2_div_by_16, 249, 1);
   setup_ccp1(ccp_pwm);
   set_timer2(0);
   
   //ban dau tat dong co 
   set_pwm1_duty((unsigned int16) 0); output_low(pin_c2);
   
   MODE=0;
   
   while(true)
   {

      if(input(STOP2)==0) 
      {
         MODE = 0;
         putc('S');  // goi qua vdk1
      }
     
      duty = SPEED*100; 
      
      if(MODE ==0)
      {
         set_pwm1_duty((unsigned int16) 0); output_low(pin_c2);
      }
      else
      {
         //set_pwm1_duty((unsigned int16) duty);
         set_pwm1_duty((unsigned int16) SPEED*100);  // chi de mo phong thoi 
      }
   }
}


