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
    totalNoOfFrames = 17;
    currentFrame = 0;
}

Loading::~Loading()
{
    unloadTextures();
}

void Loading::loadTextures()
{
    for(int i = 0; i < totalNoOfFrames; i++)
    {
        string textureToLoad = "./resources/loading/loading" + to_string(i + 1) + ".png";
        Texture2D loadedTexture = LoadTexture(textureToLoad.c_str());
        loadingTextures.push_back(loadedTexture);
        loadingTextures.at(i).width = GetScreenWidth();
        loadingTextures.at(i).height = GetScreenHeight();
    }
}

void Loading::unloadTextures()
{
    
    for(int i = 0; i < totalNoOfFrames; i++)
    {
        UnloadTexture(loadingTextures.at(i));
    }

}

void Loading::update()
{
    if(currentFrame == totalNoOfFrames - 1)
    {
        Screen *mainMenu = new MainMenuScreen(gameState);
        gameState -> changeScreen(mainMenu);
    }
    else
    {
        if(int(seconds) % 1 == 0 && milliSeconds == 0 && currentFrame < totalNoOfFrames)
        {    
            currentFrame++;
        }

        milliSeconds++;
        if(milliSeconds == 60)
        {
            seconds++;
            milliSeconds = 0;
        }
    }
}

void Loading::draw()
{
    DrawTexture(loadingTextures.at(0), 0, 0, WHITE);
    DrawTexture(loadingTextures.at(currentFrame), 0, 0, WHITE);
}

