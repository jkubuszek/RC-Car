#include "MKL05Z4.h"

#define rblink 11 //PTA11 
#define lblink 7 //PTA7 
#define frontbacklight 8 //PTB8
//#define lreverse 13 //PTB13

#define rblink_mask (1<<11) 
#define lblink_mask (1<<7) 
#define frontbacklight_mask (1<<8) 
//#define lreverse_mask (1<<13)

void InitLight(void);
