#include "walls.h"

Walls::Walls(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	this->renderer = renderer;

	top = { 0, 100, SCREEN_WIDTH, THICKNESS };
	bottom = { 0, SCREEN_HEIGHT - 100, SCREEN_WIDTH, THICKNESS };
	left = { 0, 100, THICKNESS, SCREEN_HEIGHT - 200 };
	right = {SCREEN_WIDTH - THICKNESS, 100, THICKNESS, SCREEN_HEIGHT - 200};
}

void Walls::render()
{
	SDL_RenderFillRect(renderer, &top);
	SDL_RenderFillRect(renderer, &bottom);
	SDL_RenderFillRect(renderer, &left);
	SDL_RenderFillRect(renderer, &right);
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
