#pragma once

#include <SDL.h>

class Ball
{
public:
	Ball(SDL_Renderer* renderer, int x, int y);

	void move(SDL_Rect& top, SDL_Rect& bottom, SDL_Rect& left, SDL_Rect& right);

	void render();

	int get_x();

	int get_y();

	int get_radius();

private:
	const int RADIUS = 5;

	const int VELOCITY = 5;

	SDL_Renderer* renderer;

	int x, y;

	int velocity_x, velocity_y;
};