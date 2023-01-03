#include "MainMenuScreen.h"

MainMenuScreen::MainMenuScreen() : Screen()
{
    degrees = 0;
    buttonWidthDiff = (GetScreenWidth() - buttonWidth) - 50;
}

MainMenuScreen::MainMenuScreen(Game *game) : Screen(game)
{
    degrees = 0;
    buttonWidthDiff = (GetScreenWidth() - buttonWidth) - 50;
    loadTextures();
}

MainMenuScreen::~MainMenuScreen()
{

}

void MainMenuScreen::unloadTextures()
{

}

void MainMenuScreen::loadTextures()
{
    menuBG.setTexture(LoadTexture("./resources/mainMenu.png"));
    menuBG.setPosition({ float(0.0), float(0.0) });
    menuBG.setSize({float(GetScreenWidth()), float(GetScreenHeight())});
    for(int i = 1; i <= 2; i++)
    {
        string temp;
        Vector2 Position = {float(buttonWidthDiff), float(i * buttonHeight)},
                Size = {float(buttonWidth), float(buttonHeight)};
        if(i == 1)
        {
            survival.setTexture(LoadTexture("./resources/survival.png"));
            survival.setPosition(Position);
            survival.setSize(Size);
        }
        else
        {
            level.setTexture(LoadTexture("./resources/level.png"));
            level.setPosition(Position);
            level.setSize(Size);
        }
    }

}   

void MainMenuScreen::update()
{
    degrees = degrees % 360;
    double x = degrees * 3.14159/180;
    int result = sin(x) * 10;

    for (int i = 1; i <= 2; i++)
    {
        int tempX = GetMousePosition().x, tempY = GetMousePosition().y;
        if(i == 1)
            survival.setYPosition(i * buttonHeight + result);
        else
            level.setYPosition(i * buttonHeight + result);
        if (tempX >= buttonWidthDiff && tempX <= buttonWidthDiff + buttonWidth && tempY >= i * buttonHeight && tempY <= i * buttonHeight + buttonHeight)
        {
            degrees += 10;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                Screen *s;
                if (i == 1)
                    s = new Survival(gameState, "level0");
                else
                    s = new LevelScreen(gameState);
                gameState -> changeScreen(s);
            }
        }
        else
            degrees = 0;
    }
}

void MainMenuScreen::draw()
{
    menuBG.draw();
    survival.draw();
    level.draw();
}