#include <cstdlib>
#include <ctime>

#include "ball.h"
#include "physics.h"
#include "walls.h"

Ball::Ball(SDL_Renderer* renderer, int x, int y)
{
	this->renderer = renderer;

	this->x = x;
	this->y = y;

    // Choose 1 of 4 random directions for ball to go
    srand(time(NULL));
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

void Ball::move(SDL_Rect& top, SDL_Rect& bottom, SDL_Rect& left, SDL_Rect& right)
{
    x += velocity_x;
    y += velocity_y;

    if (Physics::is_collision(*this, top) || Physics::is_collision(*this, bottom)) {
        y -= velocity_y;
        velocity_y *= -1;
    }

    if (Physics::is_collision(*this, left) || Physics::is_collision(*this, right)) {
        x -= velocity_x;
        velocity_x *= -1;
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
         SDL_RenderDrawLine(renderer, x, y, x + circle_x, y + circle_y);
         SDL_RenderDrawLine(renderer, x, y, x + circle_y, y + circle_x);
         SDL_RenderDrawLine(renderer, x, y, x - circle_y, y + circle_x);
         SDL_RenderDrawLine(renderer, x, y, x - circle_x, y + circle_y);
         SDL_RenderDrawLine(renderer, x, y, x - circle_x, y - circle_y);
         SDL_RenderDrawLine(renderer, x, y, x - circle_y, y - circle_x);
         SDL_RenderDrawLine(renderer, x, y, x + circle_y, y - circle_x);
         SDL_RenderDrawLine(renderer, x, y, x + circle_x, y - circle_y);

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
