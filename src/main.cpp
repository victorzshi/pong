#include <stdio.h>

#include <string>

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "audio.h"
#include "ball.h"
#include "paddle.h"
#include "score.h"
#include "timer.h"
#include "walls.h"

// Screen constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int SCREEN_TIME_PER_FRAME = 1000 / SCREEN_FPS;

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

// Sound effects
Audio audio;

bool start()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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

	// Create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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
	font = TTF_OpenFont("assets/fonts/PressStart2P-Regular.ttf", 32);
	if (font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	// Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	return true;
}

void stop()
{
	audio.free();

	TTF_CloseFont(font);
	font = NULL;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	Mix_Quit();
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

	audio = Audio();

	Score score(renderer, font, SCREEN_WIDTH, SCREEN_HEIGHT);

	Walls walls(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	Paddle left_paddle(renderer, 19, SCREEN_HEIGHT / 2, Player::HUMAN_UP_DOWN);

	Paddle right_paddle(renderer, SCREEN_WIDTH - 20, SCREEN_HEIGHT / 2, Player::CPU);

	Ball ball(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	Timer frame_timer;

	int total_frames = 0;

	while (is_running && !score.is_game_over())
	{
		frame_timer.start();

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
		ball.move(score, audio, walls, left_paddle, right_paddle);

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		walls.render();
		score.render();
		left_paddle.render();
		right_paddle.render();
		ball.render();

		SDL_RenderPresent(renderer);
		++total_frames;
		int frame_time = frame_timer.get_elapsed_time();
		if (frame_time < SCREEN_TIME_PER_FRAME)
		{
			SDL_Delay(SCREEN_TIME_PER_FRAME - frame_time);
		}
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