#include <stdio.h>
// #include <libopencm3/cm3/nvic.h>
// #include <libopencm3/stm32/rcc.h>
// #include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
// CAB202 libraries
#include <lcd.h>
#include <graphics.h>

#include "common.h"
#include "peripherals_control.h"
#include "input_digital.h"
#include "input_analogue.h"
#include "timing.h"
#include "pwm.h"
#include "serial_comm.h"
#include "pong.h"

int main(void)
{
	// Setup data:
		// Game data:
	// uint16_t joysticks[JOYSTICKS];
	uint8_t button_states = 0;
		// Hardware data:
	double time_limits[] = { 0 };
	func_ptr_min_t timed_funcs[] = { input_digital_button_debounce };
	uint8_t timed_funcs_en[] = { 1 };

	// Enable MCU peripherals:
    peripherals_control_init();
	serial_comm_init();
	pwm_init();
    timing_init(1, time_limits, timed_funcs, timed_funcs_en);
	input_digital_init();
	input_analogue_init();
	input_analogue_enable_reading();
	// Setup LCD:
	lcd_init(73);
	clear_screen();
	pong();

    // Only return if restarting.
        // Call shutdown functions:

    return 0;
}