#include <stdio.h>

#include <string>

#include "score.h"

Score::Score(SDL_Renderer* renderer, TTF_Font* font, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	this->renderer = renderer;

	left_total = 0;
	right_total = 0;

	this->SCREEN_WIDTH = SCREEN_WIDTH;
	this->SCREEN_HEIGHT = SCREEN_HEIGHT;

	digit_textures.resize(MAX_SCORE + 1);
	digit_boxes.resize(MAX_SCORE + 1);

	SDL_Color color = { 255, 255, 255 };

	for (int i = 0; i < digit_textures.size(); i++)
	{
		SDL_Surface* surface = TTF_RenderText_Solid(font, std::to_string(i).c_str(), color);
		if (surface == NULL)
		{
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		}
		else
		{
			//Create texture from surface pixels
			digit_textures[i] = SDL_CreateTextureFromSurface(renderer, surface);
			if (digit_textures[i] == NULL)
			{
				printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Get image dimensions
				digit_boxes[i].w = surface->w;
				digit_boxes[i].h = surface->h;
			}

			//Get rid of old surface
			SDL_FreeSurface(surface);
		}
	}
}

void Score::increment_left_total()
{
	if (left_total < MAX_SCORE)
	{
		left_total += 1;
	}
}

void Score::increment_right_total()
{
	if (right_total < MAX_SCORE)
	{
		right_total += 1;
	}
}

bool Score::is_game_over()
{
	if (left_total < MAX_SCORE && right_total < MAX_SCORE)
	{
		return false;
	}

	return true;
}

void Score::render()
{
	int left_x = (SCREEN_WIDTH * 0.25) - (digit_boxes[left_total].w / 2);
	int right_x = (SCREEN_WIDTH * 0.75) - (digit_boxes[left_total].w / 2);

	SDL_Rect left_box = { left_x, 20, digit_boxes[left_total].w, digit_boxes[left_total].h };
	SDL_Rect right_box = { right_x, 20, digit_boxes[left_total].w, digit_boxes[left_total].h };

	SDL_RenderCopy(renderer, digit_textures[left_total], NULL, &left_box);
	SDL_RenderCopy(renderer, digit_textures[right_total], NULL, &right_box);
}