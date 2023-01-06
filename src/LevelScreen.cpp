#include "LevelScreen.h"

LevelScreen::LevelScreen() : Screen(){}

LevelScreen::LevelScreen(Game *game) : Screen(game)
{
    levelTextureWidthDiff = (GetScreenWidth() / ((totalNoOfLevels / (totalNoOfLevels / 5)) + 1));
    levelTextureHeightDiff = (GetScreenHeight() / ((totalNoOfLevels / 5) + 1));
    loadTextures();
    levelNo = 0;
    changeLevel = false;

}

LevelScreen::~LevelScreen()
{
    UnloadTexture(menuBG);
    UnloadTexture(lockedLevel);
    for (int i = 0; i < totalNoOfLevels; i++)
    {
        UnloadTexture(levelsTexture.at(i));
    }
}

void LevelScreen::unloadTextures()
{

}

void LevelScreen::loadTextures()
{
    menuBG = LoadTexture("./resources/menuBG.png");
    lockedLevel = LoadTexture("./resources/lockLevel.png");

    for (int i = 0; i < totalNoOfLevels; i++)
    {
        string textureToLoad = "./resources/" + to_string(i + 1) + ".png";
        levelsTexture.push_back(LoadTexture(textureToLoad.c_str()));
        levelsTexture.at(i).width = levelIconSize;
        levelsTexture.at(i).height = levelIconSize;
    }

    lockedLevel.width = levelIconSize;
    lockedLevel.height = levelIconSize;
    menuBG.width = GetScreenWidth();
    menuBG.height = GetScreenHeight();
}

void LevelScreen::update()
{
    if(changeLevel)
    {
        string levelToRead = "level" + to_string(levelNo);
        Screen * s = new Level(gameState, levelToRead.c_str());
        gameState -> changeScreen(s);
    }
}

void LevelScreen::draw()
{
    DrawTexture(menuBG, 0, 0, WHITE);
    int count = 0;
    for (int i = 0; i < (totalNoOfLevels / 5); i++)
    {
        for (int j = 0; j < totalNoOfLevels / (totalNoOfLevels / 5); j++)
        {
            int x = j * levelTextureWidthDiff + levelIconSize,
                y = i * levelTextureHeightDiff + levelIconSize;

            int tempX = GetMousePosition().x, tempY = GetMousePosition().y;

            if (count < gameState -> getUnlockedLevels())
            {
                DrawTexture(levelsTexture.at(count), x, y, WHITE);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    if ((tempX >= x && tempX <= x + levelIconSize) && (tempY >= y && tempY <= y + levelIconSize))
                    {
                        changeLevel = true;
                        levelNo = count + 1;
                    }
                }
            }
            else
                DrawTexture(lockedLevel, x, y, WHITE);
            count++;
        }
    }


}