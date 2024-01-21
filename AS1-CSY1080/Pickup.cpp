#include "Pickup.h"
#include <ctime>
#include <deque>

Pickup::Pickup(Grid* grid, Snake* snake)
{
	// randomly assign coordinates but they can't be any of the coordinates of the snake

	m_grid = grid;
	m_snake = snake;

	// A: randomize a coordinate, then check if it's in the snake
	// B: have a list of all possible coordinates, when a coordinate is added to the snake you take it out of the list, when a coordinate is removed from the snake you add it back
	//	  to get a random coordinate you get the size of the list (i guess its a vector) and get a random number between 0 and size, then you give the pick up that random coordinate

	// CAREFUL THERES A BUG WHERE THE PICKUP DOESNT INITIALIZE
	// maybe it initalizes where the snake is?? tbd

	newCoords();
}

void Pickup::newCoords()
{
	bool isValid;
	srand(static_cast<unsigned int>(time(0)));
	do
	{
		isValid = true;

		m_coords.i = randInRange(m_grid->getRowBuffer(), m_grid->getNbRows() - m_grid->getRowBuffer() - 1);
		m_coords.j = randInRange(m_grid->getColumnBuffer(), m_grid->getNbColumns() - m_grid->getColumnBuffer() - 1);

		deque<Coordinates> snakeCoords = m_snake->getSnakeCoords();

		for (auto it = snakeCoords.cbegin(); it != snakeCoords.cend(); it++)
		{
			Coordinates temp = *it;

			if (m_coords.i == temp.i && m_coords.j == temp.j)
			{
				isValid = false;
				break;
			}
		}
	} while (!isValid);

	m_grid->setGridChar(m_coords.i, m_coords.j, ASCII::pickup);
}

int Pickup::randInRange(int min, int max)
{
	return rand() % (max - min + 1) + min; 
}