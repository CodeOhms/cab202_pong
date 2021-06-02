#include "libopencm3/pwm_libopencm3.h"

void pwm_init(void)
{
    // Set gpio pin PB5 as output:
    // gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO9);
    GPIOB_CRH &= ~((3 << 6)|(3 << 4));
    GPIOB_CRH |= (2 << 6)|(2 << 4);

    // Output compare enable:
    TIM4_CCER |= (1 << 12);
    // Enable auto-reload preload register:
    TIM4_CR1 |= (1 << 7);
    // Choose pwm mode 1:
    TIM4_CCMR2 |= (0x6 << 12);
    // Output compare preload enable:
    TIM4_CCMR2 |= (1 << 11);
    // Set prescaler:
    TIM4_PSC = 3; // actually 4, hidden +1
    // Set maximum pwm value:
    TIM4_ARR = 255;
    // Initialise duty cycle to 0%:
    TIM4_CCR2 = 0;
    // Lock in timer settings
    TIM4_EGR |= (1 << 0);
    // Enable counter:
    TIM4_CR1 |= (1 << 0);
}

void pwm_set_duty_cycle(float duty_cycle)
{
    if(0 <= duty_cycle && duty_cycle <= 100)
    {
        TIM4_CCR4 = (uint16_t) (duty_cycle * 2.55);
    }
}