#pragma once
#include "Constants.h"
#include "Grid.h"
#include "Snake.h"

class Pickup
{
	// THOUGHT : the randomized pickup location needs to be somewhere other than the snake's locations
	// maybe you also don't want it to be right next to the snake

public:
	Pickup(Grid*, Snake*);
	void newCoords();

private:
	Coordinates m_coords;

	Grid* m_grid;
	Snake* m_snake;

	int randInRange(int, int);
};

