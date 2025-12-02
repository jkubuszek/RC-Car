#include "MKL05Z4.h"
//right - PTB5 -> TPM1_CH1
struct r_engine{
    fwd = 0;
    bwd = 0;
    en = 0;  
};
//left - PTA12 -> TPM0_CH3
struct l_engine{
    fwd = 0;
    bwd = 0;
    en = 0;  
};

void steer(){
    int8_t rspeed, lspeed;
    bool forward = (rx_buffer[0] == 'F');
    bool right = (rx_buffer[3] == 'R');
    uint8_t speed = (rx_buffer[1]-'0')*10 + (rx_buffer[2]-'0');
    uint8_t steer = (rx_buffer[4]-'0')*10 + (rx_buffer[5]-'0');

    bool rfwd = forward;
    bool lfwd = forward;

    if (right) {
        lspeed = speed + steer;
        rspeed = speed - steer;
        if (rspeed < 0) rfwd = !rfwd;
    } else {
        lspd= speed - steer;
        rspeed = speed + steer;
        if (lspeed < 0) lfwd = !lfwd;
    }

    if (rfwd){
        r_engine.fwd = 1;
        r_engine.in2 = 0
    } else {
        r_engine.fwd = 0;
        r_engine.in2 = 1
    }

    if (lfwd){
        l_engine.fwd = 1;
        l_engine.in2 = 0
    } else { 
        l_engine.fwd = 0;
        l_engine.in2 = 1
    }
    
    //right - PTB5 -> TPM1_CH1
    TPM1->sCONTROLS[1].CnV = abs(rspeed*26/100);
    //left - PTA12 -> TPM0_CH3
    TPM0->CONTROLS[3].CnV = abs(lspeed*26/100);
    
}