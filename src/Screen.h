#ifndef SCREEN
#define SCREEN
#include "game.h"
#include "Sprite.h"

class Game;

class Screen
{
    public:
    Screen();
    Screen(Game *game);
    ~Screen();
    void loadTextures();
    void unloadTextures();
    virtual void update();
    virtual void draw();

    protected:
    Game * gameState;

};

#endif //SCREEN