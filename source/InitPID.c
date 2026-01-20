#include "InitPID.h"
#include "frdm_bsp.h" 
#include "i2c.h"
#include "stdio.h"

#define adres 0x68

void InitPID(void){
	
	I2C_Init(); //init I2C
	if(I2C_Ping(adres)){PTA->PTOR |=(1<<7);}
	I2C_WriteReg(adres , 0x6B, 0x01); // power on gyroscope module
	I2C_WriteReg(adres , 0x1B, 0x00); // set precision
	I2C_WriteReg(adres , 0x1A, 0x03); // set LPF
	uint8_t data[]={0,0};
	for(int j=0; j<=1024; j++){
		I2C_ReadRegBlock(adres, 0x47, 3, data);
		z = (int16_t)((data[0] << 8) | data[1]);
		gyro_error += z;
		DELAY(1)
		if(z){PTA->PSOR |=(1<<7);}
	}
	gyro_error /= 1024;
	PTA->PCOR |=(1<<7);
	
}
