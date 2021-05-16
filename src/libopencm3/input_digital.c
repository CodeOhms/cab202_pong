#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "input_digital.h"

void input_digital_init(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);

    // Setup button pins as inputs with pull down resistors:
    // gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO0); // use external pull down
        // Use internal pull down:
    gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, GPIO0); // default to pull down resistor
    // GPIO_BSRR(GPIOC_ODR) = (1<<0); // Use set/reset register to enable pull up. Can use gpio_set also
}