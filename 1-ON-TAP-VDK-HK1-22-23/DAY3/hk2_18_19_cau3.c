#include <16f887.h>
#fuses  intrc_io  // khai bao nay de su dung 2 chan A6,A7 thanh IO 
#use delay(clock=8Mhz)
#use rs232(BAUD=4800,BITS=8,STOP=1,PARITY=N,RCV=PIN_C7,XMIT=PIN_C6) 

unsigned char rx_data=0;
unsigned int8  product=0,product_pre=0;
unsigned int16 box=0;


void main()
{
   set_tris_c(0x80);  //1000.0000
   setup_timer_1(t1_disabled|t1_div_by_1);
   set_timer1(0);
   
   while(true)
   {
      if(kbhit()==1)
      {
         rx_data=getc();
         if(rx_data=='1')  // 0x31
         {
            setup_timer_1(t1_external|t1_div_by_1);
         }
         else if (rx_data=='0')
         {
            setup_timer_1(t1_disabled|t1_div_by_1);
         }
         else;
      }
         
      product=get_timer1();
      if(product==50) 
      {
         box++;
         set_timer1(0);
      }
      if(product != product_pre)
      {
         printf("P=%02u,B=%05Lu",product,box);
         product_pre = product;
      }
      
      
   }
}
