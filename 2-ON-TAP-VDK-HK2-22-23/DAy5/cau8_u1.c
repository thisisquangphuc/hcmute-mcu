#include <16f887.h>
#device adc=10
#fuses intrc
#use delay(clock=8M)    
#use rs232(BAUD=9600,BITS=8,STOP=1,PARITY=N,RCV=PIN_C7,XMIT=PIN_C6)  
unsigned int8 temp1, temp2;


void main()
{
      set_tris_a(0xff);
      set_tris_c(0x80);
      
      setup_adc(adc_clock_internal);
      setup_Adc_ports(san0|san1|vss_vdd);
      
      while(true) {
           set_adc_channel(0);
           temp1=read_adc()/2.046; 
           set_adc_channel(1);
           temp2=read_adc()/2.046; 
           
                  //cach 1
           putc(temp1);    
           putc(temp2|0x80);
//!           cach 2
//!           putc(temp1);    
//!           putc(temp2);      
                  
      }         
}






