#include "InitDrive.h"

void InitDrive(void){
    //SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; //already done in InitPWM.h	

    PORTB->PCR[rforward] |= PORT_PCR_MUX(1);
    PORTB->PCR[rreverse] |= PORT_PCR_MUX(1);

    PORTB->PCR[lforward] |= PORT_PCR_MUX(1);
    PORTB->PCR[lreverse] |= PORT_PCR_MUX(1);

    PTB->PDDR |= (rforward_mask | rreverse_mask | lforward_mask | lreverse_mask);
}