#include "MKL05Z4.h"
#define rforward 10 //PTB10 
#define rreverse 11 //PTB11 
#define lforward 12 //PTB12
#define lreverse 13 //PTB13

#define rforward_mask (1<<10) 
#define rreverse_mask (1<<11) 
#define lforward_mask (1<<12) 
#define lreverse_mask (1<<13) 

void InitDrive(){
    //SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; //already done in InitPWM.h	

    PORTB->PCR[rforward] |= PORT_PCR_MUX(1);
    PORTB->PCR[rreverse] |= PORT_PCR_MUX(1);

    PORTB->PCR[lforward] |= PORT_PCR_MUX(1);
    PORTB->PCR[lreverse] |= PORT_PCR_MUX(1);

    PTB->PDDR |= (rforward_mask | rreverse_mask | lforward_mask | lreverse_mask);
}