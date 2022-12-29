#ifndef MAINMENUSCREEN
#define MAINMENUSCREEN
#include "Screen.h"


class MainMenuScreen : public Screen
{

    public:
    MainMenuScreen();
    MainMenuScreen(Game &game);
    ~MainMenuScreen();
    void loadTextures();
    void unloadTextures();
    void update();
    void draw();

    private:
    int degrees, buttonWidthDiff;
    Sprite menuBG, survival, level;
    
};


#endif //MAINMENUSCREEN