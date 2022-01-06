#pragma once

#include <SDL.h>

class Ball
{
public:
	Ball(SDL_Renderer* renderer, int x, int y, int r = 5, int velocity = 5);

	void move(SDL_Rect& top, SDL_Rect& bottom, SDL_Rect& left, SDL_Rect& right);

	void render();

private:
	SDL_Renderer* _renderer;

	int _position_x, _position_y, _radius;

	int _velocity_x, _velocity_y;

	bool _is_collided(SDL_Rect& box);

	double _calculate_distance_squared(int x_1, int x_2, int y_1, int y_2);
};