#include "MKL05Z4.h"
#include "InitPWM.h"
#include "InitUART.h"
#include "steering.h"
#include <string.h>
#include <stdbool.h>



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

    uint32_t status = LPUART0->STAT; //reading LPUART0 status flags

    if (status & LPUART_STAT_RDRF_MASK) { //checking if a full byte arrived
        uint8_t received_byte = LPUART0->DATA; //storing received byte
        if (!message_ready && (buff_index < RX_BUFFER_SIZE)) { //if not full message
            rx_buffer[buff_index] = received_byte; //store to buffer at correct index
            buff_index++;
            if (buff_index == RX_BUFFER_SIZE) { //if full message
                message_ready = true; 
                buff_index = 0; //reset index for new message
                LPUART0->CTRL &= ~LPUART_CTRL_RIE_MASK; //disable rx interrupts
            }
        }
    }

    if(message_ready){
        steer();
        LPUART0->CTRL |= LPUART_CTRL_RIE_MASK; //enable rx interrupts back again
    }



}