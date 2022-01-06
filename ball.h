#pragma once

#include <SDL.h>

class Ball
{
public:
	Ball(SDL_Renderer* renderer, int x, int y, int r = 5);

	void render();

private:
	SDL_Renderer* _renderer;

	int _position_x, _position_y, _radius;
};