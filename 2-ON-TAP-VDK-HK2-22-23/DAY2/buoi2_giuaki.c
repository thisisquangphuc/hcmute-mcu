#include <16f887.h>  
#device adc=10
#fuses intrc
#use delay(clock=8M)
#include <lcd.c>

#bit TMR1IF =0x0c.0      //khai bao co tran timer 1                   
                         
const unsigned int8 code7seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

#define RUN    pin_c3  
#define PAUSE   pin_c4
#define pulse pin_e0


unsigned int8 mode=0;
unsigned int8 temp=0, product=0;
unsigned int16 box=0;
unsigned int8 overcount=0;
             
void main()
{
    set_tris_a(0x00);
    set_tris_b(0);
    set_tris_c(0b00011000); //0x18
    set_tris_d(0);
    set_tris_e(0x04); //0b00000100
    
    
    lcd_init();
    setup_adc(adc_clock_internal);
    setup_adc_ports(san7|vss_vdd);
    set_adc_channel(7);
                                   
    setup_timer_1(t1_div_by_1);
    set_timer1(0);
    
    setup_timer_0(t0_internal|t0_div_256);
    set_timer0(100);
    
                       
    while(true)
    {
         if(input(RUN)==0)  
         {
            mode=1; 
            setup_timer_1(t1_external);     //bat counter
         }             
         if(input(PAUSE)==0) {
            mode=2; 
            setup_timer_1(t1_disabled);    //dung dem  
         }
         
         if(mode==1) {
            //doc adc
              temp=read_adc()/2.046;   
                                  
            //dem sp  
              product = get_timer1();
              if (product ==24) {
                  box++;
              }
            //xuat xung      
              if(TMR1IF==1) //Tràn 
              {        
                  set_timer1(100); overcount++; TMR1IF=0;
                  if(overcount<7) {   
                     output_high(pulse);
                  } else if (overcount < 10) {
                     output_low(pulse);
                  } else {
                     overcount=0;
                  }
              }             
            
         } else if (mode==2) {
             //doc adc
              temp=read_adc()/2.046; 
              
              setup_timer_1(t1_disabled);
              
              output_low(pulse); //tat xung
              
         } else { 
               temp=read_adc()/2.046;
         }//mode ==0
     
         //hien thi 7 seg
         output_a(code7seg[temp/10]);  
         output_b(code7seg[temp%10]);  
         // hien thi lcd                                
         lcd_gotoxy(1,1); 
         printf(lcd_putc,"P=%02u", product); 
         lcd_gotoxy(2,1);
         printf(lcd_putc,"Box=%05Lu", box); 
         
         lcd_gotoxy(1,10);
         if(temp>40) {
            lcd_putc("ALARM");
         } else {
            lcd_putc("     ");
         } 
                                     
         lcd_gotoxy(2,10);
         if(mode==1) {
            lcd_putc("RUN ");
         } else if (mode==0){        
            lcd_putc("STOP");
         } 
    }        
}

