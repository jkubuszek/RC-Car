#include "InitLight.h"

void InitLight(void){
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; //already done in InitPWM.h	
	
    PORTA->PCR[rblink] |= PORT_PCR_MUX(1);
    PORTA->PCR[lblink] |= PORT_PCR_MUX(1);
		PORTA->PCR[frontbacklight] |= PORT_PCR_MUX(1);

    //PORTB->PCR[lforward] |= PORT_PCR_MUX(1);
    //PORTB->PCR[lreverse] |= PORT_PCR_MUX(1);

    PTA->PDDR |= (rblink_mask | lblink_mask | frontbacklight_mask);
    PTA->PCOR |= (rblink_mask | lblink_mask | frontbacklight_mask);
}
