#ifndef  PONG_H
#define  PONG_H

#ifdef ENV_ARM
#include "libopencm3/pong_libopencm3.h"
#endif

#include "pong_common.h"

void pong(void);

#endif // PONG_H