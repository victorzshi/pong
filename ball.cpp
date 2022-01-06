#include <cstdlib>
#include <ctime>

#include "ball.h"
#include "walls.h"

Ball::Ball(SDL_Renderer* renderer, int x, int y)
{
	this->renderer = renderer;

	position_x = x;
	position_y = y;

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
    position_x += velocity_x;
    position_y += velocity_y;

    if (is_collided(top) || is_collided(bottom)) {
        velocity_y *= -1;
    }

    if (is_collided(left) || is_collided(right)) {
        velocity_x *= -1;
    }
}

void Ball::render()
{
    // Midpoint circle algorithm
    int x = RADIUS;
    int y = 0;
    int error = 0;

    while (x >= y)
    {
         SDL_RenderDrawPoint(renderer, position_x + x, position_y + y);
         SDL_RenderDrawPoint(renderer, position_x + y, position_y + x);
         SDL_RenderDrawPoint(renderer, position_x - y, position_y + x);
         SDL_RenderDrawPoint(renderer, position_x - x, position_y + y);
         SDL_RenderDrawPoint(renderer, position_x - x, position_y - y);
         SDL_RenderDrawPoint(renderer, position_x - y, position_y - x);
         SDL_RenderDrawPoint(renderer, position_x + y, position_y - x);
         SDL_RenderDrawPoint(renderer, position_x + x, position_y - y);

        if (error <= 0)
        {
            y += 1;
            error += 2 * y + 1;
        }

        if (error > 0)
        {
            x -= 1;
            error -= 2 * x + 1;
        }
    }
}

bool Ball::is_collided(SDL_Rect& box)
{
    // Closest point on collision box
    int closest_x, closest_y;

    // Find closest x offset
    if (position_x < box.x)
    {
        closest_x = box.x;
    }
    else if (position_x > box.x + box.w)
    {
        closest_x = box.x + box.w;
    }
    else
    {
        closest_x = position_x;
    }

    // Find closest y offset
    if (position_y < box.y)
    {
        closest_y = box.y;
    }
    else if (position_y > box.y + box.h)
    {
        closest_y = box.y + box.h;
    }
    else
    {
        closest_y = position_y;
    }

    // If the closest point is inside the circle
    if (calculate_distance_squared(position_x, position_y, closest_x, closest_y) < RADIUS * RADIUS)
    {
        return true;
    }
    
    return false;
}

double Ball::calculate_distance_squared(int x_1, int y_1, int x_2, int y_2)
{
    int delta_x = x_2 - x_1;
    int delta_y = y_2 - y_1;

    return delta_x * delta_x + delta_y * delta_y;
}
