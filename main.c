#include "MKL05Z4.h"
#include "InitPWM.h"
#include "InitUART.h"
#include "steering.h"
#include <string.h>




int main(){
    InitPWM();
    InitUART();
    InitDrive();
    while(1){
        //nop
    }
    return 0;
}

void LPUART0_IRQHandler(void) {

    uint32_t status = UART0->S1; //reading LPUART0 status flags

    if (status & LPUART_STAT_RDRF_MASK) { //checking if a full byte arrived
        uint8_t received_byte = UART0->D; //storing received byte
        if (!message_ready && (buff_index < RX_BUFFER_SIZE)) { //if not full message
            rx_buffer[buff_index] = received_byte; //store to buffer at correct index
            buff_index++;
            if (buff_index == RX_BUFFER_SIZE) { //if full message
                message_ready = true; 
                buff_index = 0; //reset index for new message
                UART0->C2 &= ~UART0_C2_RIE_MASK;	; //disable rx interrupts
            }
        }
    }

    if(message_ready){
        steer();
        UART0->C2 |= UART0_C2_RIE_MASK;	 //enable rx interrupts back again
    }



}