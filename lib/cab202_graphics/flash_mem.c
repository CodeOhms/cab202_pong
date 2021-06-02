#include "flash_mem.h"

#ifdef ENV_AVR
#include <avr/pgmspace.h>

uint8_t flash_mem_read_byte(uint32_t* address_ptr)
{
    return pgm_read_byte(address);
}

#elif ENV_ARM

uint8_t flash_mem_read_byte(uint32_t* address_ptr)
{
    return *address_ptr;
}

#endif