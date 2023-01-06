#ifndef GAMEMODE
#define GAMEMODE
#include "Screen.h"


class GameMode : public Screen
{

    public:
    GameMode(Game *game, string levelName);
    ~GameMode();
    void loadTextures();
    void unloadTextures();
    void calcTime();
    void initializeLevel(string levelToRead);
    vector<vector<char>> readLvl(string levelName);
    bool checkKeyPress(int keyPress);
    virtual void checkLevelStatus();
    void getMoleToHit();
    void setKeys();
    void update();
    void draw();
    
    protected:
    bool isPaused, updateSurvival, bonus;
    int score, life, row, column, currentAnimationFrame;
    int gameWidth, gameHeight;
    float miliSeconds, seconds, delay, speed, limit;
    
    vector<vector<char>> currentLevel;
    vector<vector<int>> key;
    vector<Texture2D> moles;
    Texture2D hole, fullHeart, emptyHeart, levelBG, keyTexture, menu;
    
    Sprite Continue, main, restart;

};


#endif //GAMEMODE