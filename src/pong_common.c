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

void draw_ball(position_t x, position_t y, dimensions_t ball_dims)
{
    for(uint8_t px_x = 0; px_x < ball_dims.x; ++px_x)
    {
        for(uint8_t px_y = 0; px_y < ball_dims.y; ++px_y)
        {
            draw_pixel((int) x + px_x, (int) y + px_y, FG_COLOUR);
        }
    }
}

void set_ball_speed_mul_led(uint8_t ball_speed_mul)
{
    switch(ball_speed_mul)
    {
        case 1:
            pwm_set_duty_cycle(0.0);
            break;
        
        case 2:
            pwm_set_duty_cycle(25.0);
            break;
        
        case 3:
            pwm_set_duty_cycle(50.0);
            break;
        
        case 4:
            pwm_set_duty_cycle(100.0);
            break;
    }
}