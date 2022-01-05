#include <SDL.h>
#include <stdio.h>
#include <string>

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
	// Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	// Quit SDL
	SDL_Quit();
}

int main(int argc, char* args[])
{
	// Start SDL and show window
	if (!start())
	{
		printf("Failed to start!\n");
		return 1;
	}

	// Main loop flag
	bool running = true;

	// Event handler
	SDL_Event event;

	// Set the boundaries
	SDL_Rect topBoundary, bottomBoundary;
	topBoundary.x = 0;
	topBoundary.y = 100;
	topBoundary.w = SCREEN_WIDTH;
	topBoundary.h = 1;

	bottomBoundary.x = 0;
	bottomBoundary.y = SCREEN_HEIGHT - 100;
	bottomBoundary.w = SCREEN_WIDTH;
	bottomBoundary.h = 1;

	// While application is running
	while (running)
	{
		// Handle events on queue
		while (SDL_PollEvent(&event) != 0)
		{
			// User requests quit
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
		}

		// Clear screen
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);

		// Render boundaries
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderDrawRect(renderer, &topBoundary);
		SDL_RenderDrawRect(renderer, &bottomBoundary);

		// Update screen
		SDL_RenderPresent(renderer);
	}

	// Clean up memory and stop SDL
	stop();

	return 0;
}