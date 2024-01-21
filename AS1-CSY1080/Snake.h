#pragma once
#include <string>
#include <deque>
#include "Grid.h"
#include "Constants.h"

using namespace std;

class Snake
{
public:
    Snake();
    void keyPressed(Direction);
    void tick(bool);

    // Getters
    bool getCollision()
    {
        return m_isCollision;
    }
    deque<Coordinates> getSnakeCoords()
    {
        return m_snakeCoords;
    }
    Direction getSnakeCurrDir()
    {
        return m_snakeCurrDir;
    }
    bool getIsPickedUp()
    {
        return m_isPickedUp;
    }
    
    // Setters
    void setGrid(Grid* grid)
    {
        m_grid = grid;
    }
    void setIsPickedUp(bool isPickedUp)
    {
        m_isPickedUp = isPickedUp;
    }
    
private:
    Direction m_snakeCurrDir;
    Direction m_snakeNextDir;

    deque<Coordinates> m_snakeCoords; // PUSH FRONT POP BACK
    
    Grid* m_grid;
    int m_gridNbRows, m_gridNbColumns, m_gridRowBuffer, m_gridColumnBuffer;

    bool m_isCollision;
    bool m_doGrow;
    bool m_isPickedUp;

    void snakeInit();
    void collisionDetection(Coordinates);
    void snakeToGrid();
};

