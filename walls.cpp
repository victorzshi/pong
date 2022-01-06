#include "walls.h"

Walls::Walls(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	_renderer = renderer;

	const int THICKNESS = 5;

	_top = { 0, 100, SCREEN_WIDTH, THICKNESS };
	_bottom = { 0, SCREEN_HEIGHT - 100, SCREEN_WIDTH, THICKNESS };
}

SDL_Rect& Walls::top()
{
	return _top;
}

SDL_Rect& Walls::bottom()
{
	return _bottom;
}

void Walls::render()
{
	SDL_RenderFillRect(_renderer, &_top);
	SDL_RenderFillRect(_renderer, &_bottom);
}