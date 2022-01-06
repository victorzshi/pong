#include "walls.h"

Walls::Walls(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, int thickness)
{
	_renderer = renderer;

	_top = { 0, 100, SCREEN_WIDTH, thickness };
	_bottom = { 0, SCREEN_HEIGHT - 100, SCREEN_WIDTH, thickness };
	_left = { 0, 100, thickness, SCREEN_HEIGHT - 200 };
	_right = {SCREEN_WIDTH - thickness, 100, thickness, SCREEN_HEIGHT - 200};
}

SDL_Rect& Walls::top()
{
	return _top;
}

SDL_Rect& Walls::bottom()
{
	return _bottom;
}

SDL_Rect& Walls::left()
{
	return _left;
}

SDL_Rect& Walls::right()
{
	return _right;
}

void Walls::render()
{
	SDL_RenderFillRect(_renderer, &_top);
	SDL_RenderFillRect(_renderer, &_bottom);
	SDL_RenderFillRect(_renderer, &_left);
	SDL_RenderFillRect(_renderer, &_right);
}