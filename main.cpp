#include <stdio.h>

#include <string>

#include <SDL.h>

#include "ball.h"
#include "paddle.h"
#include "walls.h"

// Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Start SDL and show window
bool start();

// Clean up memory and stop SDL
void stop();

// Global window
SDL_Window* window = NULL;

// Global renderer
SDL_Renderer* renderer = NULL;

bool start()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}

	// Create window
	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Create vertical sync renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Initialize renderer color to black
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

	return true;
}

void stop()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	SDL_Quit();
}

int main(int argc, char* args[])
{
	if (!start())
	{
		printf("Failed to start!\n");
		return 1;
	}

	bool is_running = true;

	SDL_Event event;

	Walls walls(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	Paddle left_paddle(renderer, 19, SCREEN_HEIGHT / 2, Player::HUMAN_UP_DOWN);

	Paddle right_paddle(renderer, SCREEN_WIDTH - 19, SCREEN_HEIGHT / 2, Player::CPU);

	Ball ball(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	while (is_running)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				is_running = false;
			}

			left_paddle.handle_event(event);
			right_paddle.handle_event(event);
		}

		left_paddle.move(walls, ball.get_x(), ball.get_y());
		right_paddle.move(walls, ball.get_x(), ball.get_y());
		ball.move(walls, left_paddle, right_paddle);

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		walls.render();
		left_paddle.render();
		right_paddle.render();
		ball.render();

		SDL_RenderPresent(renderer);
	}

	stop();

	return 0;
}