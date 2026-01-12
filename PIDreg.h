#include "MKL05Z4.h"

#define P 10
#define I 0
#define Df 0

extern volatile int32_t pro;
extern volatile int32_t in;
extern volatile int32_t dif;
//extern volatile uint8_t data[];
extern volatile int16_t z;
extern volatile int32_t gyro_error;
extern volatile uint8_t right;
extern volatile uint16_t steer;
extern volatile uint8_t steer_ext;


void PIDreg(void);
