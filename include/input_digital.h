#ifndef  INPUT_DIGITAL_H
#define  INPUT_DIGITAL_H

#include "timing.h"

#ifdef  ENV_ARM
#include "libopencm3/input_digital_libopencm3.h"
#endif //ARM

#define BUTTON_HISTORY_SIZE 5 // Maximum of 8 bits!

#endif //INPUT_DIGITAL_H