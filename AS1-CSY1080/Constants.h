#pragma once

struct Coordinates
{
    int i;
    int j;
};

enum class Direction
{
    left,
    right,
    up,
    down
};

// https://www.asciitable.com/
enum ASCII : char
{
    empty = 32,
    frame = 219 - 256,
    snakeHead = 178 - 256,
    snakeBody = 177 - 256, 
    pickup = 254 - 256
};
