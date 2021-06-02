#ifndef  TIMING_LIBOPENCM3_H
#define  TIMING_LIBOPENCM3_H

// #include <libopencm3/cm3/nvic.h>
// #include <libopencm3/stm32/rcc.h>
// #include <libopencm3/stm32/gpio.h>
// #include <libopencm3/stm32/timer.h>

#include "timing_common.h"

void timing_init_hardware(void);

uint16_t timing_get_prescaler(void);

uint32_t calculate_elapsed_ticks(uint32_t overflow_count);

uint32_t elapsed_ticks(uint8_t overflow_counter_index);

double calculate_ticks_to_time(uint32_t overflow_count);

double ticks_to_time(uint8_t overflow_counter_index);

uint32_t time_to_ticks(double time_ms);

#endif //TIMING_LIBOPENCM3_H