#include <16f887.h>
#device adc=10
#fuses intrc
#use delay(clock=8M)                       
#use rs232(BAUD=9600,BITS=8,STOP=1,PARITY=N,RCV=PIN_C7,XMIT=PIN_C6)  
#include <lcd.c>
unsigned int8 temp1, temp2;

unsigned int8 count=0;

void main()
{
      set_tris_a(0xff);
      set_tris_c(0x80);
      
      lcd_init();
        
        
      while(true) {
           if(kbhit()==1) {
               if(count == 0)     
               {
                 temp1=getc();
                 count++; 
               } else {
                  //count != 0
                  temp2=getc();
                  count=0;  
               }          
           }                                         
           
           lcd_gotoxy(1,1);
           printf("CH1=%03u",temp1); lcd_putc(223); lcd_putc('C'); 
           
           lcd_gotoxy(2,1);              
           printf("CH2=%03u",temp2); lcd_putc(223); lcd_putc('C');
      }         
}






