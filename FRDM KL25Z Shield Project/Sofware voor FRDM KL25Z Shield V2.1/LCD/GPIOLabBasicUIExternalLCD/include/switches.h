#ifndef SWITCHES_H
#define SWITCHES_H

// All switches are on port E
#define SW_K1_POS (30)
#define SW_K2_POS (29)
#define SW_K3_POS (23)
#define SW_K4_POS (22)

// Macro to read switches returns state switches, active low
#define READ_SWITCHES (PTE->PDIR)  

// Function prototypes
extern void Init_Switches(void);

#endif
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
