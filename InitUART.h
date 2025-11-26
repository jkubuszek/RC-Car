#include "MKL05Z4.h"
#define TX_pin 1 //PORTB1 = TX
#define RX_pin 2 //PORTB2 = RX

void InitUART(){
//SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; // Enable PORTB clock, RX and TX are there. this is already in InitPWM.c
PORTB->PCR[RX_pin] = PORT_PCR_MUX(2); //LPUART0_RX (MUX = 2)
PORTB->PCR[TX_pin] = PORT_PCR_MUX(2); //LPUART0_TX (MUX = 2)

SIM->SCGC4 |= SIM_SCGC4_LPUART0_MASK; //Enable LPUART0 clock
SIM->SOPT2 |= SIM_SOPT2_LPUART0SRC(1); //Set UART clock source = MCGFLLCLK=41943040Hz

LPUART0->CTRL &= ~(LPUART_CTRL_TE_MASK | LPUART_CTRL_RE_MASK); //Disable TX and RX for baud rate change
LPUART0->BAUD = LPUART_BAUD_SBR(312); //Set 9600 baud rate, SBR = f_clock/(OSR*baud_rate); OSR = 16 by default
LPUART0->CTRL = LPUART_CTRL_TE_MASK | LPUART_CTRL_RE_MASK; //Enable TX and RX back again

LPUART0->CTRL |= LPUART_CTRL_RDRFIE_MASK; //enable RX pin interrupt

NVIC_EnableIRQ(LPUART0_IRQn); //enable UART interrupts
}