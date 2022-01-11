#include <stdio.h>

#include <SDL_mixer.h>

#include "audio.h"

Audio::Audio()
{
    beeep = Mix_LoadWAV("assets/sounds/ping_pong_8bit_beeep.ogg");
    if (beeep == NULL)
    {
        printf("Failed to load beeep sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }

    peeeeeep = Mix_LoadWAV("assets/sounds/ping_pong_8bit_peeeeeep.ogg");
    if (peeeeeep == NULL)
    {
        printf("Failed to load peeeeeep sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }

    plop = Mix_LoadWAV("assets/sounds/ping_pong_8bit_plop.ogg");
    if (plop == NULL)
    {
        printf("Failed to load plop sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

void Audio::free()
{
    Mix_FreeChunk(beeep);
    Mix_FreeChunk(peeeeeep);
    Mix_FreeChunk(plop);
    beeep = NULL;
    peeeeeep = NULL;
    plop = NULL;
}

void Audio::play_beeep()
{
    Mix_PlayChannel(-1, beeep, 0);
}

void Audio::play_peeeeeep()
{
    Mix_PlayChannel(-1, peeeeeep, 0);
}

void Audio::play_plop()
{
    Mix_PlayChannel(-1, plop, 0);
}
