#ifndef  LCD_ARM_H
#define  LCD_ARM_H

// #include <libopencm3/stm32/gpio.h>

#define GPIO_PORT_B_BASE		        (PERIPH_BASE_APB2 + 0x0c00)
#define GPIOB

// What pins did we connect D/C and RST to
#define DCPIN		(1 << 10)   // PORTB
#define RSTPIN		(1 <<12)    // PORTB
#define DCPIN_PORT  GPIOB
#define RSTPIN_PORT GPIOB
// Libopencm3 uses same base address for targeting DDRD and PORT registers
#define DCPIN_DDRD  DCPIN_PORT
#define RSTPIN_DDRD RSTPIN_PORT

// What pins are the SPI lines on
#define DINPIN		(1 << 1)   // PORTB
#define SCKPIN		(1 << 0)   // PORTB
#define SCEPIN		(1 << 11)    // PORTB
#define DINPIN_PORT GPIOB
#define SCKPIN_PORT GPIOB
#define SCEPIN_PORT GPIOB
#define DINPIN_DDRD DINPIN_PORT
#define SCKPIN_DDRD SCKPIN_PORT
#define SCEPIN_DDRD SCEPIN_PORT

#endif //LCD_ARM_H