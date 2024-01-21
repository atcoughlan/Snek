#include "Game.h"
#include <Windows.h>
#include <chrono>

using namespace std;

// Constructor
Game::Game()
{
    // would contain the bounds draw? if i go with the video thing where the cursor moves around to draw things WAIT BUT IT CLEARS THE WHOLE SCREEN
    // hrmm ok
    // so like every game loop it would draw the bounds (FUNCTION), then the snake, then the powerups (VECTOR FOR POWERUPS POSITIONS?)
    // https://www.youtube.com/watch?v=8BWJ3RBjjIg
    // enum for the directions? switch on them or something to figure out where the snake is moving
    // instead of printing out an increasingly larger string of characters, you'd have a vector of points and you loop through them and

    // should start after clicking space or something, should be a grid with instructions on the right (ideally) or the bottom

    // should i try and make a square snake hrmmmmm

    // snake should be initialized at random coordinates in random direction
    // user input for difficulty? (could be snake speed)

    // beep beep beep for 3 2 1 changing level, or bomb exploding

    // highscores stored in an external file (BASED ON FISH HUNT FORMAT) (LOOK AT COURSE NOTES)

    // box on the side with instructions on how to play, highscores on the side? or shown at the end of the game
    // maybe i have a start screen, game screen, and end screen => game state enum

    // think about turning the 2d array into a single array

    // do i want it to start when you click one of the arrows and it goes in that direction

    // idee: ca check les coordonnees avant apres et check quel caractere ca devrait etre (genre corner pipe or straight pipe typa thing)

    m_quit = false;
    m_gameOver = false;
    m_arrowHit = false;
    m_gameStart = false;

    m_timeStep = 0;

    m_pickup = new Pickup(&m_grid, &m_snake);

    m_snake.setGrid(&m_grid);
}

// Game loop
void Game::run()
{
    while (!m_quit && !m_gameOver) // when the player hasn't quit (change so that when they lose they will be given the option to restart, or they can quit at any time)
    {
        processEvents();
        update();
        render();
    }
}

// Processes keyboard events
void Game::processEvents()
{
    if (m_snake.getSnakeCurrDir() == Direction::left || m_snake.getSnakeCurrDir() == Direction::right)
    {
        m_timeStep = 150;
    }
    else
    {
        m_timeStep = 150;
    }
    
    // poll for events or whatever with the virtual keys
    auto endPoll = chrono::system_clock::now() + chrono::milliseconds(m_timeStep);
    while (chrono::system_clock::now() < endPoll)
    {        
        if (!m_arrowHit && m_gameStart)
        {
            m_arrowHit = true;
            if (GetAsyncKeyState(VK_LEFT) < 0)
            {
                m_snake.keyPressed(Direction::left);
            }
            else if (GetAsyncKeyState(VK_RIGHT) < 0)
            {
                m_snake.keyPressed(Direction::right);
            }
            else if (GetAsyncKeyState(VK_UP) < 0)
            {
                m_snake.keyPressed(Direction::up);
            }
            else if (GetAsyncKeyState(VK_DOWN) < 0)
            {
                m_snake.keyPressed(Direction::down);
            }
            else
            {
                m_arrowHit = false;
            }
        }

        if (GetAsyncKeyState(VK_RETURN) < 0)
        {
            m_gameStart = true;
            //m_pickup->newCoords(); have to remove the first draw if i want to do this
        }
        if (GetAsyncKeyState(VK_ESCAPE) < 0)
        {
            m_quit = true;
        }
    }
    m_arrowHit = false;
}

// Updates the entities positions (snake + powerups or wtv)
void Game::update()
{
    m_snake.tick(m_gameStart);

    if (m_snake.getIsPickedUp())
    {
        m_pickup->newCoords();
        m_snake.setIsPickedUp(false);
    }
    
    if (m_snake.getCollision())
    {
        m_gameOver = true;
    }
}

// Draws everything on the screen
void Game::render()
{
    system("CLS");

    m_grid.drawGrid();
}