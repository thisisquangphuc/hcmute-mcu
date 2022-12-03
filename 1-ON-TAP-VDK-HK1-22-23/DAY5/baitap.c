/**
DUNG CHIET AP 50MV/1% DIEU CHHINH CAP DO DONG CO 
CO 10 CAP   
XUAT DU LIEU RA UART 
**/
#include <16f887.h>
#device adc=10
#fuses  intrc_io  // khai bao nay de su dung 2 chan A6,A7 thanh IO 
#use delay(clock=8Mhz)
#use rs232(BAUD=4800,BITS=8,STOP=1,PARITY=N,RCV=PIN_C7,XMIT=PIN_C6) 

unsigned int8 per=0;
unsigned int8 level=0, level_pre=1;

void main()
{
   set_tris_e(0xff);
   set_tris_c(0x80);
   setup_adc(adc_clock_internal);
   setup_adc_ports(SAN5|VSS_VDD);
   set_adc_Channel(5);
   printf("%03u %02u \r\n",per,level);
   while(true)
   {
      per=read_adc()/10.23;      //per [0;100]
      level = per/10;
      if(level_pre != level)
      {
         printf("%03u %02u  \r\n",per,level);
         level_pre = level;
      }
      
   }
}
