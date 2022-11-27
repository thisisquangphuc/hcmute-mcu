#INCLUDE <16F887.H>
#fuses intrc   //intrc_io
#use delay(clock=8M)
#use rs232(BAUD=9600,BITS=8,STOP=1,PARITY=N,RCV=PIN_C7,XMIT=PIN_C6) 

#define RUN       pin_d0
#define STOP      pin_d1
#define LED_STATUS    pin_d2

unsigned char rx_data=0;
int1 mode=0;         //0=stop, 1=run

void main()
{
   set_tris_d(0x03); //0b0000.0011
   set_tris_d(0x80); 
   output_low(LED_STATUS);
   
   while(true)
   {
    
      if(input(RUN)==0)
      {
         output_high(LED_STATUS);
         putc('1');
      }
      if(input(STOP)==0)
      {
         output_low(LED_STATUS);
         putc('0');
      }
            
   }
   
}
