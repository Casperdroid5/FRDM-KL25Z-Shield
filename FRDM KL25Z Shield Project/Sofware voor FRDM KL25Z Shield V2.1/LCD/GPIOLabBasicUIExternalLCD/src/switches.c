#include <MKL25Z4.H>
#include "switches.h"
#include "gpio_defs.h"

void Init_Switches(void)
{
    // Enable clock for port E
    SIM->SCGC5 |=  SIM_SCGC5_PORTE_MASK;

    // Select GPIO and enable pull-up resistors for pins connected to switches
    PORTE->PCR[SW_K1_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;	
    PORTE->PCR[SW_K2_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;	
    PORTE->PCR[SW_K3_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;	
    PORTE->PCR[SW_K4_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;	

    // Set port E bits connected to switches to inputs
    PTE->PDDR &= ~( MASK(SW_K1_POS) | 
                    MASK(SW_K2_POS) |
                    MASK(SW_K3_POS) | 
                    MASK(SW_K4_POS) );
}

// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
