#include "input_analogue.h"

uint8_t adc_buff[2];

void input_analogue_init(void)
{
    // Setup ADC:
    rcc_periph_clock_enable(RCC_ADC1);

    /* Make sure the ADC doesn't run during config. */
	adc_power_off(ADC1);

    // Using only one ADC peripheral, use independent mode:
    adc_set_dual_mode(ADC_CR1_DUALMOD_IND);
	// Continuously run ADC on two joysticks, requires scan mode:
    adc_enable_scan_mode(ADC1);
    adc_set_continuous_conversion_mode(ADC1);
    adc_disable_external_trigger_regular(ADC1);
    adc_set_left_aligned(ADC1);
        // Setup group/sequence of channels:
    uint8_t channels[ADC_CHANNELS_NUM] = { ADC_CHANNEL0 };
    adc_set_regular_sequence(ADC1, ADC_CHANNELS_NUM, channels);
    // Sample time:
    adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_1DOT5CYC);

    // Disable the temperature sensor:
    adc_disable_temperature_sensor();

	adc_power_on(ADC1);
    adc_enable_dma(ADC1);

	/* Wait for ADC starting up. */
	for (int i = 0; i < 800000; i++)    /* Wait a bit. */
		__asm__("nop");

	adc_reset_calibration(ADC1);
	adc_calibrate(ADC1);

    // Setup DMA to transfer ADC readings:
    rcc_periph_clock_enable(RCC_DMA1);

    /* MEM2MEM mode for channel 1. */
	dma_enable_mem2mem_mode(DMA1, DMA_CHANNEL1);

	/* Highest priority. */
	// dma_set_priority(DMA1, DMA_CHANNEL1, DMA_CCR_PL_VERY_HIGH);
    // Use default priority - low.

	/* 32Bit wide transfer for source and destination. */
	// dma_set_memory_size(DMA1, DMA_CHANNEL1, DMA_CCR_MSIZE_32BIT);
	// dma_set_peripheral_size(DMA1, DMA_CHANNEL1, DMA_CCR_PSIZE_32BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL1, DMA_CCR_MSIZE_8BIT);
	dma_set_peripheral_size(DMA1, DMA_CHANNEL1, DMA_CCR_PSIZE_8BIT);

	/*
	 * After every 32bits we have to increase the address because
	 * we use RAM.
	 */
	dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL1);
	dma_enable_peripheral_increment_mode(DMA1, DMA_CHANNEL1);

	/* We define the source as peripheral. */
	dma_set_read_from_peripheral(DMA1, DMA_CHANNEL1);

	/* We want to transfer string s1. */
	dma_set_peripheral_address(DMA1, DMA_CHANNEL1, ADC2_DR);

	/* Destination should be string s2. */
	dma_set_memory_address(DMA1, DMA_CHANNEL1, &adc_buff);

	/*
	 * Set number of DATA to transfer.
	 * Remember that this means not necessary bytes but MSIZE or PSIZE
	 * depending on your source device.
	 */
	dma_set_number_of_data(DMA1, DMA_CHANNEL1, 2);
}