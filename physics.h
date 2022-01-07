#pragma once

#include <SDL.h>

#include "ball.h"

class Physics
{
public:
	static bool is_collision(Ball& ball, SDL_Rect& box);

	static bool is_collision(SDL_Rect& box_1, SDL_Rect& box_2);

	static double calculate_distance_squared(int x_1, int y_1, int x_2, int y_2);
};