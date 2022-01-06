#include "ball.h"

Ball::Ball(SDL_Renderer* renderer, int x, int y, int r)
{
	_renderer = renderer;

	_position_x = x;
	_position_y = y;

    _radius = r;
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