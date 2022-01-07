#include <SDL.h>

#include "ball.h"
#include "paddle.h"
#include "physics.h"
#include "walls.h"

Paddle::Paddle(SDL_Renderer* renderer, int x, int y, Player player)
{
	this->renderer = renderer;

    this->player = player;

    velocity_y = 0;

    collider = { x - (WIDTH / 2), y - (LENGTH / 2), WIDTH, LENGTH};
}

void Paddle::handle_event(SDL_Event& event)
{
    switch (player)
    {
    case Player::HUMAN_UP_DOWN:
        if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                velocity_y -= VELOCITY;
                break;
            case SDLK_DOWN:
                velocity_y += VELOCITY;
                break;
            }
        }
        else if (event.type == SDL_KEYUP && event.key.repeat == 0)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                velocity_y += VELOCITY;
                break;
            case SDLK_DOWN:
                velocity_y -= VELOCITY;
                break;
            }
        }
        break;

    case Player::HUMAN_W_S:
        if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_w:
                velocity_y -= VELOCITY;
                break;
            case SDLK_s:
                velocity_y += VELOCITY;
                break;
            }
        }
        else if (event.type == SDL_KEYUP && event.key.repeat == 0)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_w:
                velocity_y += VELOCITY;
                break;
            case SDLK_s:
                velocity_y -= VELOCITY;
                break;
            }
        }
        break;
    }
}

void Paddle::move(Walls& walls, int ball_x, int ball_y)
{
    if (player == Player::CPU) cpu_move(ball_x, ball_y);

    collider.y += velocity_y;

    if (Physics::is_collision(collider, walls.get_top()) ||
        Physics::is_collision(collider, walls.get_bottom()))
    {
        collider.y -= velocity_y;
    }
}

void Paddle::render()
{
    SDL_RenderFillRect(renderer, &collider);
}

SDL_Rect& Paddle::get_collider()
{
    return collider;
}

void Paddle::cpu_move(int ball_x, int ball_y)
{
    int distance = collider.x - ball_x;
    int center = collider.y + (collider.h / 2);
    
    if (distance < 150)
    {
        if (ball_y > center)
        {
            velocity_y = VELOCITY;
        }
    
        if (ball_y < center)
        {
            velocity_y = -VELOCITY;
        }
    }
    else
    {
        velocity_y = 0;
    }
}