#ifndef SURVIVAL
#define SURVIVAL

#include "GameMode.h"

class Survival : public GameMode
{
    public:
    Survival(Game *game, string levelName);
    void checkLevelStatus();
    ~Survival();
};


#endif //SURVIVAL