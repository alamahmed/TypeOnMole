#include "Survival.h"

Survival::Survival(Game *game, string levelName) : GameMode(game, levelName)
{
}

void Survival::checkLevelStatus()
{
    if(updateSurvival)
    {
        if(limit > 30)
            limit -= 5;
        else if(speed > 2)
        {
            limit = 60;
            speed--;
        }
        updateSurvival = false;
    }
    if(bonus)
        life++;
}

Survival::~Survival()
{

}