// #include <libopencm3/cm3/nvic.h>
// #include <libopencm3/stm32/rcc.h>
// #include <libopencm3/stm32/gpio.h>
// #include <libopencm3/stm32/timer.h>

// #include "peripherals_control.h"
// #include "input_digital.h"
// #include "timing.h"
// // CAB202 libraries
// #include <lcd.h>
// #include <graphics.h>

// #define RCCLEDPORT (RCC_GPIOA)
// #define LEDPORT (GPIOB)
// #define LEDPIN (GPIO12)
// #define GPIO_MODE_OUTPUT GPIO_MODE_OUTPUT_2_MHZ
// #define GPIO_PUPD_NONE GPIO_CNF_OUTPUT_PUSHPULL

// static void led_setup(void)
// {
// #ifdef STM32F1
//     gpio_set_mode(LEDPORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LEDPIN);
// #else
// 	gpio_mode_setup(LEDPORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LEDPIN);
// #endif
// }

// // #define SET_BIT(reg, pin)			gpio_set(reg, pin)
// // #define CLEAR_BIT(reg, pin)			gpio_clear(reg, pin)
// // #define WRITE_BIT(reg, pin, value)	value==1 ? SET_BIT(reg, pin) : CLEAR_BIT(reg, pin)
// void blink(void);
// void blink(void)
// {
// 	static uint8_t button_history = 0;
// 	// static uint8_t button_is_pressed = 0;
// 	const uint8_t button_mask = 0b11111; // retain 5 most recent samples of button state
// 	uint8_t button_current_state = gpio_get(GPIOA, GPIO0);
// 	button_history = ((button_history<<1) & button_mask) | button_current_state;
// 	if(button_history == button_mask)
// 	{
// 		// button_is_pressed = 1;
// 		gpio_clear(LEDPORT, LEDPIN); // builtin LED is tied to Vcc, inversed logic
// 		// WRITE_BIT(LEDPORT, LEDPIN, 0);
// 	}
// 	else if(button_history == 0)
// 	{
// 		// button_is_pressed = 0;
// 		gpio_set(LEDPORT, LEDPIN);
// 		// WRITE_BIT(LEDPORT, LEDPIN, 1);
// 	}
// }

// int main(void)
// {
// 	// Setup data
// 	double time_limits[] = { 0 };
// 	func_ptr_min_t timed_funcs[] = { blink };
// 	uint8_t timed_funcs_en[] = { 1 };

// 	// Enable MCU peripherals:
//     peripherals_control_init();
// 	led_setup();
//     input_digital_init();
//     timing_init(1, time_limits, timed_funcs, timed_funcs_en);
// 	// Setup LCD:
// 	lcd_init(LCD_HIGH_CONTRAST);
// 	clear_screen();
// 	char s[] = "Hello world!";
// 	draw_string(0, 10, s, FG_COLOUR);
// 	show_screen();
// 	while(1)
//     {
//     // Read input:
//         // Buttons (digital):

//         // Joysticks (analogue):

//     // Interpret input:
        
//     // Update entity models:

//     // Update the screen:
    
//     }

//     // Only return if restarting.
//         // Call shutdown functions:

//     return 0;
// }







#include <stdint.h>
#include <stdio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
 
#include <graphics.h>
#include <macros.h>
 
#include "lcd_model.h"
 
void new_lcd_init(uint8_t contrast) {
    // Set up the pins connected to the LCD as outputs
    SET_OUTPUT(GPIOB, SCEPIN); // Chip select -- when low, tells LCD we're sending data
	// gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_OPENDRAIN, SCEPIN);
    SET_OUTPUT(GPIOB, RSTPIN); // Chip Reset
    SET_OUTPUT(GPIOB, DCPIN);  // Data / Command selector
    SET_OUTPUT(GPIOB, DINPIN); // Data input to LCD
    SET_OUTPUT(GPIOB, SCKPIN); // Clock input to LCD
 
    CLEAR_BIT(GPIOB, RSTPIN); // Reset LCD
    SET_BIT(GPIOB, SCEPIN);   // Tell LCD we're not sending data.
    SET_BIT(GPIOB, RSTPIN);   // Stop resetting LCD
 
    LCD_CMD(lcd_set_function, lcd_instr_extended);
    LCD_CMD(lcd_set_contrast, contrast);
    LCD_CMD(lcd_set_temp_coeff, 0);
    LCD_CMD(lcd_set_bias, 3);
 
    LCD_CMD(lcd_set_function, lcd_instr_basic);
    LCD_CMD(lcd_set_display_mode, lcd_display_normal);
    LCD_CMD(lcd_set_x_addr, 0);
    LCD_CMD(lcd_set_y_addr, 0);
}
 
void setup(void) {
     
    new_lcd_init(LCD_DEFAULT_CONTRAST);
    clear_screen();
    draw_string( 10, 10, "Hello Cab202!", FG_COLOUR );
    show_screen();
}
 
char buffer[10];
 
void draw_int(uint8_t x, uint8_t y, int t) {
    snprintf( buffer, 10, "%d", t );
    draw_string( x, y, buffer, FG_COLOUR );
}
 
void process(void) {
    static uint8_t contrast = 0;
    contrast ++;
    if ( contrast > 127 ) contrast = 0;
     
    draw_string( 10, 20, "         ", FG_COLOUR );
    draw_int( 10, 20, contrast );
    show_screen();
     
    LCD_CMD( lcd_set_function, lcd_instr_extended );
    LCD_CMD( lcd_set_contrast, contrast );
    LCD_CMD( lcd_set_function, lcd_instr_basic );
}
 
int main(void) {
	rcc_clock_setup_in_hse_8mhz_out_72mhz();
	rcc_periph_clock_enable(RCC_GPIOB);
    setup();
 
    for ( ;; ) {
        process();
        // _delay_ms(50);
		for (int i = 0; i < 500000; i++) {	/* Wait a bit. */
			__asm__("nop");
		}
    }
}