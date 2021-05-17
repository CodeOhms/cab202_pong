#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

#include "peripherals_control.h"
#include "input_digital.h"
#include "timing.h"
// CAB202 libraries
#include <lcd.h>
#include <graphics.h>

#define RCCLEDPORT (RCC_GPIOC)
#define LEDPORT (GPIOC)
#define LEDPIN (GPIO13)
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

void blink(void);
void blink(void)
{
	static uint8_t button_history = 0;
	// static uint8_t button_is_pressed = 0;
	const uint8_t button_mask = 0b11111; // retain 5 most recent samples of button state
	uint8_t button_current_state = gpio_get(GPIOA, GPIO0);
	button_history = ((button_history<<1) & button_mask) | button_current_state;
	if(button_history == button_mask)
	{
		// button_is_pressed = 1;
		gpio_clear(GPIOC, GPIO13); // builtin LED is tied to Vcc, inversed logic
	}
	else if(button_history == 0)
	{
		// button_is_pressed = 0;
		gpio_set(GPIOC, GPIO13);
	}
}

int main(void)
{
	// Setup data
	double time_limits[] = { 0 };
	func_ptr_min_t timed_funcs[] = { blink };
	uint8_t timed_funcs_en[] = { 1 };

	// Enable MCU peripherals:
    peripherals_control_init();
	led_setup();
    input_digital_init();
    timing_init(1, time_limits, timed_funcs, timed_funcs_en);
	// Setup LCD:
	lcd_init(LCD_LOW_CONTRAST);
	clear_screen();
	char s[] = "Hello world!";
	draw_string(0, 10, s, FG_COLOUR);
	show_screen();
	while(1)
    {
    // Read input:
        // Buttons (digital):

        // Joysticks (analogue):

    // Interpret input:
        
    // Update entity models:

    // Update the screen:
    
    }

    // Only return if restarting.
        // Call shutdown functions:

    return 0;
}