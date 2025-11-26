#include "MKL05Z4.h"
#define rspd
#define lspd

void InitPWM()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;		// Enabling port B clock
											
	PORTB->PCR[rspd] |= PORT_PCR_MUX(2);
	PORTB->PCR[lspd] |= PORT_PCR_MUX(2);	// Enabling right and left speed control pins as PWM
	
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;		// Enabling TMP0 clock
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);		// clock source = TPMx MCGFLLCLK=41943040Hz
	
	TPM0->SC &= ~TPM_SC_CPWMS_MASK;		//	TPM0 counting forwards
	TPM0->SC |= TPM_SC_PS(6);	//	clock divider = 64; clock=655360Hz
	TPM0->MOD = 25;		//	 MODULO=25 - f_pwm=25kHz (we need 25kHz to eliminate irritating sounds the car may make)
	
	TPM0->CONTROLS[3].CnSC = TPM_CnSC_MSB_MASK|TPM_CnSC_ELSA_MASK;	//	TPM0 - Edge-aligned PWM Low-true pulses (set Output on match, clear Output on reload)
	TPM0->CONTROLS[3].CnV = 0x0000;					// fill factor = 0
	TPM0->SC |= TPM_SC_CMOD(1);						// Enable TPM0
}
