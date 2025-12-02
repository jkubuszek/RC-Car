#include "MKL05Z4.h"
#define rdir1 PTB10 
#define rdir2 PTB11 
#define ldir1 PTB12
#define ldir2 PTB13

#define rdir1_mask (1<<10) 
#define rdir2_mask (1<<11) 
#define ldir1_mask (1<<12) 
#define ldir2_mask (1<<13) 

void InitDrive(){
    //SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; //already done in InitPWM.h	

    PORTB->PCR[rdir1] |= PORT_PCR_MUX(0);
    PORTA->PCR[rdir2] |= PORT_PCR_MUX(0);

    PORTB->PCR[ldir1] |= PORT_PCR_MUX(0);
    PORTA->PCR[ldir2] |= PORT_PCR_MUX(0);

    PTB->PDDR |= (rdir1_mask | rdir2_mask | ldir1_mask | ldir2_mask);
}