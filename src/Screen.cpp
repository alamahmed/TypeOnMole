#include "Screen.h"

Screen::Screen()
{

}

Screen::Screen(Game *game)
{
    gameState = game;
}

Screen::~Screen()
{
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
