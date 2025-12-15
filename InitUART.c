#include "InitUART.h"

void InitPWM()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;		// Enabling port B clock
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;		// Enabling port A clock

	PORTB->PCR[rspd] |= PORT_PCR_MUX(2);
	PORTA->PCR[lspd] |= PORT_PCR_MUX(2);	// Enabling right and left speed control pins as PWM
	
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;		// Enabling TMP1 clock
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);		// clock source = TPMx MCGFLLCLK=41943040Hz
	
	TPM1->SC &= ~TPM_SC_CPWMS_MASK;		//	TPM1 counting forwards
	TPM1->SC |= TPM_SC_PS(6);	//	clock divider = 64; clock=655360Hz
	TPM1->MOD = 25;		//	 MODULO=25 - f_pwm=25kHz (we need 25kHz to eliminate irritating sounds the car may make)

	//right engine
	TPM1->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK|TPM_CnSC_ELSA_MASK;	//	TPM1 - Edge-aligned PWM Low-true pulses (set Output on match, clear Output on reload)
	TPM1->CONTROLS[1].CnV = 0x0000;					// fill factor = 0

	//left engine
	TPM1->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK|TPM_CnSC_ELSA_MASK;	//	TPM1 - Edge-aligned PWM Low-true pulses (set Output on match, clear Output on reload)
	TPM1->CONTROLS[0].CnV = 0x0000;					// fill factor = 0

	TPM1->SC |= TPM_SC_CMOD(1);						// Enable TPM1
}