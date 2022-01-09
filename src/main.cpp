#include <stdio.h>

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "include/ball.h"
#include "include/paddle.h"
#include "include/score.h"
#include "include/walls.h"

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

// Global font
TTF_Font* font = NULL;

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
	else
	{
		// Initialize renderer color to black
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	}

	// Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	// Open the font
	font = TTF_OpenFont("assets/PressStart2P-Regular.ttf", 32);
	if (font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	return true;
}

void stop()
{
	TTF_CloseFont(font);
	font = NULL;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	TTF_Quit();
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

	Score score(renderer, font, SCREEN_WIDTH, SCREEN_HEIGHT);

	Paddle left_paddle(renderer, 19, SCREEN_HEIGHT / 2, Player::HUMAN_UP_DOWN);

	Paddle right_paddle(renderer, SCREEN_WIDTH - 20, SCREEN_HEIGHT / 2, Player::CPU);

	Ball ball(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	while (is_running && !score.is_game_over())
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
		ball.move(walls, left_paddle, right_paddle, score);

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		walls.render();
		score.render();
		left_paddle.render();
		right_paddle.render();
		ball.render();

		SDL_RenderPresent(renderer);
	}

	if (!is_running)
	{
		stop();

		return 0;
	}
	else
	{
		while (true)
		{
			if (SDL_PollEvent(&event) != 0 && event.type == SDL_QUIT)
			{
				stop();

				return 0;
			}
		}
	}
}