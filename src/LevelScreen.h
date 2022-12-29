#ifndef LEVELSCREEN
#define LEVELSCREEN
#include "Screen.h"


class LevelScreen : public Screen
{
    public:
    LevelScreen(Game &game);
    ~LevelScreen();
    void loadTextures();
    void unloadTextures();
    void update();
    void draw();

};

#endif //LEVELSCREEN