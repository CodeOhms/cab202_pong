#ifndef  LCD_ARM_H
#define  LCD_ARM_H

#include <libopencm3/stm32/gpio.h>

// What pins did we connect D/C and RST to
#define DCPIN		GPIO10   // PORTB
#define RSTPIN		GPIO14    // PORTB
#define DCPIN_PORT  GPIOB
#define RSTPIN_PORT GPIOB
// Libopencm3 uses same base address for targeting DDRD and PORT registers
#define DCPIN_DDRD  DCPIN_PORT
#define RSTPIN_DDRD RSTPIN_PORT

// What pins are the SPI lines on
#define DINPIN		GPIO11   // PORTB
#define SCKPIN		GPIO12   // PORTB
#define SCEPIN		GPIO13    // PORTB
#define DINPIN_PORT GPIOB
#define SCKPIN_PORT GPIOB
#define SCEPIN_PORT GPIOB
#define DINPIN_DDRD DINPIN_PORT
#define SCKPIN_DDRD SCKPIN_PORT
#define SCEPIN_DDRD SCEPIN_PORT

#endif //LCD_ARM_H