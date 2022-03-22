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
#include <math.h>
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

#define LED1 (9)  // On port C
#define LED2 (8)  // On port C
#define LED3 (5)  // On port A
#define LED4 (13)  // On port A
#define LED5 (12) // On port A
#define LED6 (2)  // On port D
/// \}
/*!
 * \brief Defines for creating masks
 */
#define MASK(x)       (1UL << (x))

// Local function prototypes
void Delay_us(uint32_t d);
void Init_ADC(void)  //enables adc0
	{
    SIM->SCGC6 |= (1UL << SIM_SCGC6_ADC0_SHIFT); 
    ADC0->CFG1 = 0xC; // 16 bits
    ADC0->SC2 = 0;
	}

float Measure_Voltage() //measures voltage from adc on pin ptb3
	{
    volatile unsigned res = 0;
    volatile float vref, vbat;
    ADC0->SC1[0] = 13; // start conversion on channel 0 ptb pin 3 is channel 13
    while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK))
    {;}
    res = ADC0->R[0];
    // complement result since voltage falls with increasing ohm level
    // but we want result to rise with increasing ohm level
    vbat = 3.3*res/65535;
    return vbat;
	}
/*!
 * \brief Main application
 */
int main(void)
{
		// Enable clock to ports B and D
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

    // Make 3 pins connected to the RGB LEDs GPIO
    PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK;     
    PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(1);          
    PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX_MASK;          
    PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(1);          
    PORTD->PCR[BLUE_LED_POS] &= ~PORT_PCR_MUX_MASK;          
    PORTD->PCR[BLUE_LED_POS] |= PORT_PCR_MUX(1);    

    // Set port pins to outputs
    PTB->PDDR |= MASK(RED_LED_POS) | MASK(GREEN_LED_POS);
    PTD->PDDR |= MASK(BLUE_LED_POS);

    // Turn off the RGB LEDs
    PTB->PSOR |= MASK(RED_LED_POS) | MASK(GREEN_LED_POS);
    PTD->PSOR |= MASK(BLUE_LED_POS);
        
	
    // Enable clock to ports A, C 
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTA_MASK;

    // Make 3 pins connected to the LEDs GPIO
    PORTC->PCR[LED1] &= ~PORT_PCR_MUX_MASK;     
    PORTC->PCR[LED1] |= PORT_PCR_MUX(1);          
    PORTC->PCR[LED2] &= ~PORT_PCR_MUX_MASK;          
    PORTC->PCR[LED2] |= PORT_PCR_MUX(1);          
    PORTA->PCR[LED3] &= ~PORT_PCR_MUX_MASK;          
    PORTA->PCR[LED3] |= PORT_PCR_MUX(1);  
		PORTA->PCR[LED4] &= ~PORT_PCR_MUX_MASK;     
    PORTA->PCR[LED4] |= PORT_PCR_MUX(1);          
    PORTA->PCR[LED5] &= ~PORT_PCR_MUX_MASK;          
    PORTA->PCR[LED5] |= PORT_PCR_MUX(1);          
    PORTD->PCR[LED6] &= ~PORT_PCR_MUX_MASK;          
    PORTD->PCR[LED6] |= PORT_PCR_MUX(1);  	

    // Set port pins to outputs
    PTC->PDDR |= MASK(LED1) | MASK(LED2);
    PTA->PDDR |= MASK(LED3) | MASK(LED4) | MASK(LED5);
	  PTD->PDDR |= MASK(LED6);

    // Turn off the LEDs
    PTC->PCOR |= MASK(LED1) | MASK(LED2);
    PTA->PCOR |= MASK(LED3) | MASK(LED4) | MASK(LED5);
		PTD->PCOR |= MASK(LED6);

	
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
		
    // Turn on the LEDs
    PTB->PSOR |= MASK(RED_LED_POS) | MASK(GREEN_LED_POS);
    PTD->PSOR |= MASK(BLUE_LED_POS);
		
    // Delay to allow the display to start
    Delay_us(500000UL);
    ssd1306_init();
    ssd1306_update();
    char str[20];
    ssd1306_clearscreen();
		ssd1306_setorientation(2); //flip screen to correct orientation.
    Init_ADC();

    while(1)
    {
      ssd1306_goto(0,0);
      ssd1306_clearscreen();
      
      sprintf(str, "Voltage: %f\r", Measure_Voltage());
      ssd1306_terminal(str);    
      Delay_us(1000UL);
			float voltage = Measure_Voltage();
			if (voltage < 0.5F) //this code is not very clean, but it's "error proof"
			{
				// Turn off the first LED
        PTC->PCOR |= MASK(LED1);
				// Turn off the second LED
        PTC->PCOR |= MASK(LED2);
				// Turn off the third LED
        PTA->PCOR |= MASK(LED3);
  			// Turn off the fourth LED
        PTA->PCOR |= MASK(LED4);
				// Turn off the fith LED
        PTA->PCOR |= MASK(LED5);
				// Turn off the sixth LED
        PTD->PCOR |= MASK(LED6);
			}		
			else if (voltage > 0.5F && voltage <1.0F)
			{
				// Turn on the first LED
        PTC->PSOR |= MASK(LED1);			
				// Turn off the second LED
        PTC->PCOR |= MASK(LED2);	
  			// Turn off the third LED
        PTA->PCOR |= MASK(LED3);
				// Turn off the fourth LED
        PTA->PCOR |= MASK(LED4);
				// Turn off the fith LED
        PTA->PCOR |= MASK(LED5);
				// Turn off the sixth LED
        PTD->PCOR |= MASK(LED6);
			}		
			else if (voltage > 1.0F && voltage <1.5F)
			{
				// Turn on the first LED
        PTC->PSOR |= MASK(LED1);			
				// Turn on the second LED
        PTC->PSOR |= MASK(LED2);
				// Turn off the third LED
        PTA->PCOR |= MASK(LED3);
				// Turn off the fourth LED
        PTA->PCOR |= MASK(LED4);
				// Turn off the fith LED
        PTA->PCOR |= MASK(LED5);
				// Turn off the sixth LED
        PTD->PCOR |= MASK(LED6);
			}		
			else if (voltage > 1.5F && voltage <2.0F)
			{
				// Turn on the first LED
        PTC->PSOR |= MASK(LED1);			
				// Turn on the second LED
        PTC->PSOR |= MASK(LED2);
				// Turn on the third LED
        PTA->PSOR |= MASK(LED3);
				// Turn off the fourth LED
        PTA->PCOR |= MASK(LED4);
				// Turn off the fith LED
        PTA->PCOR |= MASK(LED5);
				// Turn off the sixth LED
        PTD->PCOR |= MASK(LED6);
			}		
			else if (voltage > 2.0F && voltage <2.5F)
			{
				// Turn on the first LED
        PTC->PSOR |= MASK(LED1);			
				// Turn on the second LED
        PTC->PSOR |= MASK(LED2);
				// Turn on the third LED
        PTA->PSOR |= MASK(LED3);
				// Turn on the fourth LED
        PTA->PSOR |= MASK(LED4);
				// Turn off the fith LED
        PTA->PCOR |= MASK(LED5);
				// Turn off the sixth LED
        PTD->PCOR |= MASK(LED6);
			}		
			else if (voltage > 2.5F && voltage <3.0F)
			{
				// Turn on the first LED
        PTC->PSOR |= MASK(LED1);			
				// Turn on the second LED
        PTC->PSOR |= MASK(LED2);
				// Turn on the third LED
        PTA->PSOR |= MASK(LED3);
				// Turn on the fourth LED
        PTA->PSOR |= MASK(LED4);
				// Turn on the fith LED
        PTA->PSOR |= MASK(LED5);
			  // Turn off the sixth LED
        PTD->PCOR |= MASK(LED6);
			}		
			else if (voltage > 3.0F && voltage <3.5F)
			{
				// Turn on the first LED
        PTC->PSOR |= MASK(LED1);			
				// Turn on the second LED
        PTC->PSOR |= MASK(LED2);
				// Turn on the third LED
        PTA->PSOR |= MASK(LED3);
				// Turn on the fourth LED
        PTA->PSOR |= MASK(LED4);
				// Turn on the fith LED
        PTA->PSOR |= MASK(LED5);
			  // Turn on the sixth LED
        PTD->PSOR |= MASK(LED6);
			
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
