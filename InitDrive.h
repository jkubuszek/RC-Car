#include "MKL05Z4.h"

#define rforward 10 //PTB10 
#define rreverse 11 //PTB11 
#define lforward 8 //PTB8
#define lreverse 13 //PTB13

#define rforward_mask (1<<10) 
#define rreverse_mask (1<<11) 
#define lforward_mask (1<<8) 
#define lreverse_mask (1<<13)

void InitDrive(void);

