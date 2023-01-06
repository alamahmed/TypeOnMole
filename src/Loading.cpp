#include "Loading.h"


Loading::Loading() : Screen()
{
    initializeVariables();
}

Loading::Loading(Game *game) : Screen(game)
{
    initializeVariables();
}

void Loading::initializeVariables()
{
    loadTextures();
    totalNoOfFrames = 200;
    currentFrame = 500;
}

Loading::~Loading()
{
    unloadTextures();
}

void Loading::loadTextures()
{
    FirstTexture = LoadTexture("./resources/loading/loading1.png");
    FinalTexture = LoadTexture("./resources/loading/loading2.png");
    
    FirstTexture.width = GetScreenWidth();
    FirstTexture.height = GetScreenHeight();

    FinalTexture.width = GetScreenWidth();
    FinalTexture.height = GetScreenHeight();
}

void Loading::unloadTextures()
{
    UnloadTexture(FirstTexture);
    UnloadTexture(FinalTexture);
}

void Loading::update()
{
    if(currentFrame < totalNoOfFrames)
    {
        Screen *mainMenu = new MainMenuScreen(gameState);
        gameState -> changeScreen(mainMenu);
    }
    else
    {
        if(currentFrame >= totalNoOfFrames)
            currentFrame -= 3;
    }
}

void Loading::draw()
{
    Rectangle rect;
    rect.x = 0;
    rect.y = float(currentFrame);
    rect.height = GetScreenHeight();
    rect.width = GetScreenWidth();
    DrawTexture(FirstTexture, 0, 0, WHITE);
    DrawTextureRec(FinalTexture,rect,{0,float(currentFrame)},WHITE);
}

