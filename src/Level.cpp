#include "Level.h"

Level::Level(Game *game, string levelName) : GameMode(game, levelName)
{
    int size = levelName.size();
    string temp = levelName.substr(5, size);
    targetScore = stoi(temp);
    currentLevel = targetScore;
    targetScore *= 5;
}

Level::~Level()
{

}

void Level::checkLevelStatus()
{
    if(score == targetScore)
    {
        int temp = gameState -> getUnlockedLevels();
        if(currentLevel == temp)
            gameState -> setUnlockedLevels(temp + 1);

        Screen * s = new LevelScreen(gameState);
        gameState -> changeScreen(s);
    }
}

