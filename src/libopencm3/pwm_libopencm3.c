#include "libopencm3/pwm_libopencm3.h"

void pwm_init(void)
{
    // Set gpio pin PB5 as output:
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO9);

    // Output compare enable:
    TIM4_CCER |= TIM_CCER_CC4E;
    // Enable auto-reload preload register:
    TIM4_CR1 |= TIM_CR1_ARPE;
    // Choose pwm mode 1:
    TIM4_CCMR2 |= TIM_CCMR2_OC4M_PWM1;
    // Output compare preload enable:
    TIM4_CCMR2 |= TIM_CCMR2_OC4PE;
    // Set prescaler:
    TIM4_PSC = 3; // actually 4, hidden +1
    // Set maximum pwm value:
    TIM4_ARR = 255;
    // Initialise duty cycle to 0%:
    TIM4_CCR2 = 0;
    // Lock in timer settings
    TIM4_EGR |= TIM_EGR_UG;
    // Enable counter:
    TIM4_CR1 |= TIM_CR1_CEN;
}

void pwm_set_duty_cycle(float duty_cycle)
{
    if(0 <= duty_cycle && duty_cycle <= 100)
    {
        TIM4_CCR4 = (uint16_t) (duty_cycle * 2.55);
    }
}