#include "steering.h"
#include "InitDrive.h"
#include <stdlib.h>

void steering(){
    uint8_t stop = (rx_buffer_copy[0] == 'Z'); //checking if we stop
    forward = (rx_buffer_copy[0] == 'F'); //checking if we go forward
    right = (rx_buffer_copy[3] == 'R'); //checking if we go right
    speed = (rx_buffer_copy[1]-'0')*10 + (rx_buffer_copy[2]-'0'); //getting the speed value out of buffer
    steer = (rx_buffer_copy[4]-'0')*10 + (rx_buffer_copy[5]-'0'); //getting the steering value out of buffer
				
		if(steer == 0){
			steer_ext = 1;
		}else{
			steer_ext = 0;}
	
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
		
    

    
    
}
