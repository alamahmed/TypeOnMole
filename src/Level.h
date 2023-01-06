#ifndef LEVEL
#define LEVEL
#include "GameMode.h"
#include "LevelScreen.h"

class Level : public GameMode
{
    public:
    Level(Game *game, string LevelName);
    ~Level();
    void checkLevelStatus();
    
    private:
    int targetScore, currentLevel;
};

#endif //LEVEL