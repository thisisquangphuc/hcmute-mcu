#include <16f887.h>  
#device adc=10
#fuses intrc   
#use delay(clock=8M) 
                        
#DEFINE  LCD_RS_PIN      PIN_D0
#DEFINE  LCD_RW_PIN      PIN_D1
#DEFINE  LCD_ENABLE_PIN  PIN_D2
#DEFINE  LCD_DATA4     PIN_D4           
#DEFINE  LCD_DATA5     PIN_D5
#DEFINE  LCD_DATA6     PIN_D6
#DEFINE  LCD_DATA7     PIN_D7
#include <lcd.c>   

#use rs232(BAUD=4800,BITS=8,STOP=1,PARITY=N,RCV=PIN_C7,XMIT=PIN_C6) 
     
#define LED pin_e1
   
unsigned char rxdata;
unsigned int8 level, old_level;
int1 statusLED;     
unsigned int8 mode, old_mode;  
   
void delay_msX(unsigned int16 t);    
     
       
#int_rda
void uart_interrupt()
{
    rxdata=getc();
    old_mode = mode;
    if(rxdata=='R') {
        //bat pwm  - quay thuan
        setup_ccp1(ccp_pwm); 
        setup_ccp2(ccp_off);  
        mode = 1;   
   } else if(rxdata=='L') {
        //bat pwm - quay nghich             
        setup_ccp1(ccp_off);
        setup_ccp2(ccp_pwm); 
        mode = 2;
   } else if (rxdata=='S') {
        //tat pwm  
        setup_ccp1(ccp_off); 
        setup_ccp2(ccp_off);  
        mode = 0;
   } 
}      
     
void main() {        
   set_tris_a(0xff);
   set_tris_c(0x80);     //1000.0000 
   set_tris_d(0);
   set_tris_e(0b00000001);      //0x01
   
   lcd_init();
   setup_adc(adc_clock_internal);
   setup_adc_ports(san5|vss_vdd); //   setup_adc_ports(san5|vss_vref);
   set_adc_channel(5);     
   
   setup_timer_2(t2_div_by_16, 124, 1); 
   set_timer2(0);
   setup_ccp1(ccp_pwm);
   setup_ccp2(ccp_pwm);
   
   enable_interrupts(global);
   enable_interrupts(int_rda);
                
   while(true)
   {     
   
      level=read_adc()/102.3;  
      lcd_gotoxy(2,1);
      if(mode==1) {
            set_pwm1_duty(level*10/100*500); 
            statusLED = 1;     
            printf(lcd_putc,"DIR = Left ");  
      } else if(mode==2) {            
           set_pwm2_duty(level*10/100*500);  
           statusLED = 1;     
           printf(lcd_putc,"DIR = Right");  
      } else if (mode==0) {
           //tat pwm  
           statusLED = 0; 
           printf(lcd_putc,"DIR = Stop ");   
      }  
       
      if (statusLED==1) {            
         output_toggle(LED);
         delay_msX(5000);
      } else {
         output_low(LED);
      }
            
      //hoen thi LCD
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Duty=%03u%%",level*10);      //lcd_putc('%');    
                    
   }                                    
}
   
void delay_msX(unsigned int16 t)     
{
    for (unsigned int16 i=0; i<t; i++) {
         //cong viec  
         //kiem tra chiet ap
         level=read_adc()/102.3;
         if(level != old_level ) {
            old_level = level;
            break;
         } 
         //du lieu uart da dc xu ly boi ngat 
         if(mode != old_mode) {
            old_mode = mode;
            break; 
         }
           
         delay_ms(1);
    }
}
     
     
                                                                     

                                 
