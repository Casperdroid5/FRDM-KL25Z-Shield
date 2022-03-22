/*----------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/
#include <MKL25Z4.H>
#include "gpio_defs.h"
#include "LCD_4bit.h"
#include "LEDs.h"
#include "switches.h"

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void)
{    
   Init_Switches();
   Init_RGB_LEDs();
   Control_RGB_LEDs(0,0,0);
   
   
   
   // 1: Only test the switches, so the application runs correctly without an
   //    LCD connected
   // 0: Test both switches and LCD. Make sure both are connected to the MCU.
#if 0
   Test_Switches();
#else
   lcd_clear();
   lcd_init();
   lcd_clear();
   
   PORTD->PCR[2] &= ~PORT_PCR_MUX_MASK;          
   PORTD->PCR[2] |= PORT_PCR_MUX(1);  
   PTD->PDDR |= MASK(2);
   PTD->PSOR |= MASK(2);
   
   
   
   while(1)
   {
		  for(int i=0; i<15000000; i++) // Delay
      {;}
      PTD->PSOR |= MASK(2); //turn led on
      lcd_set_cursor(0,0);
      lcd_print("     Hello");
      
      lcd_set_cursor(0,1);
      lcd_print("     world!");
				
      for(int i=0; i<100000000; i++) // Delay
      {;}
      PTD->PCOR |= MASK(2); //turn led off
      
      
     
      
   }
#endif
}