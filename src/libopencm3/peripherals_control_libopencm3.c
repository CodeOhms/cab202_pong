#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/flash.h>

#include "peripherals_control.h"


void rcc_clock_setup_72mhz(void)
{
    /* Enable internal high-speed oscillator. */
	// rcc_osc_on(RCC_HSI);
    RCC_CR |= 1;
	// rcc_wait_for_osc_ready(RCC_HSI);
    while(!(RCC_CR & (1 << 1)));

	/* Select HSI as SYSCLK source. */
	// rcc_set_sysclk_source(RCC_CFGR_SW_SYSCLKSEL_HSICLK);
    RCC_CFGR &= ~(0b111 << 24);
    RCC_CFGR |= (0b101 << 24);

	/* Enable external high-speed oscillator 8MHz. */
	// rcc_osc_on(RCC_HSE);
    RCC_CR |= (1 << 16);
	// rcc_wait_for_osc_ready(RCC_HSE);
    while(!(RCC_CR & (1 << 17)));
	// rcc_set_sysclk_source(RCC_CFGR_SW_SYSCLKSEL_HSECLK);
    RCC_CFGR &= ~(0b111 << 24);
    RCC_CFGR |= (0b110 << 24);

	/*
	 * Set prescalers for AHB, ADC, APB1, APB2.
	 * Do this before touching the PLL (TODO: why?).
	 */
	// rcc_set_hpre(RCC_CFGR_HPRE_SYSCLK_NODIV);    /* Set. 72MHz Max. 72MHz */
    RCC_CFGR &= ~(0b1111 << 4);
	// rcc_set_ppre1(RCC_CFGR_PPRE1_HCLK_DIV2);     /* Set. 36MHz Max. 36MHz */
    RCC_CFGR &= ~(0b111 << 8);
    RCC_CFGR |= (0b100 << 8);
	// rcc_set_ppre2(RCC_CFGR_PPRE2_HCLK_NODIV);    /* Set. 72MHz Max. 72MHz */
    RCC_CFGR &= ~(0b111 << 11);

	/*
	 * Sysclk runs with 72MHz -> 2 waitstates.
	 * 0WS from 0-24MHz
	 * 1WS from 24-48MHz
	 * 2WS from 48-72MHz
	 */
	// flash_set_ws(0x02);
	FLASH_ACR &= ~(7);
	FLASH_ACR |= (0x02);

	/*
	 * Set the PLL multiplication factor to 9.
	 * 8MHz (external) * 9 (multiplier) = 72MHz
	 */
	// rcc_set_pll_multiplication_factor(RCC_CFGR_PLLMUL_PLL_CLK_MUL9);
    RCC_CFGR &= ~(0b1111 << 18);
    RCC_CFGR |= (0b111 << 18);

	/* Select HSE as PLL source. */
	// rcc_set_pll_source(RCC_CFGR_PLLSRC_HSE_CLK);
    RCC_CFGR |= (1 << 16);

	/*
	 * External frequency undivided before entering PLL
	 * (only valid/needed for HSE).
	 */
	// rcc_set_pllxtpre(RCC_CFGR_PLLXTPRE_HSE_CLK);
    RCC_CFGR &= ~(1 << 17);

	/* Enable PLL oscillator and wait for it to stabilize. */
	// rcc_osc_on(RCC_PLL);
    RCC_CR |= (1 << 24);
	// rcc_wait_for_osc_ready(RCC_PLL);
    while(!(RCC_CR & (1 << 25)));

	/* Select PLL as SYSCLK source. */
	// rcc_set_sysclk_source(RCC_CFGR_SW_SYSCLKSEL_PLLCLK);
    RCC_CFGR &= ~(0b111 << 24);
    RCC_CFGR |= (0b111 << 24);

	/* Set the peripheral clock frequencies used */
	rcc_ahb_frequency = 72000000;
	rcc_apb1_frequency = 36000000;
	rcc_apb2_frequency = 72000000;
}

void peripherals_control_init(void)
{
    // Setup clocks:
    // rcc_clock_setup_in_hse_8mhz_out_72mhz();
    rcc_clock_setup_72mhz();
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