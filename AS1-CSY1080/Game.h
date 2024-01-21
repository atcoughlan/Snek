#pragma once
#include "Grid.h"
#include "Snake.h"
#include "Pickup.h"
#include <vector>

using namespace std;

class Game
{
public:
	Game();
	void run();

private:
    int m_timeStep; // not const because maybe it speeds up?

    bool m_quit;
    bool m_gameOver;
    bool m_arrowHit;
    bool m_gameStart;

    Grid m_grid;
    Snake m_snake;
    Pickup* m_pickup;

    int m_pickupCount;

	void processEvents();
	void update(); // THIS SHOULD CALL TICK
	void render();
};

