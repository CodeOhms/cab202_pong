#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "peripherals_control.h"

void peripherals_control_init(void)
{
    // Setup clocks:
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
        // GPIO clocks:
    // rcc_periph_clock_enable(RCC_GPIOA);
    RCC_APB2ENR |= RCC_APB2ENR_IOPAEN;
    // rcc_periph_clock_enable(RCC_GPIOB);
    RCC_APB2ENR |= RCC_APB2ENR_IOPBEN;
        // Enable clock for timer 2:
    RCC_APB1ENR |= RCC_APB1ENR_TIM2EN;
        // Enable clock for timer 4:
    RCC_APB1ENR |= RCC_APB1ENR_TIM4EN;
        // ADC:
    // rcc_periph_clock_enable(RCC_ADC1);
    RCC_APB2ENR |= RCC_APB2ENR_ADC1EN;
        // DMA:
    // rcc_periph_clock_enable(RCC_DMA1);
    RCC_AHBENR |= RCC_AHBENR_DMA1EN;
        // USART:
    // rcc_periph_clock_enable(RCC_USART1);
    RCC_APB2ENR |= RCC_APB2ENR_USART1EN;
}