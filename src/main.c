#include <stdio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
// CAB202 libraries
#include <lcd.h>
#include <graphics.h>

#include "peripherals_control.h"
#include "input_digital.h"
#include "input_analogue.h"
#include "timing.h"
#include "pwm.h"
#include "pong.h"

#define RCCLEDPORT (RCC_GPIOB)
#define LEDPORT (GPIOB)
#define LEDPIN (GPIO15)
#define GPIO_MODE_OUTPUT GPIO_MODE_OUTPUT_2_MHZ
#define GPIO_PUPD_NONE GPIO_CNF_OUTPUT_PUSHPULL

static void led_setup(void)
{
#ifdef STM32F1
    gpio_set_mode(LEDPORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LEDPIN);
#else
	gpio_mode_setup(LEDPORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LEDPIN);
#endif
}

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
	led_setup();
	pwm_init();
    timing_init(1, time_limits, timed_funcs, timed_funcs_en);
	input_digital_init();
	input_analogue_init();
	input_analogue_enable_reading();
	// Setup LCD:
	lcd_init(73);
	clear_screen();
	// char s[] = "Hello world!";
	// draw_string(0, 0, s, FG_COLOUR);
	// show_screen();
	// while(1)
    // {
    // // Read input:
    //     // Buttons (digital):
	// 	button_states = input_digital_read();

	// 		// Joysticks (analogue):
	// 	input_analogue_read(joysticks);

	// 	// Interpret input:
	// 	char js_r[30];
	// 	// double inputVoltage = ((double) joysticks[0]) / 4096 * 3.3;
	// 	// sprintf(js_r, "Joystick 1 = %i", (uint8_t) inputVoltage);
	// 	sprintf(js_r, "Joystick 1 = %i", joysticks[0]);
	// 	clear_screen();
	// 	draw_string(0, 10, js_r, FG_COLOUR);
	// 	for (int i = 0; i < 9000000; i++)
	// 		{ __asm__("nop"); }
	// 	show_screen();

	// 	// Update entity models:

	// 	// Update the screen:
    
    // }
	pong();

    // Only return if restarting.
        // Call shutdown functions:

    return 0;
}