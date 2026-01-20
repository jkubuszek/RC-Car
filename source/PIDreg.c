#include "PIDreg.h"
#include "i2c.h"
#include "stdio.h"
#include "InitLight.h"

void PIDreg(void)
{
		if(steer_ext){
			//function variables
			int16_t pid = 0;
			uint8_t data[]={0,0};
			//gryoskope Z get data
			I2C_ReadRegBlock(0x68, 0x47, 3, data);
			//data change to int 16
			z = (int16_t)((data[0] << 8) | data[1]);
			//usuniecie offsetu
			z = z - gyro_error;
			//proportional calculate
			pro = P*z;
			//Integral calculate
			in += I*z;
			//Differential calculate
			dif = Df*(z1-z);
			z1=z;
			pid = pro+in+dif;
			right = (pid < 0);
			pid=(pid < 0) ? -pid : pid;
			pid=(pid > 60) ? 60 : pid;
			steer = pid;
				//this NOP() -s was used to balancing cycle time missing leds below. Led was used to set PID coefficients
			__NOP();
			__NOP();
			__NOP();
			__NOP();
			__NOP();
			__NOP();
			/* section to tests
			if(right){
				PTA->PSOR=(rblink_mask);
				PTA->PCOR=(lblink_mask);
			}
			else{
				PTA->PSOR=(lblink_mask);
				PTA->PCOR=(rblink_mask);
			}
			*/
			
		}else{
			pro = 0;
			in = 0;
			dif = 0;
			z1=0;
			
		}

		
}
	
