#pragma once

#include <SDL.h>

class Walls
{
public:
	Walls(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, int thickness = 1);

	SDL_Rect& top();
		
	SDL_Rect& bottom();

	SDL_Rect& left();

	SDL_Rect& right();

	void render();

private:
	SDL_Renderer* _renderer;

	SDL_Rect _top, _bottom, _left, _right;
};
