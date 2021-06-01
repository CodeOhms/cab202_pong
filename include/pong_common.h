#ifndef  PONG_COMMON_H
#define  PONG_COMMON_H

#include <stdio.h>
// CAB202 libraries
#include <lcd.h>
#include <graphics.h>

#include "common.h"
#include "timing.h"
#include "input_analogue.h"
#include "input_digital.h"
#include "pwm.h"
#include "serial_comm.h"

#define CANVAS_X LCD_X
#define CANVAS_Y LCD_Y
#define BALL_SPEED 25
#define PADDLE_MAX_SPEED 60

typedef uint16_t game_tick_t;
typedef double position_t;
// typedef int8_t dposition_t;
typedef int8_t velocity_t;
typedef uint8_t dimension_t;
typedef struct dimensions_t
{
    dimension_t x;
    dimension_t y;
} dimensions_t;
typedef struct positions_t
{
    position_t x;
    position_t y;
} positions_t;
typedef struct velocities_t
{
    velocity_t dx;
    velocity_t dy;
} velocities_t;
typedef enum collision_dim_t
{
    collision_x,
    collision_y,
    collision_none
} collision_dim_t;

void canvas_clear(void);

void canvas_update_all(void);

void draw_paddle(position_t x, position_t y, position_t x_next, position_t y_next);

void draw_ball(position_t x, position_t y, dimensions_t ball_dims);

void set_ball_speed_mul_led(uint8_t ball_speed_mul);

void serial_print_sp_score(uint16_t sp_score);

#endif //PONG_COMMON_H