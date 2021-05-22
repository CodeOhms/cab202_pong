// #include "libopencm3/timing_libopencm3.h"
#include "timing.h"

uint16_t _prescaler = 0;

void timing_init_hardware(void)
{
    // Use prescaler of 4 to get a counter frequency of 18MHz:
	_prescaler = 4;
    TIM2_PSC = _prescaler - 1; // though really it is 4 bc there is a hidden +1
    timer_set_period(TIM2, 65535); // Overflow frequency of ~275Hz, period = 65535 +1
    TIM2_CR1 |= TIM_CR1_URS; // only trigger update interrupt upon overflow
    TIM2_DIER |= TIM_DIER_UIE; // UIE: update interrupt enable
    TIM2_EGR |= TIM_EGR_UG; // lock in timer settings
    // Enable counter:
    TIM2_CR1 |= TIM_CR1_CEN;

    /* Enable TIM2 interrupt. */
	nvic_enable_irq(NVIC_TIM2_IRQ);
}

// volatile uint16_t overflow_count = 0;
void tim2_isr(void)
{
    if(TIM2_SR & TIM_SR_UIF)
    { // update event triggered interrupt
	// Clear update event flag:
        TIM2_SR &= ~TIM_SR_UIF;

		for(uint8_t i = 0; i < _num_overflow_counters; ++i)
		{
			if(!_user_functions_enabled[i]) // Not enabled.
			{
				continue;
			}

			++(_overflow_counters[i]);

	// Check for timing trigger, if so run function:
			if(_overflow_counters[i] == 0)
			{ // No timing trigger, run each triggered interrupt
				(*_timer_user_functions[i])();
				// User function must manually reset its overflow counter in this case.
			}
			else if((_overflow_counters[i] * 65536 + TIM2_CNT) >= _time_limits[i])
			{
		// Call the associated function:
            	(*_timer_user_functions[i])();
		// Reset the counter:
            	_overflow_counters[i] = 0;
			}
		}
	}
}

uint16_t timing_get_prescaler()
{
	return _prescaler;
}

uint32_t calculate_elapsed_ticks(uint32_t overflow_count)
{
	return ( overflow_count * 65536 + TIM2_CNT );
}

uint32_t elapsed_ticks(uint8_t overflow_counter_index)
{
	return calculate_elapsed_ticks(_overflow_counters[overflow_counter_index]);
}

double calculate_ticks_to_time(uint32_t overflow_count)
{
	return elapsed_ticks(overflow_count) * ((double) _prescaler)/((double) F_CPU);
}

double ticks_to_time(uint8_t overflow_counter_index)
{
	return calculate_ticks_to_time(_overflow_counters[overflow_counter_index]);
}

uint32_t time_to_ticks(double time_ms)
{
    // Convert the milliseconds to seconds in formula!
    return (time_ms * 0.001) * ((double) F_CPU)/((double) _prescaler);
}