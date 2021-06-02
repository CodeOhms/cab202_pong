#include "serial_comm.h"

void serial_comm_init(void)
{
    // PA9 -> TX1, PA10 -> RX1
    // Setup GPIO pin GPIO_USART1_TX.
	// gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART1_TX);
	GPIOA_CRH &= ~(0b1111 << 4);
	GPIOA_CRH |= (2 << 6)|(3 << 4);
	

    // Setup UART parameters.
	// usart_set_baudrate(USART1, 115200);
	USART1_BRR = F_CPU/115200;
	// usart_set_databits(USART1, 8);
	USART1_CR1 &= ~(1 << 12);
	// usart_set_stopbits(USART1, USART_STOPBITS_1);
	USART1_CR2 = (USART1_CR2 & (3 << 12)) | (0x00 << 12);
	// usart_set_mode(USART1, USART_MODE_TX);
	USART1_CR1 = (USART1_CR1 & ~((1 << 2) | (1 << 3))) | (1 << 3);
	// usart_set_parity(USART1, USART_PARITY_NONE);
	USART1_CR1 &= ~(1 << 10|1 << 9);
	// usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
	USART1_CR3 = (USART1_CR3 & ~((1 << 8) | (1 << 9))) | 0;

	// Finally enable the USART.
	// usart_enable(USART1);
	USART1_CR1 |= (1 << 13)|(1 << 3)|(1 << 2);
}

void serial_comm_send(char* string, size_t size)
{
	for(uint16_t i = 0; i < size; ++i)
	{
		if(string[i] == '\0')
		{
			break;
		}
		// usart_send_blocking(USART1, string[i]);
		while ( !(USART1_SR & (1 << 6)) );
		USART1_DR = string[i];
	}
}