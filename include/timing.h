#ifndef  TIMING_H
#define  TIMING_H

#ifdef  ENV_ARM
#include "libopencm3/timing_libopencm3.h"
#endif //ARM

#include "timing_common.h"

void interrupts_init_min(uint8_t num_overflow_counters);

void timing_init(uint8_t num_overflow_counters, double* time_limits,
				 func_ptr_min_t* timer_user_functions,
				 uint8_t* user_functions_enabled);

// uint32_t time_to_ticks(double time_ms, double timer_prescaler);
// double ticks_to_time_8bit(double timer_prescaler, uint8_t* tick_count_reg, uint32_t overflow_count);
// double ticks_to_time_16bit(double timer_prescaler, uint32_t* tick_count_reg, uint32_t overflow_count);

#endif //TIMING_H