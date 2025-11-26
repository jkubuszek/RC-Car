#include "MKL05Z4.h"
#include "InitPWM.h"
#include "InitUART.h"
#include "steering.h"

int main(){
    InitPWM();
    InitUART();
    //InitDrive(); in progress
    
    return 0;
}

void LPUART0_IRQHandler(void) {
//
}