#include "serial_comm.h"

void serial_comm_init(void)
{
    // PA9 -> TX1, PA10 -> RX1
    /* Setup GPIO pin GPIO_USART1_TX. */
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ,
		      GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART1_TX);

    /* Setup UART parameters. */
	usart_set_baudrate(USART1, 115200);
	usart_set_databits(USART1, 8);
	usart_set_stopbits(USART1, USART_STOPBITS_1);
	usart_set_mode(USART1, USART_MODE_TX);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);

	/* Finally enable the USART. */
	usart_enable(USART1);
}

#define USART_FR(x)             MMIO32((x) + 0x0018)
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