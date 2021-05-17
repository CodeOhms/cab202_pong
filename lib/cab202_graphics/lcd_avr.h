#ifndef  LCD_AVR_H
#define  LCD_AVR_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

// What pins did we connect D/C and RST to
#define DCPIN		5   // PORTD
#define RSTPIN		6   // PORTD
#define DCPIN_PORT  PORTD
#define RSTPIN_PORT PORTD

// What pins are the SPI lines on
#define DINPIN		4   // PORTD
#define SCKPIN		3   // PORTD
#define SCEPIN		7   // PORTD
#define DINPIN_PORT PORTD
#define SCKPIN_PORT PORTD
#define SCEPIN_PORT PORTD

#endif //LCD_AVR_H