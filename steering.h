#include "MKL05Z4.h"
#include "InitDrive.h" 

void steer(){
    int16_t rspeed, lspeed;
    bool forward = (rx_buffer[0] == 'F'); //checking if we go forward
    bool right = (rx_buffer[3] == 'R'); //checking if we go right
    uint16_t speed = (rx_buffer[1]-'0')*10 + (rx_buffer[2]-'0'); //getting the speed value out of buffer
    uint16_t steer = (rx_buffer[4]-'0')*10 + (rx_buffer[5]-'0'); //getting the steering value out of buffer

    bool rfwd = forward; //set directions
    bool lfwd = forward;

    if (right) { //if we go right
        lspeed = speed + steer; //left enginge must go faster
        rspeed = speed - steer; //right engine must go slower
        if (rspeed < 0) rfwd = !rfwd; //check if turning and set appropriate direction
    } else {
        lspeed = speed - steer; //left enginge must go slower
        rspeed = speed + steer; //right engine must go faster
        if (lspeed < 0) lfwd = !lfwd; //check if turning and set appropriate direction
    }

    if (rfwd){ //if right engine needs to go forward
        PTB->PSOR |= rforward_mask; //set direction
        PTB->PCOR |= rreverse_mask;
    } else {
        PTB->PCOR |= rforward_mask; 
        PTB->PSOR |= rreverse_mask;
    }

    if (lfwd){ //if left engine needs to go forward
        PTB->PSOR |= lforward_mask; //set direction
        PTB->PCOR |= lreverse_mask;
    } else { 
        PTB->PCOR |= lforward_mask; 
        PTB->PSOR |= lreverse_mask;
    }
    
    //right engine PWM - PTB5 -> TPM1_CH1
    TPM1->CONTROLS[1].CnV = abs(rspeed*26/100);
    //left engine PWM - PTA12 -> TPM0_CH3
    TPM1->CONTROLS[0].CnV = abs(lspeed*26/100);
}