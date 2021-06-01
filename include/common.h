#ifndef  COMMON_H
#define  COMMON_H

#include <stdint.h>
#include <stdlib.h>
// Header file to replace register definitions from libopencm3:
#include "libopencm3/libopencm3_registers.h"

#define ABS(x) (((x) >= 0) ? (x) : -(x))

typedef void(*func_ptr_min_t)(void);

#endif  //COMMON_H