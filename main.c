#include "MKL05Z4.h"
#include "InitPWM.h"
#include "InitUART.h"
#include "steering.h"

#define RX_BUFFER_SIZE 10
volatile char rx_buffer[RX_BUFFER_SIZE];
volatile uint8_t rx_index = 0;

int main(){
    InitPWM();
    InitUART();
    InitDrive();
    


    return 0;
}

void LPUART0_IRQHandler(void) {
    


}