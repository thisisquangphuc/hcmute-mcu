#include <16f887.h>
#device adc=10
#fuses hs
#use delay(clock=11.0592M)

#bit TMR1IF=0x0c.0            
#use rs232(BAUD=9600,BITS=8,STOP=1,PARITY=N,RCV=PIN_C7,XMIT=PIN_C6) 

const unsigned int8 code7seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

#define LD1 pin_c1  
#define LD2 pin_c2

unsigned int1 status=0;
unsigned int8 mode;
unsigned int16 temp, prev_temp;
unsigned int8 channel, overcount;
unsigned char rx_data;

void main()
{
   set_tris_a(0xff);
   set_tris_b(0);
   set_tris_d(0);
   set_tris_c(0b10000000);    //0x80 
   
   setup_adc(adc_clock_div_32);
   setup_adc_ports(san5|san6|vss_vdd);
   
   setup_timer_1(t1_internal|t1_div_by_8);
   set_timer1(736);
     
   mode=1;
   
   while(true)
   {
        if(kbhit()==1) {
           rx_data=getc();   
        }                      
        
        if(rx_data == 0x01) { 
            mode=1;   
            setup_timer_1(t1_disabled);
        }
        else if(rx_data == 0x02) {
           mode = 2;
           setup_timer_1(t1_disabled);
        }
        else if(rx_data == 0x00) 
        {
            mode = 0 ;   ////cho nay phai la else if  
            setup_timer_1(t1_internal);
        }   
        
        if(mode==1) {
            channel = 5;
            output_high(LD1);
            output_low(LD2); 
        } else if (mode==2) {
            channel = 6;
            output_low(LD1);
            output_high(LD2);
        } else if( mode == 0) {
             //do 2 kenh luan phien 
            if(TMR1IF==1) //Tran 
            {
               set_timer1(736); overcount++; TMR1IF=0;
               if(overcount==16)
               {   
                  status=~status;  // status=!status;    //chi su dung cho int1
                  overcount=0;
               }           
            }   
            if(status==1) {
               channel = 5; 
               output_high(LD1);
               output_low(LD2);
            } else {
               channel = 6;
               output_low(LD1);
               output_high(LD2);
            }    
            
        }
        
        //do nhiet do 
        temp=0; 
        set_adc_channel(channel);
        for(int16 i=0;i<300;i++) {
            temp=temp+read_adc()/2.046;
        }            
        temp=temp/300; 
        
        //xuat 7 seg
        
        output_b(code7seg[temp/10]);
        output_d(code7seg[temp%10]);                       
        
        //goi len may tinh
        if(temp!=prev_temp) {
            printf("%Lu",temp); 
            prev_temp = temp;
        }                          
              
   }
}

       
