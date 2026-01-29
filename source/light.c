#include "light.h"
#include "InitLight.h"
#include <stdlib.h>

void light(){
	switch (rx_buffer_copy[0]){
		case '1':
			if(lb_active && !rb_active){
				lb_active = 0;
				PTA->PCOR=lblink_mask;
			}else{
				lb_active = lblink_mask;
				rb_active = 0;
				sekunda_OK=1;
			}
			
		break;
		case 'U': //front and backlight on
			PTA->PSOR= frontbacklight_mask;
		break;
		case 'u': //front and backlight off
			PTA->PCOR= frontbacklight_mask;
		break;
		case '4':
			if(rb_active && !lb_active){
				rb_active = 0;
				PTA->PCOR=rblink_mask;
			}else{
				rb_active = rblink_mask;
				lb_active = 0;
			}
			sekunda_OK=1;
		break;
		case 'X':
			lb_active = lblink_mask;
			rb_active = rblink_mask;
		sekunda_OK=1;
		break;
		case 'x':
			lb_active = 0;
			rb_active = 0;
			PTA->PCOR=((lblink_mask) | (rblink_mask));
		break;
		default:
			break;
		
	}
	
}

void blinker(){
	if(sekunda_OK){
		PTA->PTOR=(lblink_mask & lb_active) | (rblink_mask & rb_active);
		if(!lb_active){
			PTA->PCOR=lblink_mask;
		}
		if(!rb_active){
			PTA->PCOR=rblink_mask;
		}
		sekunda_OK = 0;
	}
}
