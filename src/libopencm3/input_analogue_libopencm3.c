#include "input_analogue.h"

uint16_t _adc_buff[ADC_BUFF_SIZE];


/* 
 * NOTE:
 * A peripheral DMA will disable the CPU if both are accessing the same destination address, so no race conditions
 * to deal with.
 */
static void input_analogue_adc_init(void)
{
	// Ensure the ADC is off to change the values:
	adc_power_off(ADC1);
	rcc_periph_reset_pulse(RST_ADC1);
	// Set prescaler, ADC clock must no exceed 14 MHz:
	rcc_set_adcpre(RCC_CFGR_ADCPRE_PCLK2_DIV8);
	// Using only one ADC peripheral, chose individual mode:
	adc_set_dual_mode(ADC_CR1_DUALMOD_IND);
	// Right aligned, values 0 - 4096 but effectively inverts the y axis:
	adc_set_right_aligned(ADC1);
	// Select channels to read analogue data:
	uint8_t channels[1] = { ADC_CHANNEL1 };
    adc_set_regular_sequence(ADC1, JOYSTICKS, channels);
	// Currently using only one joystick, disable scan mode:
	adc_disable_scan_mode(ADC1);
	// Using DMA, so require continous conversion mode:
	adc_set_continuous_conversion_mode(ADC1);
	// Set sampling time:
	adc_set_sample_time(ADC1, ADC_CHANNEL1, ADC_SMPR_SMP_1DOT5CYC);
	// :
	adc_enable_external_trigger_regular(ADC1, ADC_CR2_EXTSEL_SWSTART);
	// Enable DMA,
	// dma_enable_channel(DMA1, DMA_CHANNEL1);

	adc_enable_dma(ADC1);
	// Turn on ADC and give it about 3 microseconds to boot up:
	adc_power_on(ADC1);
	for (int i = 0; i < 800000; i++)
		{ __asm__("nop"); }
	// Calibrate the ADC for better accuracy:
	adc_reset_calibration(ADC1);
	adc_calibrate(ADC1);
}

static void input_analogue_dma_init(void)
{
	/*
	 * Procedure as listed in the data sheet, page 146 in the DMA functional description:
	 * 1. Set the peripheral register address in the DMA_CPARx register. The data will be
	 *    moved from/ to this address to/ from the memory after the peripheral event.
	 * 2. Set the memory address in the DMA_CMARx register. The data will be written to or
	 *    read from this memory after the peripheral event.
	 * 3. Configure the total number of data to be transferred in the DMA_CNDTRx register.
	 *    After each peripheral event, this value will be decremented.
	 * 4. Configure the channel priority using the PL[1:0] bits in the DMA_CCRx register.
	 * 5. Configure: a) data transfer direction, b) circular mode, c) peripheral & memory incremented
	 *    mode, d) peripheral & memory data size, e) and interrupt after half and/or full transfer in the
	 *    DMA_CCRx register.
	 * 6. Activate the channel by setting the ENABLE bit in the DMA_CCRx register.
	 */

	dma_set_read_from_peripheral(DMA1, DMA_CHANNEL1);
	// 1) Source address as the ADC peripheral:
	dma_set_peripheral_address(DMA1, DMA_CHANNEL1, (uint32_t) &ADC1_DR);
	// 2) Destination address, in SRAM, to store readings:
	dma_set_memory_address(DMA1, DMA_CHANNEL1, (uint32_t) _adc_buff);
	// 3) Specify the size, in bytes, of the array to copy into:
	dma_set_number_of_data(DMA1, DMA_CHANNEL1, ADC_BUFF_SIZE);
	// 4) Set channel priority:
	dma_set_priority(DMA1, DMA_CHANNEL1, DMA_CCR_PL_HIGH);
	// 5)
		// a) Transfer direction:
	dma_set_read_from_peripheral(DMA1, DMA_CHANNEL1);
		// b) Enable circular mode to fill the `_adc_buffer`, then start filling from the start once full:
	dma_enable_circular_mode(DMA1, DMA_CHANNEL1);
		// c) Enable memory increment mode to iterate through the `_adc_buff` array:
	dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL1);
		// d) Specify the size, in bytes, of each item in the buffer:
	dma_set_memory_size(DMA1, DMA_CHANNEL1, DMA_CCR_MSIZE_16BIT);
		// d) Specify the size, in bytes, of each reading from the ADC peripheral:
	dma_set_peripheral_size(DMA1, DMA_CHANNEL1, DMA_CCR_PSIZE_16BIT);
		// Currently only using a single joystick, so don't need peripheral increment mode.
		// e) Interrupts diabled by defualt.
}

void input_analogue_init(void)
{
	// Enable gpio for ADC:
	gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_ANALOG, GPIO1);
	
	// Prepare DMA to use with ADC:
	input_analogue_dma_init();

	// Prepare the ADC:
	input_analogue_adc_init();
}

void input_analogue_enable_reading(void)
{
	dma_enable_channel(DMA1, DMA_CHANNEL1);
	adc_start_conversion_regular(ADC1);
}

void input_analogue_read(uint16_t* joystick_readings)
{
	static uint8_t current_index = 0; // index of a reading for the 1st joystick
	for(uint8_t js = 0; js < JOYSTICKS; ++js)
	{
		joystick_readings[js] = _adc_buff[current_index + js];
	}
	current_index = (current_index + JOYSTICKS) % ADC_BUFF_SIZE;
}