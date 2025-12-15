#include "steering.h"
#include "InitDrive.h"
#include <stdlib.h>

void steer(){
    uint8_t stop = (rx_buffer[0] == 'Z'); //checking if we stop
    uint8_t forward = (rx_buffer[0] == 'F'); //checking if we go forward
    uint8_t right = (rx_buffer[3] == 'R'); //checking if we go right
    uint16_t speed = (rx_buffer[1]-'0')*10 + (rx_buffer[2]-'0'); //getting the speed value out of buffer
    uint16_t steer = (rx_buffer[4]-'0')*10 + (rx_buffer[5]-'0'); //getting the steering value out of buffer
			
		if(forward){
			PTB->PCOR = rforward_mask;
			PTB->PSOR =	rreverse_mask;
			PTB->PCOR = lforward_mask;
			PTB->PSOR =	lreverse_mask;	
		}else{
			PTB->PSOR = rforward_mask;
			PTB->PCOR =	rreverse_mask;
			PTB->PSOR = lforward_mask;
			PTB->PCOR =	lreverse_mask;
		}
		if (stop == 1){
        speed = 0;
    }
		if(!right){
			//right engine PWM - PTB5 -> TPM1_CH1
			TPM1->CONTROLS[1].CnV = speed*1667/100;
			//left engine PWM - PTA12 -> TPM1_CH0
			TPM1->CONTROLS[0].CnV = speed*(60-steer)*1667/600;
		}else{
			//right engine PWM - PTB5 -> TPM1_CH1
			TPM1->CONTROLS[1].CnV = speed*(60-steer)*1667/600;
			//left engine PWM - PTA12 -> TPM1_CH0
			TPM1->CONTROLS[0].CnV = speed*1667/100;
		}
    

    
    
}