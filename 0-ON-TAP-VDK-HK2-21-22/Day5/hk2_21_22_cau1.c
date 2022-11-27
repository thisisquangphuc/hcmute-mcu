#include <16f887.h>
#fuses  intrc_io  // khai bao nay de su dung 2 chan A6,A7 thanh IO 
#use delay(clock=8Mhz)

#define RUN_STOP  pin_b0
#define CLEAR     pin_b1

#define LED       pin_e0
#define PULSE     pin_e1

unsigned int8 bdt=0;
unsigned int8 sp=0;
unsigned int16 box=0;
int1 led_status=0;
int1 pulse_status=0;
unsigned int8 MoDE =0;   //0-stop, 1-run, 2-clear
INT1 bt_status =0;

#int_timer0
void timer0()
{
   //bo chi 64, nap=100
   //tran du 5ms
   pulse_status = !pulse_status;
   bdt++;
   if(bdt==200)
   {
      //du 1s=200.5ms
      led_status =! led_status;
      bdt=0;
   }
   clear_interrupts(int_timer0);
   
}
//!#int_timer1
//!void timer1()
//!{
//!   // dinh thoi 1s
//!   //bo chia 8 
//!   // nap 3036
//!   // tran 10 lan 
//!   bdt1++;
//!   if(bdt1==10)
//!   {
//!      led_status =! led_status;
//!      bdt1=0;
//!   }
//!   clear_interrupts(int_timer0);
//!}

void main()
{
   
   
   while()
   {
      if(input(RUN_STOP)==0)
      {
         delay_ms(20);
         if(input(RUN_STOP)==0)
         {
            bt_status=!bt_status;
         }
         
         if(bt_status==0) 
         {
            MODE=0;
            setup_Timer_1(t1_disabled);
         }
         else             
         {
            MODE=1;
            //bat counter 1
            setup_Timer_1(t1_external|t1_div_by_1);
            
         }
      }
      
      sp=get_timer1();
      if(sp==24)
      {
         box++;
         set_timer1(0);
      }
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Product=%02u",sp);
      lcd_gotoxy(1,2);
      printf(lcd_putc,"Box=%05Lu",box);
      
      if(input(CLEAR)==0)
      {
         MODE =2;
      }
      
      if(MODE==0)
      {
         //trang thai STOP
         //bat led
         output_high(LED);
      }
      else if(MODE==1)
      {
         //trang thai RUN
         //nhap nhay led 
         if(led_status==0) output_low(LED);
         else              output_high(LED);
         
         //xuat xung re1
         if(pulse_status==0) output_low(PULSE);
         else                 output_high(PULSE);
         
      }
      else if(MODE==2)
      {
         //trang thai clear
         output_low(LED);
      }
      
   }
}

