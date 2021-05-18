#ifndef  INPUT_ANALOGUE_LIBOPENCM3_H
#define  INPUT_ANALOGUE_LIBOPENCM3_H

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/dma.h>

#include "common.h"

void input_analogue_init(void);

#endif //INPUT_ANALOGUE_LIBOPENCM3_H