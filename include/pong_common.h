#ifndef  PONG_COMMON_H
#define  PONG_COMMON_H

// CAB202 libraries
#include <lcd.h>
#include <graphics.h>

#include "common.h"
#include "timing.h"
#include "input_analogue.h"

#define CANVAS_X LCD_X
#define CANVAS_Y LCD_Y
#define BALL_SPEED 1
#define PADDLE_MAX_SPEED 40

typedef uint16_t game_tick_t;
typedef double position_t;
// typedef int8_t dposition_t;
typedef int8_t velocity_t;
typedef uint8_t dimension_t;
typedef struct dimensions
{
    dimension_t x;
    dimension_t y;
} dimensions_t;
typedef struct positions
{
    position_t x;
    position_t y;
} positions_t;
// typedef struct dpositions
// {
//     dposition_t dx;
//     dposition_t dy;
// } dpositions_t;
typedef struct velocities
{
    velocity_t dx;
    velocity_t dy;
} velocities_t;
typedef enum collsion_dim
{
    collision_x,
    collision_y,
    collision_none
} collision_dim_t;

void canvas_clear(void);

void canvas_update_all(void);

void draw_paddle(position_t x, position_t y, position_t x_next, position_t y_next);

void draw_ball(position_t x, position_t y, dimensions_t ball_dims);

#endif //PONG_COMMON_H