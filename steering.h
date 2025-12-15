#include "MKL05Z4.h"
#define RX_BUFFER_SIZE 10 

char rx_buffer[RX_BUFFER_SIZE]; //buffer 
uint8_t buff_index = 0; 
uint8_t message_ready = 0;

void steer(void);

