#include "walls.h"

Walls::Walls(SDL_Renderer* renderer, int screen_width, int screen_height)
{
	this->renderer = renderer;

	top = { 0, 0 - THICKNESS, screen_width, THICKNESS };
	bottom = { 0, screen_height, screen_width, THICKNESS };
	left = { 0 - THICKNESS, 0, THICKNESS, screen_height };
	right = {screen_width, 0, THICKNESS, screen_height};
}

void Walls::render()
{
	SDL_RenderFillRect(renderer, &top);
	SDL_RenderFillRect(renderer, &bottom);
	SDL_RenderFillRect(renderer, &left);
	SDL_RenderFillRect(renderer, &right);
	
	render_halfway_line();
}

SDL_Rect& Walls::get_top()
{
	return top;
}

SDL_Rect& Walls::get_bottom()
{
	return bottom;
}

SDL_Rect& Walls::get_left()
{
	return left;
}

SDL_Rect& Walls::get_right()
{
	return right;
}

void Walls::render_halfway_line()
{
	for (int i = 0; i < left.h; i++)
	{
		if (i % 10 < 5)
		{
			SDL_RenderDrawPoint(renderer, top.w / 2, i);
		}
	}
}