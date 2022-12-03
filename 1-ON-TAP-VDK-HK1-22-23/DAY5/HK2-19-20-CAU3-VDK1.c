#include <16f887.h>
#fuses   intrc_io  // khai bao nay de su dung 2 chan A6,A7 thanh IO 
#use     delay(clock=8Mhz)
#use     rs232(BAUD=9600,BITS=8,STOP=1,PARITY=N,RCV=PIN_C7,XMIT=PIN_C6) 


#DEFINE BLINK  pin_d2
#DEFINE ADJ    pin_d0
#DEFINE STOP   pin_d1

unsigned char data_rx;
unsigned int8 value=0;
unsigned int8 freq=0;
int1 MODE=1;
//ban dau vao chuong trinh mac dinh chay
//vi de khong noi khi nao chuong trinh start
//nhung trong de co chuc nang STOP 
int1 TT_NN=0;
unsigned int8 count=0;
#INT_RDA
void ngat_uart()
{
   data_rx=getc();
   if(data_rx>=0 && data_rx<=9)
   {
      freq = data_rx;
   }
   clear_interrupt(INT_RDA);
}
#INT_TIMER1
void ngat_timer1()
{
   count++; set_timer1(3036);
   unsigned int8 count_freq = 10*freq;
   // 1s       --> 10 lan
   // freq (s) --> tran 10*freq lan
   if(count == count_freq)
   {
      count=0;
      //cong viec
      //du freq (s)
      TT_NN = !TT_NN;
   }
}
void main()
{
   set_tris_d(0x03);  //0b000.0011
   set_tris_c(0x80);
   
   enable_interrupts(global);
   enable_interrupts(int_rda);
   enable_interrupts(int_timer1);
   
   while(true)
   {
      if(input(ADJ)==0) 
      {
         delay_ms(50);
         value++;
         if(value>9) value=1;
         putc(value);
         putc('A');
         while(input(ADJ)==0);
      }
      if(input(STOP)==0) 
      { // khong chong doi 
         MODE=0; value=0;
         putc('S');
      }
      
      if(MODE==1) 
      {
         if(TT_NN == 1) output_high(BLINK);
         else           output_low(BLINK);
      }
      else
      {
         output_low(BLINK);
      }
      
      
      
      
   }
}


   
