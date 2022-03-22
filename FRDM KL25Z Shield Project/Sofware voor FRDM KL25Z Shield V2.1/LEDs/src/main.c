#include <MKL25Z4.H>

// Freedom KL25Z LEDs
#define LED1 (9)  // On port C
#define LED2 (8)  // On port C
#define LED3 (5)  // On port A
#define LED4 (13)  // On port A
#define LED5 (12) // On port A
#define LED6 (4)  // On port D

#define RED_LED_POS   (18)  // On port B
#define GREEN_LED_POS (19)  // On port B
#define BLUE_LED_POS  (1)   // On port D

// For creating a mask
#define MASK(x)       (1UL << (x))

// Local function prototypes
void Delay_us(uint32_t d);
void RGB_LEDs_DEMO();

// Main
int main(void)
{
		int i = 0; 
	
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

    // Turn on the LEDs
    PTC->PSOR |= MASK(LED1) | MASK(LED2);
    PTA->PSOR |= MASK(LED3) | MASK(LED4) | MASK(LED5);
		PTD->PSOR |= MASK(LED6);

    while(1)
    {
			
			if(i < 3)
			{	
        // Turn off the first LED
        PTC->PCOR |= MASK(LED1);
        Delay_us(100000UL);
			
        // Turn on the first LED
        PTC->PSOR |= MASK(LED1);
        Delay_us(5000000UL);
							
			  // Turn off the second LED
        PTC->PCOR |= MASK(LED2);
        Delay_us(100000UL);			 

        // Turn on the second LED
        PTC->PSOR |= MASK(LED2);
        Delay_us(100000UL);
		
			  // Turn off the third LED
        PTA->PCOR |= MASK(LED3);
        Delay_us(100000UL);
					
        // Turn on the third LED
        PTA->PSOR |= MASK(LED3);
        Delay_us(100000UL);
					
				// Turn off the fourth LED
        PTA->PCOR |= MASK(LED4);
        Delay_us(100000UL);

        // Turn on the fourth LED
        PTA->PSOR |= MASK(LED4);
        Delay_us(100000UL);
				
				// Turn off the fith LED
        PTA->PCOR |= MASK(LED5);
        Delay_us(100000UL);

        // Turn on the fith LED
        PTA->PSOR |= MASK(LED5);
        Delay_us(100000UL);
				
				// Turn off the sixth LED
        PTD->PCOR |= MASK(LED6);
        Delay_us(100000UL);

        // Turn on the sixth LED
        PTD->PSOR |= MASK(LED6);
        Delay_us(150000UL);
				
				i = i+1;
				
			}
			
			else
			{
				RGB_LEDs_DEMO();
				i = 0;
			}
			
    }

	
}
void RGB_LEDs_DEMO()
{
				// Turn on red from RGB LEDs
        PTB->PCOR = MASK(RED_LED_POS);
		    Delay_us(500000UL);
				// Turn off red from RGB LEDs
			  PTB->PSOR = MASK(RED_LED_POS);
				Delay_us(500000UL);
				// Turn on green from RGB LEDs
        PTB->PCOR = MASK(GREEN_LED_POS);	
				Delay_us(500000UL);
				// Turn off green from RGB LEDs
				PTB->PSOR = MASK(GREEN_LED_POS);	
				Delay_us(500000UL);		
				// Turn on blue from RGB LEDs
        PTD->PCOR = MASK(BLUE_LED_POS);
				Delay_us(500000UL);
				// Turn off blue from RGB LEDs
			  PTD->PSOR = MASK(BLUE_LED_POS);
				Delay_us(500000UL);
	
				// Turn on red from RGB LEDs
        PTB->PCOR = MASK(RED_LED_POS);
		    Delay_us(600000UL);
				// Turn on blue from RGB LEDs
        PTD->PCOR = MASK(BLUE_LED_POS);
				Delay_us(600000UL);
				// Turn on green from RGB LEDs
        PTB->PCOR = MASK(GREEN_LED_POS);	
				Delay_us(1000000UL);
				
				// Turn off all RGB LEDs
			  PTD->PSOR = MASK(BLUE_LED_POS);
				PTB->PSOR = MASK(GREEN_LED_POS);	
				PTB->PSOR = MASK(RED_LED_POS);
	
}

// Software delay of approximately 1.02 us, depending on CPU clock frequency
// and optimization level 
// - CPU clock: 48 MHz
// - Optimization level: -O3
// - Optimize for time: disabled
void Delay_us(uint32_t d)
{

#if (CLOCK_SETUP != 1)
  #warning This delay function does not work as designed
#endif

    volatile uint32_t t;

    for (t=7*d; t>0; t--)
    {;}
}