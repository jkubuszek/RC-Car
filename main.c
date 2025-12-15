#include "MKL05Z4.h"
#include "InitPWM.h"
#include "InitUART.h"
#include "steering.h"
#include <string.h>

volatile char rx_buffer[RX_BUFFER_SIZE];
volatile uint8_t buff_index = 0;
volatile uint8_t message_ready = 0;

int main(){
    InitPWM();
    InitUART();
    InitDrive();
    __enable_irq();

    while(1){
        if(message_ready == 1){
            steer();
            message_ready = 0; 
            // buff_index = 0;
            // UART0->C2 |= UART0_C2_RIE_MASK;
        }
    }
    return 0;
}

void UART0_IRQHandler(void) {

    uint32_t status = UART0->S1; //reading LPUART0 status flags

    if (status & (UART0_S1_OR_MASK | UART0_S1_NF_MASK | UART0_S1_FE_MASK | UART0_S1_PF_MASK)) {
        volatile uint8_t dummy = UART0->D; //removing trash from errors
        return; 
    }

    if (status & UART0_S1_RDRF_MASK) { //checking if a full byte arrived
        uint8_t received_byte = UART0->D; //storing received byte
            if (status & UART0_S1_RDRF_MASK) {
                uint8_t received_byte = UART0->D;
                if (received_byte == '\n') { 
                    message_ready = 1;

                    if (buff_index < RX_BUFFER_SIZE) {
                        rx_buffer[buff_index] = '\0'; 
                    }
                    
                    buff_index = 0;

                } else {
                    if (buff_index < (RX_BUFFER_SIZE - 1)) {
                        rx_buffer[buff_index] = received_byte;
                        buff_index++;
                    }
                }
        }
    }
}