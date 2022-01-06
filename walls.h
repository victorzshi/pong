#pragma once

#include <SDL.h>

class Walls
{
public:
	Walls(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);

	void render();

	SDL_Rect& get_top();

	SDL_Rect& get_bottom();

	SDL_Rect& get_left();

	SDL_Rect& get_right();

private:
	const int THICKNESS = 1;

	SDL_Renderer* renderer;

	SDL_Rect top, bottom, left, right;
};
