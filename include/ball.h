#pragma once

#include <SDL.h>

#include "audio.h"
#include "paddle.h"
#include "score.h"
#include "walls.h"

class Ball
{
public:
	Ball(SDL_Renderer* renderer, int x, int y);

	void move(Score& score, Audio& audio, Walls& walls, Paddle& left_paddle, Paddle& right_paddle);

	void render();

	int get_x();

	int get_y();

	int get_radius();

private:
	const int RADIUS = 4;

	const int SPEED = 5;

	SDL_Renderer* renderer;

	int x, y;
	
	int start_x, start_y;

	int velocity_x, velocity_y;

	bool is_seeded = false;

	void set_random_velocity();

	void reset();
};