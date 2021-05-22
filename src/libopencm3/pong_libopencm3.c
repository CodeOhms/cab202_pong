#include "pong.h"

uint32_t get_elapsed_game_ticks(void)
{
    return elapsed_ticks(1);
}

double get_elapsed_game_time(void)
{
    return ticks_to_time(1);
}