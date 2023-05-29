#include <16f887.h>
#fuses hs          
#use delay(clock=20M)    

#define LED pin_e1
#define PULSE pin_e0

#INT_TIMER1 //khai bao ngat
void ngat_t1()
{
     //moi khi timer 1 tran thi chuong trinh chinh nhay vao day 
     //da du 10ms  
     set_timer1(63036);
     output_toggle(PULSE);   
     clear_interrupt(int_timer1);        
}
//void nhapnhayled();
void main() {
   set_tris_a(0xff);
   set_tris_e(0);
   
   while(true)
   {
       output_high(LED);
       delay_ms(2000);
       output_low(LED);
       delay_ms(1000);   
       
       //nhapnhayled();
   }

}
