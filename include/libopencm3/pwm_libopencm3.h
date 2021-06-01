#ifndef  PWM_LIBOPENCM3_H
#define  PWM_LIBOPENCM3_H

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

void pwm_init(void);

void pwm_set_duty_cycle(float duty_cycle);

#endif //PWM_LIBOPENCM3_H