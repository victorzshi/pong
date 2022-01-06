#pragma once

#include <SDL.h>

class Paddle
{
public:
	Paddle(SDL_Renderer* renderer, int x, int y);

	void handle_event(SDL_Event& event);

	void move(SDL_Rect& top, SDL_Rect& bottom);

	void render();

	SDL_Rect& get_collider();

private:
	const int WIDTH = 10;
	const int LENGTH = 50;
	const int VELOCITY = 5;

	SDL_Renderer* renderer;

	int velocity_y;

	SDL_Rect collider;
};