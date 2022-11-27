#include <16f887.h>
#fuses intrc
#use delay(clock=8M)

#define LCD_ENABLE_PIN  PIN_E0                                    ////
#define LCD_RS_PIN      PIN_E1                                    ////
#define LCD_RW_PIN      PIN_E2                                    ////
#define LCD_DATA4       PIN_D4                                    ////
#define LCD_DATA5       PIN_D5                                    ////
#define LCD_DATA6       PIN_D6                                    ////
#define LCD_DATA7       PIN_D7 
#include <lcd.c>

#define RUN    pin_b0
#define STOP   pin_b1
//khong dinh nghia nut RESET o day,vi no duoc noi vao chan MCLR cua VDK
// khi ma e nhan RESET thi chuong trinh cua e se chay lai tu dau
// co nghia la ca bien cua e se dc khio tao lai

unsigned int8  mode=0; //0=reset , 1-run, 2-stop
unsigned int8  product=0;
unsigned int16 box=0;

void main()
{
   set_tris_d(0x00);
   set_tris_e(0x00);
   set_tris_c(0x01); //0b0000.0001  - counter 1 ==> pin_c0
   
   
   lcd_init();
   // hien thi 1 lan thi de o day 
   
   while(true)
   {
      if(input(RUN)==0)    mode=1;
      if(input(STOP)==0)   mode=2;
      
      if(mode==0) //reset - moi cap dien 
      {
         //DUNG DEM COUNTER 1
         lcd_gotoxy(11,1);
         lcd_putc("RESET");
      }
      else if (mode==1) //run 
      {
         //Enable counter 1 - cho phep dem 
         lcd_gotoxy(11,1);
         lcd_putc("  RUN");
         product=get_timer1();
         if(product==50)
         {
            box++;
         }
         
         if(box==50000) mode=2; //chuyen san trang thai STOP
         
         
      }
      else if (mode==2)
      {
         //DUNG DEM COUNTER 1
         lcd_gotoxy(11,1);
         lcd_putc(" STOP");
         if(box==50000)
         {
            lcd_gotoxy(12,1);
            lcd_putc("FULL");
         }
      }
      
      
      //hien thi san pham va thung 
      lcd_gotoxy(1,1);
      printf(lcd_putc,"P=%02u",product);
      lcd_gotoxy(1,2);
      printf(lcd_putc,"Box=%05Lu", box);
      
   }
}

