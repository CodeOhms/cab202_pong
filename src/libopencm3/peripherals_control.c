#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "peripherals_control.h"

void peripherals_control_init(void)
{
    // Setup clocks:
    rcc_clock_setup_in_hse_8mhz_out_72mhz();

    rcc_periph_clock_enable(RCC_GPIOC);

    // Enable clock for timer 2:
    RCC_APB1ENR |= RCC_APB1ENR_TIM2EN;
}