#ifndef  INPUT_ANALOGUE_LIBOPENCM3_H
#define  INPUT_ANALOGUE_LIBOPENCM3_H

// #include <libopencm3/stm32/rcc.h>
// #include <libopencm3/stm32/gpio.h>
// #include <libopencm3/stm32/adc.h>
// #include <libopencm3/stm32/dma.h>

#include "common.h"

void input_analogue_init(void);

void input_analogue_enable_reading(void);

void input_analogue_read(uint16_t* joystick_readings);

#endif //INPUT_ANALOGUE_LIBOPENCM3_H