#include "include/walls.h"

Walls::Walls(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	this->renderer = renderer;

	top = { 0, 0 - THICKNESS, SCREEN_WIDTH, THICKNESS };
	bottom = { 0, SCREEN_HEIGHT, SCREEN_WIDTH, THICKNESS };
	left = { 0 - THICKNESS, 0, THICKNESS, SCREEN_HEIGHT };
	right = {SCREEN_WIDTH, 0, THICKNESS, SCREEN_HEIGHT};
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