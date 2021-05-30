#include "pong.h"

/*
 * Function forward declarations.
 */
static void pong_init(void);
static void pong_reset(void);
static void pong_setup_single_player(void);
static void pong_single_player(void);
static collision_dim_t collision_w_bound(uint8_t collider_index);
static collision_dim_t collision_w_paddle_y(position_t pad_y_next, position_t coll_y_next,
                                            dimension_t pad_len, dimension_t coll_len);
static collision_dim_t collision_w_paddle(uint8_t paddle_index, uint8_t collider_index);
static void paddle_bound_collision(uint8_t paddle_index);
static void ball_collision_x(void);
static void ball_collision_y(void);

/*
 * Variables
 *
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
double dt;
    // Objects:
uint8_t objects_num;
dimensions_t bounds;
// Game mode:
typedef enum game_mode_t
{
    single_player,
    multi_player
} game_mode_t;
game_mode_t game_mode;

static void pong_init(void)
{
    dt = 0;

    bounds.x = CANVAS_X;
    bounds.y = CANVAS_Y;

    objects_num = 3;
    positions = malloc(sizeof(positions_t) * objects_num);
    velocities = malloc(sizeof(positions_t) * objects_num);
    positions_next = malloc(sizeof(positions_t) * objects_num);
    velocities = malloc(sizeof(velocities_t) * objects_num);
    object_dimensions = malloc(sizeof(dimensions_t) * objects_num);

    // Dimensions, 0 to 255:
        // Ball:
    object_dimensions[0].x = 3;
    object_dimensions[0].y = 3;
        // Paddle:
    object_dimensions[1].x = 1;
    object_dimensions[1].y = 17; // 20 px

    // Initial positions:
        // Ball:
    positions[0].x = CANVAS_X / 2;
    positions[0].y = CANVAS_Y / 2;
    positions_next[0].x = CANVAS_X / 2;
    positions_next[0].y = CANVAS_Y / 2;

    // Initial velocities:
        // Ball:
    {
        int signx = 0;
        int signy = 0;
        while(1)
        {
            srand(joysticks[0]);
            const int upper = 1;
            const int lower = -1;
            if(signx == 0)
            {
                signx = (rand() % (upper - lower + 1)) + lower;
            }
            if(signy == 0)
            {
                signy = (rand() % (upper - lower + 1)) + lower;
            }
            if(signx != 0 && signy != 0)
            {
                break;
            }
        }
        velocities[0].dx = signx * 20;
        velocities[0].dy = signy * 20;
    }
    // positions[0].y = 2;
    // positions_next[0].y = 2;
    // velocities[0].dx = 0;
    // velocities[0].dy = 50;


        // Paddles:
    positions[1].x = 0;
    positions[1].y = 20;
    positions_next[1].x = 0;
    positions_next[1].y = 20;
    velocities[1].dx = 0;
    velocities[1].dy = 0;
}

static void pong_reset(void)
{
    positions[0].x = CANVAS_X / 2;
    positions[0].y = CANVAS_Y / 2;
    positions_next[0].x = CANVAS_X / 2;
    positions_next[0].y = CANVAS_Y / 2;
}

static void pong_setup_single_player(void)
{
    objects_num = 2;
    game_mode = single_player;
}

static void pong_single_player(void)
{
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
                break;
        }
    }

    // Ball paddle collisions:
    for(uint8_t pad = 1; pad < objects_num; ++pad)
    {
        dimension_of_collision = collision_w_paddle(pad, 0);
        switch(dimension_of_collision)
        {
            case collision_x:
                ball_collision_x();
                break;
        }
    }
    // Ball bound collisions:
    dimension_of_collision = collision_w_bound(0);
    switch(dimension_of_collision)
    {
        case collision_y:
            ball_collision_y();
            break;
        
        case collision_x:
            if(positions_next[0].x <= 0)
            { // Lost life, reset.
                pong_reset();
            }
            else
            {
                ball_collision_x();
            }
            break;
            
        case collision_none:
            break;
    }
}

/*
 * Functions to check for collisions:
 */
static collision_dim_t collision_w_bound(uint8_t collider_index)
{
    // Positions:
    position_t x_next = positions_next[collider_index].x;
    position_t y_next = positions_next[collider_index].y;
    // Dimensions:
    uint8_t coll_width = object_dimensions[collider_index].x;
    uint8_t coll_len = object_dimensions[collider_index].y;

    // Left or right bound collision:
    if(x_next < 0 || x_next + coll_width > bounds.x)
    {
        return collision_x;
    }
    // Top or bottom collision:
    if(y_next < 0 || y_next + coll_len > bounds.y)
    {
        return collision_y;
    }

    return collision_none;
}

static collision_dim_t collision_w_paddle_y(position_t pad_y_next, position_t coll_y_next,
                                            dimension_t pad_len, dimension_t coll_len)
{
    // Will the paddle move to intersect between the current and predicted y coordinates of the colliding object?:
    // if(pad_y_next <= coll_y_next && (coll_y_next + coll_len) <= (pad_y_next + pad_len))
    if((coll_y_next >= pad_y_next || coll_y_next + coll_len >= pad_y_next) &&
       coll_y_next <= pad_y_next + pad_len)
    { // The colliding object either hit the paddle or its predicted next position went through it:
        return collision_x;
    }

    return collision_none;
}

static collision_dim_t collision_w_paddle(uint8_t paddle_index, uint8_t collider_index)
{
    // Paddle constrained along the x axis, so no movement in the x direction!
    // Positions:
    position_t coll_x = positions[collider_index].x;
    position_t coll_y = positions[collider_index].y;
    position_t pad_x = positions[paddle_index].x;
    position_t pad_y = positions[paddle_index].y;
    position_t coll_x_next = positions_next[collider_index].x;
    position_t coll_y_next = positions_next[collider_index].y;
    int pad_y_next = positions_next[paddle_index].y;
    // Dimensions:
    dimension_t pad_len = object_dimensions[paddle_index].y;
    dimension_t coll_width = object_dimensions[paddle_index].x;
    dimension_t coll_len = object_dimensions[collider_index].y;

    // Check if colliding object will cross paths with the paddle:
    if(pad_x == 0)
    { // Left paddle
        if(coll_x_next < pad_x)
        {
            return collision_w_paddle_y(pad_y_next, coll_y_next, pad_len, coll_len);
        }
    }
    else if(pad_x == bounds.x)
    { // Right paddle
        if(coll_x_next + coll_width > pad_x)
        {
            return collision_w_paddle_y(pad_y_next, coll_y_next, pad_len, coll_len);
        }
    }

    return collision_none;
}

/*
 * Functions to react to detected collisions:
 */
static void paddle_bound_collision(uint8_t paddle_index)
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

static void ball_collision_x(void)
{
    // Invert the x velocity:
    velocities[0].dx = velocities[0].dx * -1;

    // Reflect the x direction overshoot to prevent the ball sticking:
    if(positions_next[0].x < 0)
    { // Left side
        positions_next[0].x = positions_next[0].x * -1;
    }
    else if(positions_next[0].x > bounds.x + object_dimensions[0].x)
    { // Right side
        // positions[0].x = bounds.x - (positions[0].x - bounds.x);
        positions_next[0].x = 2*bounds.x - positions_next[0].x;
    }
}

static void ball_collision_y(void)
{
    // Invert the y velocity:
    velocities[0].dy = velocities[0].dy * -1;

    // Reflect the y direction overshoot to prevent the ball sticking:
    if(positions_next[0].y < 0)
    { // Top side
        positions_next[0].y = positions_next[0].y * -1;
    }
    else if(positions_next[0].y > bounds.y + object_dimensions[0].y)
    { // Bottom side
        positions_next[0].y = 2*bounds.y - positions_next[0].y;
    }
}

void pong(void)
{
    pong_init();
    pong_setup_single_player();

    while(1)
    {
        canvas_clear();

    // Get time since last game tick:
        dt = get_elapsed_game_time();

    // Read input:
        // Buttons (digital):

			// Joysticks (analogue):
        input_analogue_read(joysticks);

    // Interpret input, translating joystick movement to direction and intensity:
        // Joystick:
        if(ABS(joysticks[0] - 2048) <= J1_DEADZONE)
        { // Middle
            velocities[1].dy = 0;
        }
        if(joysticks[0] > 2048 + J1_DEADZONE)
        { // Down
            velocities[1].dy = PADDLE_MAX_SPEED;
        }
        else if(joysticks[0] < 2048 - J1_DEADZONE)
        { // Up
            velocities[1].dy = -PADDLE_MAX_SPEED;
        }

    // Update entity models:
        // Calculate the next position, assuming no collisions, for each object:
        for(uint8_t obj = 0; obj < objects_num; ++obj)
        {
            positions_next[obj].x += velocities[obj].dx*dt;
            positions_next[obj].y += velocities[obj].dy*dt;
        }

        // Check for and react to collisions, according to game mode:
        switch(game_mode)
        {
            case single_player:
                pong_single_player();
                break;
            
            case multi_player:
                break;
        }

    // Update the screen:
        draw_ball(positions_next[0].x , positions_next[0].y, object_dimensions[0]);
        draw_paddle(positions_next[1].x, positions_next[1].y, positions_next[1].x, positions_next[1].y + object_dimensions[1].y);
        canvas_update_all();
        
    // Set the current position to the next position that was calculated:
        for(uint8_t obj = 0; obj < objects_num; ++obj)
        {
            positions[obj].x = positions_next[obj].x;
            positions[obj].y = positions_next[obj].y;
        }
    }
}