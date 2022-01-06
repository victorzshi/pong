#include "ball.h"
#include "walls.h"

Ball::Ball(SDL_Renderer* renderer, int x, int y, int r, int velocity)
{
	_renderer = renderer;

	_position_x = x;
	_position_y = y;
    _radius = r;

    _velocity_x = velocity;
    _velocity_y = velocity;
}

void Ball::move(SDL_Rect& top, SDL_Rect& bottom, SDL_Rect& left, SDL_Rect& right)
{
    _position_x += _velocity_x;
    _position_y += _velocity_y;

    if (_is_collided(top) || _is_collided(bottom)) {
        _velocity_y *= -1;
    }

    if (_is_collided(left) || _is_collided(right)) {
        _velocity_x *= -1;
    }
}

void Ball::render()
{
    // Midpoint circle algorithm
    int x = _radius;
    int y = 0;
    int error = 0;

    while (x >= y)
    {
         SDL_RenderDrawPoint(_renderer, _position_x + x, _position_y + y);
         SDL_RenderDrawPoint(_renderer, _position_x + y, _position_y + x);
         SDL_RenderDrawPoint(_renderer, _position_x - y, _position_y + x);
         SDL_RenderDrawPoint(_renderer, _position_x - x, _position_y + y);
         SDL_RenderDrawPoint(_renderer, _position_x - x, _position_y - y);
         SDL_RenderDrawPoint(_renderer, _position_x - y, _position_y - x);
         SDL_RenderDrawPoint(_renderer, _position_x + y, _position_y - x);
         SDL_RenderDrawPoint(_renderer, _position_x + x, _position_y - y);

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

bool Ball::_is_collided(SDL_Rect& box)
{
    //Closest point on collision box
    int closest_x, closest_y;

    //Find closest x offset
    if (_position_x < box.x)
    {
        closest_x = box.x;
    }
    else if (_position_x > box.x + box.w)
    {
        closest_x = box.x + box.w;
    }
    else
    {
        closest_x = _position_x;
    }

    //Find closest y offset
    if (_position_y < box.y)
    {
        closest_y = box.y;
    }
    else if (_position_y > box.y + box.h)
    {
        closest_y = box.y + box.h;
    }
    else
    {
        closest_y = _position_y;
    }

    //If the closest point is inside the circle
    if (_calculate_distance_squared(_position_x, _position_y, closest_x, closest_y) < _radius * _radius)
    {
        //This box and the circle have collided
        return true;
    }

    //If the shapes have not collided
    return false;
}

double Ball::_calculate_distance_squared(int x_1, int y_1, int x_2, int y_2)
{
    int delta_x = x_2 - x_1;
    int delta_y = y_2 - y_1;

    return delta_x * delta_x + delta_y * delta_y;
}
