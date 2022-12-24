#include "preProcessors.h"

// Vector2 textSize = MeasureTextEx(font, totalScore.c_str(), fontSize, 0);

const int totalNoOfLevels = 10;
const int totalNoOfMoles = 12;

const int totalLives = 5;
const int levelIconSize = 130;
const int heartSize = 40;
const int keySize = heartSize;
const int holeWidth = 140;
const int holeHeight = 100;
const int widthDiff = 0;
const int heightDiff = 120;
const int buttonWidth = 430;
const int buttonHeight = 170;
const int fontSize = 80;

class Game
{
public:
    Game(int width, int height, int fps, string title);
    ~Game() noexcept;
    Game(const Game &other) = delete;
    Game &operator=(const Game &other) = delete;
    bool gameShouldClose() const;
    void tick();
    vector<vector<char>> readLvl(string levelName);
    void renderMainMenu();
    void renderLevel();
    void renderLevelMenu();
    void calcTime();
    void getMoleToHit();
    bool checkKeyPress(int keyPress);
    void setKeys();
    void checkGameState();
    void loadTextures();
    void initializeLevel(string levelToRead);
    void initalizeVariables(int width, int height);

private:
    void Update();
    void Draw();

    vector<vector<char>> currentLevel;
    vector<vector<char>> unlockedLevels;
    vector<vector<int>> key;

    int score, life, row, column;

    float miliSeconds, seconds, delay, speed;
    int gameWidth, gameHeight;
    int buttonWidthDiff, levelTextureWidthDiff, levelTextureHeightDiff;

    Font font;

    bool isPaused;
    enum gameState
    {
        mainMenuScreen,
        Survival,
        levelScreen,
        levels,
        endGame
    };
    gameState currentState;

    Texture2D mole, hole, fullHeart, emptyHeart, levelBG, keyTexture, menu, menuBG, lockedLevel, mainMenu, survivalButton, levelButton, gameOver;
    vector<Texture2D> levelsTexture;
};