#include "pong.h"

/*
 * Store positions and velocities for all objects within two arrays.
 * This will work well as in pong no objects are being created or destroyed
 * during the game.
 * The ping pong ball will always be at the first index, followed by the two paddles.
 */

// Input data:
uint16_t joysticks[JOYSTICKS];

// Entity data:
// Array containing positions of objects:
positions_t* positions;
// Array containing change in positions of objects, assuming no collisions, not same as velocities as not wrt to time:
// dpositions_t* dpositions;
// Array containing the new position of objects to render a new frame:
positions_t* positions_next;
// Arrays containing velocities of objects:
velocities_t* velocities;
// Arrays containing dimensions of objects:
dimensions_t* object_dimensions;
// Timing variables:
game_tick_t dtick;
double dt;
// Objects:
uint8_t objects_num;
dimensions_t bounds;

void pong_init(void)
{
    // Set paddle dimensions:

    bounds.x = CANVAS_X;
    bounds.y = CANVAS_Y;

    dtick = 0;
    dt = 0;
}

void pong_setup_single_player(void)
{
    objects_num = 2;

    positions = malloc(sizeof(positions_t) * objects_num);
    velocities = malloc(sizeof(positions_t) * objects_num);
    positions_next = malloc(sizeof(positions_t) * objects_num);
    velocities = malloc(sizeof(velocities_t) * objects_num);
    object_dimensions = malloc(sizeof(dimensions_t) * objects_num);

    // Player paddles:
    positions[1].x = 0;
    positions[1].y = 20;
    positions_next[1].x = 0;
    positions_next[1].y = 20;
    velocities[1].dx = 0;
    velocities[1].dy = 0;
    object_dimensions[1].x = 0;
    object_dimensions[1].y = 20;

    // Ping pong ball:
}

// void pong_single_player(void);

/*
 * Functions to check for collisions:
 */
collision_dim_t collision_w_bound(uint8_t collider_index)
{
    // Positions:
    position_t x_next = positions_next[collider_index].x;
    position_t y_next = positions_next[collider_index].y;
    // Dimensions:
    uint8_t coll_width = object_dimensions[collider_index].x;
    uint8_t coll_len = object_dimensions[collider_index].y;

    // Left or right bound collision:
    if(x_next < 0.0 || x_next + coll_width > bounds.x)
    {
        return collision_x;
    }
    // Top or bottom collision:
    if(y_next < 0 || y_next + object_dimensions[collider_index].y > bounds.y)
    {
        return collision_y;
    }

    return collision_none;
}

collision_dim_t collision_w_paddle(uint8_t paddle_index, uint8_t collider_index)
{
    // Positions:
    int coll_x = positions[collider_index].x;
    int coll_y = positions[collider_index].y;
    int pad_x = positions[paddle_index].x;
    int pad_y = positions[paddle_index].y;
    int coll_x_next = positions_next[collider_index].x;
    int coll_y_next = positions_next[collider_index].y;
    // Paddle constrained along the x axis.
    int pad_y_next = positions_next[paddle_index].y;
    // Dimensions:
    uint8_t pad_len = object_dimensions[paddle_index].y;

    // Check if colliding object will cross paths with the paddle:
    if(coll_x_next <= pad_x || coll_x_next >= pad_x)
    {
        // Will the paddle move to intersect between the current and predicted y coordinates of the colliding object?:
        if(pad_y_next >= coll_y && pad_y_next + pad_len >= coll_y_next)
        { // The colliding object either hit the paddle or its predicted next position went through it:
            return collision_x;
        }
    }

    return collision_none;
}

/*
 * Functions to react to detected collisions:
 */
void paddle_bound_collision(uint8_t paddle_index)
{
    if(velocities[paddle_index].dy < 0)
    { // -ve dy, so hit top of screen:
        positions_next[paddle_index].y = 0;
    }
    else
    { // +ve dy, so hit bottom of screen:
        positions_next[paddle_index].y = bounds.y - object_dimensions[paddle_index].y;
    }

    velocities[paddle_index].dy = 0;
}

void paddle_continue(uint8_t paddle_index)
{

}

void ball_bound_collision_y()
{
    // Invert the y velocity:
    velocities[0].dy = velocities[0].dy * -1;
}

void ball_paddle_collision()
{
    // Invert the x velocity:
    velocities[0].dx = velocities[0].dx * -1;
}

void ball_continue()
{

}

void pong(void)
{
    pong_init();
    pong_setup_single_player();

    while(1)
    {
        canvas_clear();

    // Get time since last game tick:
        dtick = get_elapsed_game_ticks();
        dt = get_elapsed_game_time();

    // Read input:
        // Buttons (digital):

			// Joysticks (analogue):
        input_analogue_read(joysticks);

    // Interpret input, translating joystick movement to direction and intensity:
        if(joysticks[0] > 3000)
        {
            velocities[1].dy = 20;
        }
        else if(joysticks[0] < 1000)
        {
            velocities[1].dy = -20;
        }

    // Update entity models:
        // Calculate the next position, assuming no collisions, for each object:
        for(uint8_t obj = 0; obj < objects_num; ++obj)
        {
            positions_next[obj].x += velocities[obj].dx*dt;
            positions_next[obj].y += velocities[obj].dy*dt;
        }

        // Check for and react to collisions:
            // Paddle bound collisions:
        collision_dim_t dimension_of_collision;
        for(uint8_t pad = 1; pad < objects_num; ++pad)
        {
            dimension_of_collision = collision_w_bound(pad);
            // React to paddle striking a bound:
            switch(dimension_of_collision)
            {
                // Can only collide with bounds in the y direction:
                case collision_y:
                    paddle_bound_collision(pad);
                    break;
                case collision_none:
                    paddle_continue(pad);
                    break;
            }
        }
            // Ball bound collisions:
        dimension_of_collision = collision_w_bound(0);
        switch(dimension_of_collision)
        {
            case collision_y:
                ball_bound_collision_y();
                break;
                
            case collision_none:
                ball_continue();
                break;
        }

    // Update the screen:
        draw_paddle(positions_next[1].x, positions_next[1].y, positions_next[1].x, positions_next[1].y + object_dimensions[1].y);
        canvas_update_all();
        // for (int i = 0; i < 9000000; i++)
		// 	{ __asm__("nop"); }
        
    // Set the current position to the next position that was calculated:
        for(uint8_t obj = 0; obj < objects_num; ++obj)
        {
            positions[obj].x = positions_next[obj].x;
            positions[obj].y = positions_next[obj].y;
        }
    }
}