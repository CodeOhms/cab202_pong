#include "common.h"
#include "timing.h"

volatile uint8_t _num_overflow_counters = 0;
volatile uint32_t* _overflow_counters = NULL;
volatile uint32_t* _time_limits  = NULL;
// volatile void (**_timer_user_functions)(void) = NULL;
volatile func_ptr_min_t* _timer_user_functions = NULL;
volatile uint8_t* _user_functions_enabled = NULL;

void interrupts_init_min(uint8_t num_overflow_counters)
{
    _num_overflow_counters = num_overflow_counters;

    // Allocate the arrays:
    _overflow_counters = malloc(num_overflow_counters * sizeof(uint32_t));
    _time_limits  = malloc(num_overflow_counters * sizeof(uint32_t));
    _timer_user_functions = malloc(num_overflow_counters * sizeof(func_ptr_min_t));
    _user_functions_enabled = malloc(num_overflow_counters * sizeof(uint8_t));

    // Initialise registers:
    timing_init_hardware();
}

void timing_init(uint8_t num_overflow_counters, double* time_limits,
				 func_ptr_min_t* timer_user_functions,
				 uint8_t* user_functions_enabled)
{
    interrupts_init_min(num_overflow_counters);

    // Copy the arrays:
    for(uint8_t i = 0; i < num_overflow_counters; ++i)
    {
        _timer_user_functions[i] = timer_user_functions[i];
        _user_functions_enabled[i] = user_functions_enabled[i];

    // Init counters to zero:
        _overflow_counters[i] = 0;

    // Convert time limits, in ms, to ticks:
        double prescaler_number = (double) timing_get_prescaler();
        // _time_limits[i] = time_to_ticks(time_limits[i], prescaler_number);
        _time_limits[i] = time_to_ticks(time_limits[i]);
    }
}

// uint32_t time_to_ticks(double time_ms, double timer_prescaler)
// {
//     // Convert the milliseconds to seconds in formula!
//     return (time_ms * 0.001) * ((double) F_CPU)/timer_prescaler;
// }

// double ticks_to_time_8bit(double timer_prescaler, uint8_t* tick_count_reg, uint32_t overflow_count)
// {
//     return ( overflow_count * 256 + *tick_count_reg ) * timer_prescaler/((double) F_CPU);
// }

// double ticks_to_time_16bit(double timer_prescaler, uint32_t* tick_count_reg, uint32_t overflow_count)
// {
//     return ( overflow_count * 65536 + *tick_count_reg ) * timer_prescaler/((double) F_CPU);
// }