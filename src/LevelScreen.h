#ifndef LEVELSCREEN
#define LEVELSCREEN
#include "Screen.h"
#include "Level.h"


class Screen;

class LevelScreen : public Screen
{
    public:
    LevelScreen();
    LevelScreen(Game *game);
    ~LevelScreen();
    void loadTextures();
    void unloadTextures();
    void update();
    void draw();
    
    private:
    int levelTextureWidthDiff, levelTextureHeightDiff, levelNo;
    Texture2D menuBG, lockedLevel;
    vector<Texture2D> levelsTexture;
    bool changeLevel;
    
};

#endif //LEVELSCREEN