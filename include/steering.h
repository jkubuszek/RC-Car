#include "MKL05Z4.h"

#define RX_BUFFER_SIZE 32
extern volatile char rx_buffer[RX_BUFFER_SIZE]; //buffer 
extern volatile uint8_t buff_index; 
extern volatile uint8_t message_ready;
extern volatile uint8_t right;
extern volatile uint16_t speed;
extern volatile uint16_t steer;
extern volatile uint8_t steer_ext;
extern volatile uint8_t forward;

void steering(void);

