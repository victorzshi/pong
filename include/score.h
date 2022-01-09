#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <vector>

class Score
{
public:
	Score(SDL_Renderer* renderer, TTF_Font* font, int screen_width, int screen_height);

	void increment_left_total();

	void increment_right_total();

	bool is_game_over();

	void render();

private:
	int MAX_SCORE = 9;

	SDL_Renderer* renderer;

	int screen_width, screen_height;

	int left_total, right_total;

	std::vector<SDL_Texture*> digit_textures;

	std::vector<SDL_Rect> digit_boxes;
};