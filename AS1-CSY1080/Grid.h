#pragma once
#include <string>
#include <vector>
#include "Constants.h"

using namespace std;

class Grid
{
public:
	Grid(); // should be a constructor that takes nbrows as a parameter

    void drawGrid();

    // Getters
    int getNbRows()
    {
        return m_nbRows;
    }
    int getNbColumns()
    {
        return m_nbColumns;
    }
    int getRowBuffer()
    {
        return m_rowBuffer;
    }
    int getColumnBuffer()
    {
        return m_columnBuffer;
    }
    int getASCII(int i, int j)
    {
        return m_grid[i][j];
    }

    // Setters
    void setGridChar(int i, int j, char x)
    {
        m_grid[i][j] = x;
    }

private:
    // Member variables
    static const int m_nbRows = 25; // 25 ideal
    static const int m_nbColumns = m_nbRows * 2 + 1; // +1 to help center the title which is of odd length
    static const int m_rowBuffer = 1;
    static const int m_columnBuffer = m_rowBuffer * 2;

    char m_grid[m_nbRows][m_nbColumns];

    static const int m_titleHeight = 3;
    static const int m_titleLength = 19;
    const unsigned char m_title[m_titleHeight][m_titleLength] =
    {
        {201, 205, 187,  32,  201, 32,  186,  32,  201, 205, 187,  32,  186, 32,  186,  32,  201, 205, 205},
        {200, 205, 187,  32,  186, 186, 186,  32,  204, 205, 185,  32,  204, 185, 32,   32,  204, 205, 32 },
        {200, 205, 188,  32,  186, 32,  188,  32,  186, 32,  186,  32,  186, 32,  186,  32,  200, 205, 205}
    }; // only works with unsigned char

    string m_titleSpaces;

    // Member functions
    void frameInit();
    void titleSpacesInit();
};

