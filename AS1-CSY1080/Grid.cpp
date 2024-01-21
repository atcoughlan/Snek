#include "Grid.h"
#include <string>
#include <iostream>

using namespace std;

// Constructor
Grid::Grid()
{
	m_titleSpaces = "";

    frameInit();
    titleSpacesInit();
}

// Initializes bounding square in printable grid
void Grid::frameInit()
{
    for (int i = 0; i < m_nbRows; i++)
    {
        for (int j = 0; j < m_nbColumns; j++)
        {
            if (j <= m_columnBuffer - 1 || j >= m_nbColumns - m_columnBuffer || i <= m_rowBuffer - 1 || i >= m_nbRows - m_rowBuffer)
            {
                m_grid[i][j] = ASCII::frame;
            }
            else
            {
                m_grid[i][j] = ASCII::empty;
            }
        }
    }
}

// Determines the amount of spaces there should be before the title to center it over the bounding square
void Grid::titleSpacesInit()
{
    if (m_nbColumns >= m_titleLength)
    {
        for (int i = 0; i < (m_nbColumns - m_titleLength) / 2; i++)
        {
            m_titleSpaces += ASCII::empty;
        }
    }
}

// Prints out everything to the screen
void Grid::drawGrid()
{
    string line;

    // draws the title
    for (int i = 0; i < m_titleHeight; i++)
    {
        line = m_titleSpaces;
        for (int j = 0; j < m_titleLength; j++)
        {
            line += m_title[i][j];
        }
        cout << line + '\n';
    }
    cout << '\n';

    // draws m_grid
    for (int i = 0; i < m_nbRows; i++)
    {
        line = "";
        for (int j = 0; j < m_nbColumns; j++)
        {
            line += m_grid[i][j];
        }
        cout << line + '\n'; // reduces flickering vs endl and/or <<
    }
}