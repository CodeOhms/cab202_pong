/*
 *  CAB202 Teensy Library (cab202_teensy)
 *	macros.h
 *
 *	B.Talbot, September 2015
 *	L.Buckingham, September 2017
 *  Luis Mejias, 21/04/2021 12:34:56 AM
 *  Last modified Zacharia Henderson, 18/05/2021 12:05 AM
 *  Queensland University of Technology
 */
#ifndef MACROS_H_
#define MACROS_H_

#ifdef   ENV_ARM
#include <libopencm3/stm32/gpio.h>
#endif //ENV_ARM

/*
 *  Setting data directions in a data direction register (DDR)
 */
#ifndef ENV_ARM
#define SET_INPUT(portddr, pin)			(portddr) &= ~(1 << (pin))
#define SET_OUTPUT(portddr, pin)		(portddr) |= (1 << (pin))
#else // ENV_ARM is true
#define SET_INPUT(portddr, pin)			gpio_set_mode(portddr, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, pin)
#define SET_OUTPUT(portddr, pin)		gpio_set_mode(portddr, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, pin)
#endif

/*
 *  Setting, clearing, and reading bits in registers.
 *	reg is the name of a register; pin is the index (0..7)
 *  of the bit to set, clear or read.
 *  (WRITE_BIT is a combination of CLEAR_BIT & SET_BIT)
 */
#ifndef ENV_ARM
#define SET_BIT(reg, pin)			(reg) |= (1 << (pin))
#define CLEAR_BIT(reg, pin)			(reg) &= ~(1 << (pin))
#define WRITE_BIT(reg, pin, value)	(reg) = (((reg) & ~(1 << (pin))) | ((value) << (pin)))
#define BIT_VALUE(reg, pin)			(((reg) >> (pin)) & 1)
#define BIT_IS_SET(reg, pin)		(BIT_VALUE((reg),(pin))==1)
#else // ENV_ARM is true
#define SET_BIT(reg, pin)			gpio_set(reg, pin)
#define CLEAR_BIT(reg, pin)			gpio_clear(reg, pin)
// If setting bit, don't shift, but shift left if clearing bit. See manual for more
#define WRITE_BIT(reg, pin, value)	value==1 ? SET_BIT(reg, pin) : CLEAR_BIT(reg, pin)
#define BIT_VALUE(reg, pin)			gpio_get(reg, pin)
#define BIT_IS_SET(reg, pin)		(BIT_VALUE((reg),(pin))==1)
#endif

/*
 *	Rudimentary math macros
 */
#define ABS(x) (((x) >= 0) ? (x) : -(x))
#define SIGN(x) (((x) > 0) - ((x) < 0))

#endif /* MACROS_H_ */
