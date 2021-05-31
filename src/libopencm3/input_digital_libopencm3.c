#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "input_digital.h"

#define LEDPORT (GPIOB)
#define LEDPIN (GPIO15)

uint8_t _button_is_pressed = 0;

void input_digital_init(void)
{
    // Setup button pins as inputs with pull down resistors:
    // gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO0); // use external pull down
        // Use internal pull down:
    gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, GPIO0); // default to pull down resistor
    // GPIO_BSRR(GPIOA_ODR) = GPIO0; // Use set/reset register to enable pull up. Can use gpio_set also
	gpio_set(GPIOA, GPIO0);
}

void input_digital_button_debounce(void)
{
	const uint8_t button_mask = 0b11111; // retain 5 most recent samples of button state
    static uint8_t button_history = 0;
	uint8_t button_current_state = gpio_get(GPIOA, GPIO0);
	button_history = ((button_history<<1) & button_mask) | button_current_state;
	if(button_history == button_mask)
	{
		_button_is_pressed = 1;
        gpio_set(LEDPORT, LEDPIN);
	}
	else if(button_history == 0)
	{
		_button_is_pressed = 0;
        gpio_clear(LEDPORT, LEDPIN);
	}

	// Clear overflow counter for timer:
	timing_reset_overflow_counter(0);
}

uint8_t input_digital_read(void)
{ // TODO: update to use multiple buttons!
    return _button_is_pressed;
}