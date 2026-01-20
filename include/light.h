#include "MKL05Z4.h"

#define RX_BUFFER_SIZE 32
extern volatile char rx_buffer[RX_BUFFER_SIZE]; //buffer 
extern volatile uint8_t buff_index; 
extern volatile uint8_t message_ready;
extern volatile uint8_t sekunda_OK;
extern volatile uint16_t lb_active;
extern volatile uint16_t rb_active;


void light(void);

void blinker(void);
