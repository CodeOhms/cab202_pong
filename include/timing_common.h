#ifndef  TIMING_COMMON_H
#define  TIMING_COMMON_H

#include "common.h"

extern volatile uint8_t _num_overflow_counters;
extern volatile uint32_t* _overflow_counters;
extern volatile uint32_t* _time_limits;
extern volatile func_ptr_min_t* _timer_user_functions;
extern volatile uint8_t* _user_functions_enabled;

#endif //TIMING_COMMON_H