// #include "input_digital.h"

// int main()
// {
//     while(1)
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





/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
 * Copyright (C) 2011 Stephen Caudle <scaudle@doceme.com>
 * Copyright (C) 2012 Karl Palsson <karlp@tweak.net.au>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

#include "peripherals_control.h"
#include "input_digital.h"
#include "timing.h"

#define RCCLEDPORT (RCC_GPIOC)
#define LEDPORT (GPIOC)
#define LEDPIN (GPIO13)
#define GPIO_MODE_OUTPUT GPIO_MODE_OUTPUT_2_MHZ
#define GPIO_PUPD_NONE GPIO_CNF_OUTPUT_PUSHPULL

static void gpio_setup(void)
{
	/* Enable GPIO clock. */
	/* Using API functions: */
	rcc_periph_clock_enable(RCCLEDPORT);
	/* Set pin to 'output push-pull'. */
	/* Using API functions: */
#ifdef STM32F1
    gpio_set_mode(LEDPORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LEDPIN);
#else
	gpio_mode_setup(LEDPORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LEDPIN);
#endif
}

// static void timer_init(void)
// {
//     rcc_clock_setup_in_hse_8mhz_out_72mhz();

//     /* Enable TIM2 clock. */
// 	// rcc_periph_clock_enable(RCC_TIM2);
//     RCC_APB1ENR |= RCC_APB1ENR_TIM2EN;

//     // Use prescaler of 4 to get a counter frequency of 18MHz:
//     TIM2_PSC = 3; // though really it is 4 bc there is a hidden +1
//     timer_set_period(TIM2, 65535); // Overflow frequency of ~275Hz
//     TIM2_CR1 |= TIM_CR1_URS; // only trigger update interrupt upon overflow
//     TIM2_DIER |= TIM_DIER_UIE; // UIE: update interrupt enable
//     TIM2_EGR |= TIM_EGR_UG; // lock in timer settings
//     // Enable counter:
//     TIM2_CR1 |= TIM_CR1_CEN;

//     /* Enable TIM2 interrupt. */
// 	nvic_enable_irq(NVIC_TIM2_IRQ);
// }



int main(void)
{
	gpio_setup();
    peripherals_control_init();
    input_digital_init();
    // timer_init();
    timing_init();
	while (1) {
	}

	return 0;
}