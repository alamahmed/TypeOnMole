#include "Screen.h"

Screen::Screen()
{

}

Screen::Screen(Game &game)
{
    gameState = new Game;
    *gameState = game;
}

Screen::~Screen()
{
    delete gameState;
    unloadTextures();
}

void Screen::unloadTextures()
{

}

void Screen::loadTextures()
{

}

void Screen::update()
{

}

void Screen::draw()
{
    ClearBackground(BLACK);
}
