#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

#include "timing.h"

void timing_init(void)
{
    // Setup clock:
    // rcc_clock_setup_in_hse_8mhz_out_72mhz();

	/* Enable TIM2 clock. */
	// rcc_periph_clock_enable(RCC_TIM2);
    // RCC_APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Use prescaler of 4 to get a counter frequency of 18MHz:
    TIM2_PSC = 3; // though really it is 4 bc there is a hidden +1
    timer_set_period(TIM2, 65535); // Overflow frequency of ~275Hz
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
        // ++overflow_count;
        // Clear update event flag:
        TIM2_SR &= ~TIM_SR_UIF;

		static uint8_t button_history = 0;
		static uint8_t button_is_pressed = 0;
		const uint8_t button_mask = 0b11111; // retain 5 most recent samples of button state
		uint8_t button_current_state = gpio_get(GPIOA, GPIO0);
		button_history = ((button_history<<1) & button_mask) | button_current_state;
		if(button_history == button_mask)
		{
			button_is_pressed = 1;
			// gpio_set(GPIOC, GPIO13); // builtin LED is tied to Vcc, inversed logic.
			gpio_clear(GPIOC, GPIO13);
		}
		else if(button_history == 0)
		{
			button_is_pressed = 0;
			// gpio_clear(GPIOC, GPIO13);
			gpio_set(GPIOC, GPIO13);
		}


		// if(overflow_count >= 275) // update roughly once per second
		// {
		//     overflow_count = 0;
		// 	gpio_toggle(GPIOC, GPIO13); // toggle internal LED
		// }
	}
}