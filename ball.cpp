#include <cstdlib>
#include <ctime>

#include "ball.h"
#include "paddle.h"
#include "physics.h"
#include "walls.h"

Ball::Ball(SDL_Renderer* renderer, int x, int y)
{
	this->renderer = renderer;

    this->x = x;
    this->y = y;

    start_x = x;
    start_y = y;

    set_random_velocity();
}

void Ball::move(Walls& walls, Paddle& left_paddle, Paddle& right_paddle)
{
    x += velocity_x;
    y += velocity_y;

    if (Physics::is_collision(*this, walls.get_top()) || 
        Physics::is_collision(*this, walls.get_bottom())) {
        y -= velocity_y;
        velocity_y *= -1;
    }

    if (Physics::is_collision(*this, left_paddle.get_collider()) ||
        Physics::is_collision(*this, right_paddle.get_collider()))
    {
        x -= velocity_x;
        velocity_x *= -1;
    }

    if (Physics::is_collision(*this, walls.get_left()) ||
        Physics::is_collision(*this, walls.get_right()))
    {
        x = start_x;
        y = start_y;

        set_random_velocity();
    }
}

void Ball::render()
{
    // Midpoint circle algorithm
    int circle_x = RADIUS;
    int circle_y = 0;
    int error = 0;

    while (circle_x >= circle_y)
    {
         SDL_RenderDrawPoint(renderer, x + circle_x, y + circle_y);
         SDL_RenderDrawPoint(renderer, x + circle_y, y + circle_x);
         SDL_RenderDrawPoint(renderer, x - circle_y, y + circle_x);
         SDL_RenderDrawPoint(renderer, x - circle_x, y + circle_y);
         SDL_RenderDrawPoint(renderer, x - circle_x, y - circle_y);
         SDL_RenderDrawPoint(renderer, x - circle_y, y - circle_x);
         SDL_RenderDrawPoint(renderer, x + circle_y, y - circle_x);
         SDL_RenderDrawPoint(renderer, x + circle_x, y - circle_y);

        if (error <= 0)
        {
            circle_y += 1;
            error += 2 * circle_y + 1;
        }

        if (error > 0)
        {
            circle_x -= 1;
            error -= 2 * circle_x + 1;
        }
    }
}

int Ball::get_x()
{
    return x;
}

int Ball::get_y()
{
    return y;
}

int Ball::get_radius()
{
    return RADIUS;
}

void Ball::set_random_velocity()
{
    if (!is_seeded)
    {
        srand(time(NULL));
        is_seeded = true;
    }

    int random_int = rand() % 4;

    switch (random_int)
    {
    case 0:
        velocity_x = VELOCITY;
        velocity_y = VELOCITY;
        break;

    case 1:
        velocity_x = -VELOCITY;
        velocity_y = VELOCITY;
        break;

    case 2:
        velocity_x = -VELOCITY;
        velocity_y = -VELOCITY;
        break;

    case 3:
        velocity_x = VELOCITY;
        velocity_y = -VELOCITY;
        break;

    default:
        velocity_x = 0;
        velocity_y = 0;
        break;
    }
}