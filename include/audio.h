#pragma once

#include <SDL_mixer.h>

class Audio
{
public:
	Audio();

	void free();

	void play_beeep();

	void play_peeeeeep();

	void play_plop();

private:
	Mix_Chunk* beeep;

	Mix_Chunk* peeeeeep;

	Mix_Chunk* plop;
};