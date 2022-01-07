#include "physics.h"

bool Physics::is_collision(Ball& ball, SDL_Rect& box)
{
    int ball_x = ball.get_x();
    int ball_y = ball.get_y();
    int radius = ball.get_radius();

    // Closest point on collision box
    int closest_x, closest_y;

    // Find closest x offset
    if (ball_x < box.x)
    {
        closest_x = box.x;
    }
    else if (ball_x > box.x + box.w)
    {
        closest_x = box.x + box.w;
    }
    else
    {
        closest_x = ball_x;
    }

    // Find closest y offset
    if (ball_y < box.y)
    {
        closest_y = box.y;
    }
    else if (ball_y > box.y + box.h)
    {
        closest_y = box.y + box.h;
    }
    else
    {
        closest_y = ball_y;
    }

    // If the closest point is inside the circle
    if (calculate_distance_squared(ball_x, ball_y, closest_x, closest_y) < radius * radius)
    {
        return true;
    }

    return false;
}

bool Physics::is_collision(SDL_Rect& box_a, SDL_Rect& box_b)
{
    // The sides of the boxes
    int left_a, left_b;
    int right_a, right_b;
    int top_a, top_b;
    int bottom_a, bottom_b;

    // Calculate the sides of box A
    left_a = box_a.x;
    right_a = box_a.x + box_a.w;
    top_a = box_a.y;
    bottom_a = box_a.y + box_a.h;

    // Calculate the sides of box B
    left_b = box_b.x;
    right_b = box_b.x + box_b.w;
    top_b = box_b.y;
    bottom_b = box_b.y + box_b.h;

    // If any of the sides from box A are outside of box B
    if (bottom_a <= top_b)
    {
        return false;
    }

    if (top_a >= bottom_b)
    {
        return false;
    }

    if (right_a <= left_b)
    {
        return false;
    }

    if (left_a >= right_b)
    {
        return false;
    }

    return true;
}

double Physics::calculate_distance_squared(int x_1, int y_1, int x_2, int y_2)
{
    int delta_x = x_2 - x_1;
    int delta_y = y_2 - y_1;

    return delta_x * delta_x + delta_y * delta_y;
}
