#include "pong.h"

void canvas_clear(void)
{
    clear_screen();
}

void canvas_update_all(void)
{
    show_screen();
}

void draw_paddle(position_t x, position_t y, position_t x_next, position_t y_next)
{
    draw_line((int) x, (int) y, (int) x_next, (int) y_next, FG_COLOUR);
}

void draw_ball(position_t x, position_t y, position_t x_next, position_t y_next)
{
    draw_pixel((int) x_next, (int) y_next, FG_COLOUR);
}