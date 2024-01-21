#include "Snake.h"
#include <chrono>
#include <deque>

using namespace std;

// Constructor
Snake::Snake()
{
    m_isCollision = false;
    m_doGrow = false;
    m_isPickedUp = false;

    m_gridNbRows = m_grid->getNbRows();
    m_gridNbColumns = m_grid->getNbColumns();
    m_gridRowBuffer = m_grid->getRowBuffer();
    m_gridColumnBuffer = m_grid->getColumnBuffer();

    snakeInit();

    // should not randomly choose a direction, but rather go towards the middle depending on its initial coordinates
    m_snakeCurrDir = Direction::right;
    m_snakeNextDir = Direction::right;
}

void Snake::snakeInit()
{
    // Change so it randomly generates the first coordinate for the snake head and then two more so its of length 3
    Coordinates x, y, z, i, j, k, h;
    x.i = y.i = z.i = i.i = j.i = k.i = h.i = 10;
    x.j = 10; 
    y.j = 11; 
    z.j = 12; 
    i.j = 13; 
    j.j = 14; 
    k.j = 15; 
    h.j = 16; 
    m_snakeCoords.push_front(x);
    m_snakeCoords.push_front(y); 
    m_snakeCoords.push_front(z); 
    m_snakeCoords.push_front(i); 
    m_snakeCoords.push_front(j); 
    m_snakeCoords.push_front(k); 
    m_snakeCoords.push_front(h); 
}

// Called when an arrow key is pressed and checks if the snake direction needs to be changed and does so
void Snake::keyPressed(Direction keyDirection)
{
    // cannot turn back on itself or press key in the same direction
    if ((m_snakeCurrDir == Direction::up || m_snakeCurrDir == Direction::down) &&
        (keyDirection == Direction::left || keyDirection == Direction::right))
    {
        m_snakeNextDir = keyDirection;
    }
    // cannot turn back on itself or press key in the same direction
    else if ((m_snakeCurrDir == Direction::left || m_snakeCurrDir == Direction::right) &&
             (keyDirection == Direction::up || keyDirection == Direction::down))
    {
        m_snakeNextDir = keyDirection;
    }
}

// Updates snake's position and length
void Snake::tick(bool doMove)
{
    if (doMove)
    {
        Coordinates nextPos = m_snakeCoords.front();

        switch (m_snakeNextDir)
        {
        case Direction::left:
            nextPos.j--;
            break;

        case Direction::right:
            nextPos.j++;
            break;

        case Direction::up:
            nextPos.i--;
            break;

        case Direction::down:
            nextPos.i++;
            break;
        }

        collisionDetection(nextPos);

        // moves/grows snake if the snake hasn't hit the bounds or itself
        if (!m_isCollision)
        {
            m_snakeCoords.push_front(nextPos);

            nextPos = m_snakeCoords.back();
            m_grid->setGridChar(nextPos.i, nextPos.j, 32);

            if (!m_doGrow)
            {
                m_snakeCoords.pop_back(); // should be a flag that shoots up when the snake eats an apple, and will not pop the last one if the flag is up
            }
            else
            {
                m_doGrow = false;
            }
        }
    }

    snakeToGrid();

    m_snakeCurrDir = m_snakeNextDir;
}

// Checks if the snake collisions with itself or the bounding square
void Snake::collisionDetection(Coordinates nextPos)
{
    // bounds collision detection
    if (nextPos.i < m_gridRowBuffer ||
        nextPos.i >= m_gridNbRows - m_gridRowBuffer ||
        nextPos.j < m_gridColumnBuffer ||
        nextPos.j >= m_gridNbColumns - m_gridColumnBuffer)
    {
        m_isCollision = true;
    }

    // self collision detection
    int count = 1;
    for (auto it = m_snakeCoords.cbegin(); it != m_snakeCoords.cend(); it++)
    {
        Coordinates temp = *it;

        if (nextPos.i == temp.i &&
            nextPos.j == temp.j &&
            count < m_snakeCoords.size())
        {
            m_isCollision = true;
            break;
        }
        count++;
    }

    // pickup collision detection
    if (m_grid->getASCII(nextPos.i, nextPos.j) == ASCII::pickup)
    {
        m_doGrow = true;
        m_isPickedUp = true;
    }

}

// Inserts the snake into the printable grid
void Snake::snakeToGrid()
{
    // end of update, iterates through the queue and assigns snake positions to the 2d array
    // https://www.geeksforgeeks.org/how-to-iterate-a-stl-queue-in-cpp/
    int count = 0;
    for (auto it = m_snakeCoords.cbegin(); it != m_snakeCoords.cend(); it++)
    {
        Coordinates temp = *it;

        if (count == 0)
        {
            m_grid->setGridChar(temp.i, temp.j, ASCII::snakeHead); // different character for snake head
            count++;
        }
        else
        {
            m_grid->setGridChar(temp.i, temp.j, ASCII::snakeBody);
        }
    }
}