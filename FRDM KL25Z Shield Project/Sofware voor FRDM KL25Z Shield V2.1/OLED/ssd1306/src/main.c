/*! ***************************************************************************
 *
 * \brief     Example how to use the SSD1306 Oled driver
 * \file      main.c
 * \author    Hugo Arends
 * \date      April 2021
 *
 * \copyright 2020 HAN University of Applied Sciences. All Rights Reserved.
 *            \n\n
 *            Permission is hereby granted, free of charge, to any person
 *            obtaining a copy of this software and associated documentation
 *            files (the "Software"), to deal in the Software without
 *            restriction, including without limitation the rights to use,
 *            copy, modify, merge, publish, distribute, sublicense, and/or sell
 *            copies of the Software, and to permit persons to whom the
 *            Software is furnished to do so, subject to the following
 *            conditions:
 *            \n\n
 *            The above copyright notice and this permission notice shall be
 *            included in all copies or substantial portions of the Software.
 *            \n\n
 *            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *            OTHER DEALINGS IN THE SOFTWARE.
 *
 *****************************************************************************/
#include <MKL25Z4.H>
#include <stdio.h>

#include "ssd1306.h"

/// \name Definitions for Freedom KL25Z LEDs
/// \{

/*!
 * \brief Defines for the Freedom KL25Z LEDs
 */
#define RED_LED_POS   (18)  // On port B
#define GREEN_LED_POS (19)  // On port B
#define BLUE_LED_POS  (1)   // On port D

/// \}

/*!
 * \brief Defines for creating masks
 */
#define MASK(x)       (1UL << (x))

// Local function prototypes
void Delay_us(uint32_t d);

/*!
 * \brief Main application
 */
int main(void)
{
    // Enable clock to ports B and D
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

    // Make 3 pins connected to the LEDs GPIO
    PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK;     
    PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(1);          
    PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX_MASK;          
    PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(1);          
    PORTD->PCR[BLUE_LED_POS] &= ~PORT_PCR_MUX_MASK;          
    PORTD->PCR[BLUE_LED_POS] |= PORT_PCR_MUX(1);    

    // Set port pins to outputs
    PTB->PDDR |= MASK(RED_LED_POS) | MASK(GREEN_LED_POS);
    PTD->PDDR |= MASK(BLUE_LED_POS);

    // Turn off the LEDs
    PTB->PSOR |= MASK(RED_LED_POS) | MASK(GREEN_LED_POS);
    PTD->PSOR |= MASK(BLUE_LED_POS);
        
    // Delay to allow the display to start
    Delay_us(500000UL);
    ssd1306_init();
    ssd1306_update();
    
    char str[20];
    ssd1306_clearscreen();
        
    while(1)
    {
			  // Flash red LED
        PTB->PCOR = MASK(RED_LED_POS);
        Delay_us(60000UL);
        PTB->PSOR = MASK(RED_LED_POS);
			
				ssd1306_setorientation(2); //flip screen to correct orientation.
        // ---------------------------------------------------------------------
        // Demo 1: Different fonts
        ssd1306_setfont(Monospaced_plain_10);
        ssd1306_clearscreen();
        ssd1306_putstring(0,0,"Demo 1\nDifferent fonts");
        ssd1306_update();
        Delay_us(1000000UL);
        
        ssd1306_setfont(Monospaced_plain_10);
        ssd1306_clearscreen();
        ssd1306_putstring(0,0,"Monospaced_plain_10");
        ssd1306_update();
        Delay_us(1000000UL);
        
        ssd1306_setfont(Dialog_plain_12);
        ssd1306_clearscreen();
        ssd1306_putstring(0,0,"Dialog_plain_12");
        ssd1306_update();
        Delay_us(1000000UL);
        
        ssd1306_setfont(Dialog_plain_6);
        ssd1306_clearscreen();
        ssd1306_putstring(0,0,"Dialog_plain_6");
        ssd1306_update();
        Delay_us(1000000UL);
        
        ssd1306_setfont(Kranky_Regular_20);
        ssd1306_clearscreen();
        ssd1306_putstring(0,0,"Kranky_Reg\nular_20");
        ssd1306_update();
        Delay_us(1000000UL);


        // ---------------------------------------------------------------------
        // Demo 2: Draw lines
				// Flash red LED
        PTB->PCOR = MASK(RED_LED_POS);
        Delay_us(60000UL);
        PTB->PSOR = MASK(RED_LED_POS);
				
        ssd1306_setfont(Monospaced_plain_10);
        ssd1306_clearscreen();
        ssd1306_putstring(0,0,"Demo 2\nDraw lines");
        ssd1306_update();
        Delay_us(1000000UL);
        
        ssd1306_clearscreen();
        
        ssd1306_drawline(0, 0, 63, 63);
        ssd1306_update();
        Delay_us(500000UL);
        
        ssd1306_drawline(63, 0, 0, 63);
        ssd1306_update();
        Delay_us(500000UL);
        
        ssd1306_drawline(64, 0, 127, 63);
        ssd1306_update();
        Delay_us(500000UL);
        
        ssd1306_drawline(127, 0, 64, 63);
        ssd1306_update();
        Delay_us(500000UL);

        ssd1306_drawline(0, 30, 127, 30);
        ssd1306_drawline(0, 31, 127, 31);
        ssd1306_drawline(0, 32, 127, 32);
        ssd1306_drawline(0, 33, 127, 33);
        ssd1306_update();
        Delay_us(500000UL);

        ssd1306_drawline(31, 0, 31, 63);
        ssd1306_drawline(95, 0, 95, 63);
        ssd1306_update();
        Delay_us(500000UL);

        ssd1306_drawline(0, 0, 127, 63);
        ssd1306_drawline(0, 63, 127, 0);
        ssd1306_update();
        Delay_us(500000UL);

        // ---------------------------------------------------------------------
        // Demo 3: Show bitmap and text
				// Flash red LED
        PTB->PCOR = MASK(RED_LED_POS);
        Delay_us(60000UL);
        PTB->PSOR = MASK(RED_LED_POS);
				
        ssd1306_setfont(Monospaced_plain_10);
        ssd1306_clearscreen();
        ssd1306_putstring(0,0,"Demo 3\nShow bitmap and text");
        ssd1306_update();
        Delay_us(1000000UL);
        
        ssd1306_drawbitmap(bitmap1);
        ssd1306_setfont(Kranky_Regular_20);
        ssd1306_putstring(64,5,"HAN\nMIC2");
        ssd1306_update();
        Delay_us(2000000UL);

        // ---------------------------------------------------------------------
        // Demo 4: Invert display
				// Flash red LED
        PTB->PCOR = MASK(RED_LED_POS);
        Delay_us(60000UL);
        PTB->PSOR = MASK(RED_LED_POS);
								
        ssd1306_setfont(Monospaced_plain_10);
        ssd1306_clearscreen();
        ssd1306_putstring(0,0,"Demo 4\nBitmap and inverse\ndisplay");
        ssd1306_update();
        Delay_us(1000000UL);
        
        ssd1306_drawbitmap(bitmap2);
        ssd1306_update();
        
        for(int i=0; i<10; i++)
        {
            ssd1306_setinverse(i%2);
            Delay_us(500000UL);
        }
        
        ssd1306_setinverse(0);

        // ---------------------------------------------------------------------
        // Demo 5: Display orientation
				// Flash red LED
        PTB->PCOR = MASK(RED_LED_POS);
        Delay_us(60000UL);
        PTB->PSOR = MASK(RED_LED_POS);
				
        ssd1306_setfont(Monospaced_plain_10);
        ssd1306_clearscreen();
        ssd1306_putstring(0,0,"Demo 5\nDisplay orientation");
        ssd1306_update();
        Delay_us(1000000UL);
        
        for(int i=0; i<10; i++)
        {
            ssd1306_setorientation(i%2);
            Delay_us(500000UL);
        }
        
        ssd1306_setorientation(2);

        // ---------------------------------------------------------------------
        // Demo 6: Terminal emulation
				// Flash red LED
        PTB->PCOR = MASK(RED_LED_POS);
        Delay_us(60000UL);
        PTB->PSOR = MASK(RED_LED_POS);
				
        ssd1306_setfont(Monospaced_plain_10);
        ssd1306_clearscreen();
        ssd1306_putstring(0,0,"Demo 6\nTerminal emulation");
        ssd1306_update();
        Delay_us(1000000UL);
        
        ssd1306_goto(0,0);
        ssd1306_clearscreen();
        for(short i=0; i<20; ++i)
        {
            sprintf(str, "%04hd\n", i);
            ssd1306_terminal(str);    
            Delay_us(100000UL);        
        }
        
        ssd1306_clearscreen();
        for(short i=0; i<20; ++i)
        {
            sprintf(str, "%04hd\r", i);
            ssd1306_terminal(str);    
            Delay_us(100000UL);        
        }   

    }
}

/*!
 * \brief Creates a non-blocking delay
 *
 * Software delay of approximately 1.02 us, depending on CPU clock frequency
 * and optimization level 
 * - CPU clock: 48 MHz
 * - Optimization level: -O3
 * - Optimize for time: disabled
 *
 * SysTick timer has been used to measure the execution time of the following
 * function.
 *   - SysTick clock was set to 48 MHz
 *   - When t is set to 1000, the measured average execution time is 7017
 *   - This is equal to a delay of 7017 * (1/48MHz) = 146.1875 us
 *   - This means that if t would be set to one, the average delay would be
 *     146.1875 / 1000 = 0.1461875 us
 *   - Therefor, if t is set to one and a microsecond delay should be generated,
 *     the for-loop should take 1 us / 0.1461875 us = 6.840530141 times longer
 *   - This value is rounded to 7, which means that an actual average delay 
 *     is equal to 7 * 0.1461875 us = 1.0233125 us
 *
 * \param[in]  d  delay in microseconds
 */
void Delay_us(uint32_t d){

#if (CLOCK_SETUP != 1)
  #warning This delay function does not work as designed
#endif

volatile uint32_t t;
  
  for (t=7*d; t>0; t--)
  {;}
}
