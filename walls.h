#pragma once

#include <SDL.h>

class Walls
{
public:
	Walls(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);

	SDL_Rect& top();
		
	SDL_Rect& bottom();

	void render();

private:
	SDL_Renderer* _renderer;

	SDL_Rect _top, _bottom;
};
