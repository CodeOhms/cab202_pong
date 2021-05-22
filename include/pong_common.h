#ifndef  PONG_COMMON_H
#define  PONG_COMMON_H

// CAB202 libraries
#include <lcd.h>
#include <graphics.h>

#include "common.h"
#include "timing.h"

#define CANVAS_X LCD_X
#define CANVAS_Y LCD_Y
#define BALL_SPEED 1

typedef struct dimensions
{
    uint8_t x;
    uint8_t y;
} dimensions_t;
typedef enum collsion_dim
{
    collision_x,
    collision_y,
    collision_none
} collision_dim_t;
typedef uint16_t game_tick_t;
typedef uint16_t position_t;
typedef uint16_t velocity_t;

void canvas_clear(void);

void canvas_update_all(void);

void draw_paddle(position_t x, position_t y, position_t x_next, position_t y_next);

void draw_ball(position_t x, position_t y, position_t x_next, position_t y_next);

#endif //PONG_COMMON_H