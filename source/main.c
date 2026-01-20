#include "MKL05Z4.h"
#include "InitPWM.h"
#include "InitUART.h"
#include "InitLight.h"
#include "steering.h"
#include "light.h"
#include <string.h>
#include "InitPID.h"
#include "frdm_bsp.h" 
#include "i2c.h"
#include "PIDreg.h"



volatile char rx_buffer[RX_BUFFER_SIZE];
volatile uint8_t buff_index = 0;
volatile uint8_t message_ready = 0;
volatile uint8_t sekunda=0;
volatile uint8_t sekunda_OK=0;
volatile uint16_t lb_active=0;
volatile uint16_t rb_active=0;
volatile int32_t pro = 0;
volatile int32_t in = 0;
volatile int32_t dif = 0;
volatile int32_t gyro_error = 0;
//volatile uint8_t data[]={0,0};
volatile int16_t z = 0;
volatile uint8_t right=0;
volatile uint16_t speed=0;
volatile uint16_t steer=0;
volatile uint8_t steer_ext = 0;
volatile int16_t z1 = 0;
volatile uint8_t forward = 0;

int main(){
    InitPWM();
    InitUART();
    InitDrive();
		InitLight();
		InitPID();
		SysTick_Config(SystemCoreClock/10 );
    __enable_irq();

    while(1){
        if(message_ready == 1){
					if((rx_buffer[0] == 'F')||(rx_buffer[0] == 'B')||(rx_buffer[0] == 'Z')){
            steering();
					}else if(rx_buffer[0]-'0' < '5' || rx_buffer[0]== 'x'|| rx_buffer[0]== 'X'
											|| rx_buffer[0]== 'u'|| rx_buffer[0]== 'U'){
						light();
					}
            message_ready = 0;
						
            // buff_index = 0;
            // UART0->C2 |= UART0_C2_RIE_MASK;
        }
				PIDreg();
				if(!forward){
					if(right){
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
					
				}else{
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
				blinker();
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

void SysTick_Handler(void)	// Podprogram obs³ugi przerwania od SysTick'a
{ 
	sekunda+=1;				// Licz interwa³y równe 100ms
	if(sekunda==5)
	{
		sekunda=0;
		sekunda_OK=1;		// Daj znaæ, ¿e minê³a sekunda
	}
}
