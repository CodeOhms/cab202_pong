#ifndef  LCD_ARM_H
#define  LCD_ARM_H

#include <libopencm3/stm32/gpio.h>

// What pins did we connect D/C and RST to
#define DCPIN		2   // PORTA
#define RSTPIN		0   // PORTA
#define DCPIN_PORT  GPIOA
#define RSTPIN_PORT GPIOA
// Libopencm3 uses same base address for targeting DDRD and PORT registers
#define DCPIN_DDRD  DCPIN_PORT
#define RSTPIN_DDRD RSTPIN_PORT

// What pins are the SPI lines on
#define DINPIN		4   // PORTA
#define SCKPIN		5   // PORTA
#define SCEPIN		1   // PORTA
#define DINPIN_PORT GPIOA
#define SCKPIN_PORT GPIOA
#define SCEPIN_PORT GPIOA
#define DINPIN_DDRD DINPIN_PORT
#define SCKPIN_DDRD SCKPIN_PORT
#define SCEPIN_DDRD SCEPIN_PORT

#endif //LCD_ARM_H