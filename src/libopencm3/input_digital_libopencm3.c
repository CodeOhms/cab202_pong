// #include <libopencm3/stm32/rcc.h>
// #include <libopencm3/stm32/gpio.h>

#include "input_digital.h"

const uint8_t button_mask = 0b11111;
uint8_t button_history = 0;
uint8_t button_current_state = 0;
uint8_t _button_is_pressed = 0;

void input_digital_init(void)
{
    // Setup button pins as inputs with pull down resistors:
    // gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, GPIO0);
	GPIOA_CRL &= ~(0b1111);
	GPIOA_CRL |= (1 << 3);
		// Use internal pull up:
	// gpio_set(GPIOA, GPIO0);
	GPIOA_BSRR = 1;
}

void input_digital_button_debounce(void)
{
	// button_current_state = ~(gpio_get(GPIOA, GPIO0)) & 1; // inversed logic due to pull up!
	button_current_state = ~(GPIOA_IDR & 1) & 1;
	button_history = ((button_history<<1) & button_mask) | button_current_state;
	if(button_history == button_mask)
	{
		_button_is_pressed = 1;
	}
	else if(button_history == 0)
	{
		_button_is_pressed = 0;
	}

	// Clear overflow counter for timer:
	timing_reset_overflow_counter(0);
}

uint8_t input_digital_read(void)
{ // TODO: update to use multiple buttons!
    return _button_is_pressed;
}

void input_digital_flush(void)
{
	button_current_state = 0;
	button_history = 0;
	_button_is_pressed = 0;
}