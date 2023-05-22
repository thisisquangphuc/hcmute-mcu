#include <16f887.h>
#fuses intrc
#use delay(clock=8M)

#include <lcd.c>       

#define RUN pin_b0
#define STOP pin_b1

int8 mode =0;                
unsigned int8 product=0;
unsigned int16 box=0;
                     
  
void hienthiLCD()
{
   lcd_gotoxy(1,1);
   printf(lcd_putc,"P=%02u",product);
   
   lcd_gotoxy(2,1);
   printf(lcd_putc,"Box=%05Lu", box);
    
   lcd_gotoxy(1,10); 
   if(mode==1) {
      lcd_putc("RUN ");
   } else if (mode==2){
      lcd_putc("STOP"); 
      if (box==50000) {
           lcd_gotoxy(2,10);
           lcd_putc("FULL");
      }
   } else {
      lcd_putc("RESET");
   }  
   
    
   
}


void main()
{
   set_tris_a(0xff);
   set_tris_b(0b00000011);
   set_tris_c(0);
   set_tris_d(0);
   
   
   lcd_init();                            
   setup_timer_1(t1_div_by_1);
   set_timer1(0);
                                      
   while(true)
   {
      if(input(RUN)==0)
      {
         mode=1;
         setup_timer_1(t1_external); //bat timer 1
      } else if(input(STOP)==0) {
         mode=2;
         setup_timer_1(t1_disabled);   //tat timer 1                                    
      }                                 
      
      if(mode!=0)
      {
         product=get_timer1();
         if (product == 50) box++;
         if (box==50000) 
         {     
            setup_timer_1(t1_disabled);   //tat timer 1  
            mode = 2; 
         }            
      }
      
      hienthiLCD();
         
   }
   
}    

