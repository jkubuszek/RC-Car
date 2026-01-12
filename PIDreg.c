#include "PIDreg.h"
#include "i2c.h"
#include "stdio.h"
#include "InitLight.h"

void PIDreg(void)
{
		if(steer_ext){
			int pid = 0;
			uint8_t data[]={0,0};
			I2C_ReadRegBlock(0x68, 0x47, 3, data);
			z = data[0]<<8 | data[1];
			z = z - gyro_error;
			pro = P*z;
			in += I*z;
			dif -= Df*z;
			pid = pro+in+dif;
			right = (pid < 0);
			pid=pid<<1;
			pid=pid>>1;
			steer = pid/128;
			
			if(right){
				PTA->PSOR=(rblink_mask);
				PTA->PCOR=(lblink_mask);
			}
			else{
				PTA->PSOR=(lblink_mask);
				PTA->PCOR=(rblink_mask);
			}
			
		}else{
			pro = 0;
			in += 0;
			dif -= 0;
		}

		
}
	
