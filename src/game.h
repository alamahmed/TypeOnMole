#ifndef GAME
#define GAME
#include "preProcessors.h"
#include "Screen.h"

// Vector2 textSize = MeasureTextEx(font, totalScore.c_str(), fontSize, 0);
class Screen;

class Game
{
    public:
    Game();
    Game(int width, int height, int fps, string title);
    ~Game() noexcept;
    bool gameShouldClose() const;
    
    void changeScreen(Screen *screen);
    
    void tick();
    int getUnlockedLevels();
    void setUnlockedLevels(int unlockedLevels);
    void renderLevelMenu();
    void loadTextures();
    void initalizeVariables();

    private:
    void Draw();
    Screen *currentScreen;
    int unlockedLevels;
    Texture2D menu, menuBG, lockedLevel, gameOver;
    vector<Texture2D> levelsTexture, mainMenuButton;
};

#endif //GAME