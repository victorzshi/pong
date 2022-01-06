#pragma once

#include <SDL.h>

class Ball
{
public:
	Ball(SDL_Renderer* renderer, int x, int y);

	void move(SDL_Rect& top, SDL_Rect& bottom, SDL_Rect& left, SDL_Rect& right);

	void render();

private:
	const int RADIUS = 5;
	const int VELOCITY = 5;

	SDL_Renderer* renderer;

	int position_x, position_y;

	int velocity_x, velocity_y;

	bool is_collided(SDL_Rect& box);

	double calculate_distance_squared(int x_1, int x_2, int y_1, int y_2);
};