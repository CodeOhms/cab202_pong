#ifndef  SERIAL_COMM_LIBOPENCM3_H
#define  SERIAL_COMM_LIBOPENCM3_H

// #include <libopencm3/stm32/gpio.h>
// #include <libopencm3/stm32/usart.h>
#include "common.h"

void serial_comm_init(void);

void serial_comm_send(char* string, size_t size);

#endif //SERIAL_COMM_LIBOPENCM3_H