#INCLUDE <16F887.H>
#fuses intrc   //intrc_io
#use delay(clock=8M)
#use rs232(BAUD=9600,BITS=8,STOP=1,PARITY=N,RCV=PIN_C7,XMIT=PIN_C6) 

#define LED_BLINK    pin_e0

unsigned char rx_data=0;
int1 mode=0;     //1=nhap nhay

/*
   Co 2 cach 
   - Timer dinh thoi 1s
   - Dung ham delay_msX();
   delay_msX(1000);
*/
void delay_msX(unsigned int16 time_ms)
{
   for(int16 i=0; i < time_ms; i++)
   {
      delay_ms(1);
      // kierm tra dieu khien 
      if(kbhit()==1)
      {
         rx_data =getc();
         break;
      }
   }
      
}
void main()
{

   set_tris_c(0x80);
   set_tris_e(0);
   
   while(true)
   {
      if(kbhit()==1)
      {
         rx_data =getc();
      }
      
      if(rx_data == '1')
      {
         //RUN
         mode=1;
      }
      else if(rx_data == '0')
      {
         mode=0;
      }
      
      if(mode==1)
      {
         output_high(LED_BLINK);
         delay_msX(1000);
         output_low(LED_BLINK);
         delay_msX(1000);
      }
      else
      {
         output_low(LED_BLINK);
      }
      
      
      
   }
}
