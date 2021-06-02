#ifndef  INPUT_DIGITAL_LIBOPENCM3_H
#define  INPUT_DIGITAL_LIBOPENCM3_H

// #include <libopencm3/stm32/rcc.h>
// #include <libopencm3/stm32/gpio.h>

#include "common.h"

void input_digital_init(void);

void input_digital_button_debounce(void);

uint8_t input_digital_read(void);

void input_digital_flush(void);

#endif //INPUT_DIGITAL_LIBOPENCM3_H