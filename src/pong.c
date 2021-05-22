#include "pong.h"

/*
 * Store positions and velocities for all objects within two arrays.
 * This will work well as in pong no objects are being created or destroyed
 * during the game.
 * The ping pong ball will always be at the first index, followed by the two paddles.
 */

// Arrays containing positions of objects:
position_t* positions_x;
position_t* positions_y;
// Arrays containing velcoties of objects:
velocity_t* velocities_x;
velocity_t* velocities_y;
// Arrays containing positions of objects:
position_t* positions_x_next;
position_t* positions_y_next;
// Arrays containing velocites of objects:
velocity_t* velocities_x_next;
velocity_t* velocities_y_next;
// Arrays containing dimensions of objects:
dimensions_t* object_dimensions;
// Timing variables:
game_tick_t dtick;
double dt;
// Objects:
uint8_t objects_num;
dimensions_t paddle_dims;
// dimensions_t paddle_p2;
dimensions_t bounds;

void pong_init(void)
{
    // Set paddle dimensions:
    // paddle_p1.x = paddle_p2.x = 1;
    // paddle_p1.y = paddle_p2.y = 20;
    paddle_dims.x = 1;
    paddle_dims.y = 20;

    bounds.x = CANVAS_X;
    bounds.y = CANVAS_Y;

    dtick = 0;
    dt = 0;
}

void pong_setup_single_player(void)
{
    objects_num = 2;

    positions_x = malloc(sizeof(position_t) * objects_num);
    velocities_x = malloc(sizeof(position_t) * objects_num);
    positions_x_next = malloc(sizeof(position_t) * objects_num);
    velocities_x_next = malloc(sizeof(position_t) * objects_num);
    positions_y = malloc(sizeof(position_t) * objects_num);
    velocities_y = malloc(sizeof(position_t) * objects_num);
    positions_y_next = malloc(sizeof(position_t) * objects_num);
    velocities_y_next = malloc(sizeof(position_t) * objects_num);
    object_dimensions = malloc(sizeof(dimensions_t) * objects_num);

    // Player paddles:
    positions_x[1] = 0;
    positions_y[1] = 0;
    velocities_x[1] = 0;
    velocities_y[1] = 0;
    object_dimensions[1].x = 1;
    object_dimensions[1].y = 20;
    velocities_y_next[1] = 1;
    positions_y_next[1] = 0;

    // Ping pong ball:
    positions_x[0] = 0;
    positions_y[0] = 20;
    velocities_x[0] = 0;
    velocities_y[0] = 0;
    object_dimensions[0].x = 1;
    object_dimensions[0].y = 1;
}

// void pong_single_player(void);

collision_dim_t bound_collision(position_t collider_x, position_t collider_y, dimensions_t collider_dims)
{
    // Left or right bound collision:
    if(collider_x <= 0 || collider_x + collider_dims.x >= bounds.x)
    {
        return collision_x;
    }
    // Top or bottom collision:
    if(collider_y <= 0 || collider_y + collider_dims.y >= bounds.y)
    {
        return collision_y;
    }

    return collision_none;
}

collision_dim_t paddle_collision(position_t paddle_x, position_t paddle_y, position_t collider_x, position_t collider_y)
{
    if(collider_x == paddle_x)
    {
        if(paddle_y <= collider_y && collider_y <= paddle_y + paddle_dims.y)
        {
            return collision_x;
        }
    }

    return collision_none;
}

void paddle_y_collision()
{
    velocities_y[1] = 0;
    positions_y_next[1] = positions_y[1];
}

void pong(void)
{
    pong_init();
    pong_setup_single_player();

    velocities_y_next[1] = 1;

    while(1)
    {
        canvas_clear();

    // Get time since last game tick:
        dtick = get_elapsed_game_ticks();
        dt = get_elapsed_game_time();

    // Read input:
        // Buttons (digital):

			// Joysticks (analogue):

    // Interpret input:
        // pong_single_player();

    // Update entity models:
        // Check for collisions:
    for(uint8_t obj = 0; obj < objects_num; ++obj)
    {
        collision_dim_t dimension_of_collision = bound_collision(positions_x[obj], positions_y[obj], object_dimensions[obj]);
        switch(dimension_of_collision)
        {
            case collision_y:
                paddle_y_collision();
                break;
            default:
                positions_y_next[1] += 1;
        }
    }

        // React to collisions, if any:
            // Calculate the velocities:

            // Calculate the next position:

    // Update the screen:
        draw_paddle(0, positions_y_next[1], 0, positions_y_next[1] + object_dimensions[1].y);
        canvas_update_all();
        for (int i = 0; i < 9000000; i++)
			{ __asm__("nop"); }
        
    }
}