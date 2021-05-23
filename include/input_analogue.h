#ifndef  INPUT_ANALOGUE_H
#define  INPUT_ANALOGUE_H

#ifdef  ENV_ARM
#include "libopencm3/input_analogue_libopencm3.h"
#endif //ARM

#define JOYSTICKS 1
#define J1_DEADZONE 50
#define ADC_BUFF_SIZE (JOYSTICKS * 2)

#endif //INPUT_ANALOGUE_H