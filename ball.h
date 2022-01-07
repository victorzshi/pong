#pragma once

#include <SDL.h>

#include "paddle.h"
#include "walls.h"

class Ball
{
public:
	Ball(SDL_Renderer* renderer, int x, int y);

	void move(Walls& walls, Paddle& left_paddle, Paddle& right_paddle);

	void render();

	int get_x();

	int get_y();

	int get_radius();

private:
	const int RADIUS = 5;

	const int VELOCITY = 5;

	SDL_Renderer* renderer;

	int x, y;
	
	int start_x, start_y;

	int velocity_x, velocity_y;
};