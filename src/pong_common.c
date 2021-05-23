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

    // lcd_position(x, y);
    // // Calculate the pixel, within that LCD bank
	// uint8_t bank = (int) y >> 3;
	// uint8_t pixel = (int) y & 7;
	// // Set that particular pixel in our screen buffer
	// 	// Draw Pixel
    // uint8_t byte = [bank*CANVAS_X + x] |= (1 << pixel);
    // lcd_write();
}