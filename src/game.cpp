#include "game.h"


Game::Game()
{
    
}


Game::Game(int width, int height, int fps, string title)
{
    SetTargetFPS(fps);
    InitWindow(width, height, title.c_str());

    initalizeVariables();
    // loadTextures();
}

Game::~Game() noexcept
{
    delete currentScreen;
    UnloadTexture(menu);
    UnloadTexture(menuBG);
    UnloadTexture(lockedLevel);
    UnloadTexture(gameOver);
    for (int i = 0; i < totalNoOfLevels; i++)
    {
        UnloadTexture(levelsTexture.at(i));
    }
    CloseWindow();
}

void Game::initalizeVariables()
{
    srand(time(0));
    levelTextureWidthDiff = (GetScreenWidth() / ((totalNoOfLevels / (totalNoOfLevels / 5)) + 1));
    levelTextureHeightDiff = (GetScreenHeight() / ((totalNoOfLevels / 5) + 1));
}

void Game::loadTextures()
{
    menu = LoadTexture("./resources/menu.png");
    menuBG = LoadTexture("./resources/menuBG.png");
    lockedLevel = LoadTexture("./resources/lockLevel.png");
    gameOver = LoadTexture("./resources/gameOver.png");
    
    for (int i = 0; i < totalNoOfLevels; i++)
    {
        string textureToLoad = "./resources/" + to_string(i + 1) + ".png";
        levelsTexture.push_back(LoadTexture(textureToLoad.c_str()));
        levelsTexture.at(i).width = levelIconSize;
        levelsTexture.at(i).height = levelIconSize;
    }

    lockedLevel.width = levelIconSize;
    lockedLevel.height = levelIconSize;
    menuBG.width = GetScreenWidth();
    menuBG.height = GetScreenHeight();
    gameOver.width = GetScreenWidth();
    gameOver.height = GetScreenHeight();
}

bool Game::gameShouldClose() const
{
    return WindowShouldClose();
}

void Game::tick()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    this -> currentScreen -> update();
    this -> currentScreen -> draw();
    EndDrawing();
}

void Game::changeScreen(Screen *screen)
{
    cout << "Change screen start\n";
    currentScreen = new Screen;
    // currentScreen -> ~Screen();
    currentScreen = screen;
    cout << "Change screen end\n";
}

void Game::Draw()
{
    // case endGame:
    //     DrawTexture(gameOver, 0, 0, WHITE);
    //     string totalScore = to_string(score);
    //     // Vector2 textSize = MeasureTextEx(font, totalScore.c_str(), fontSize, 0);
    //     DrawText(totalScore.c_str(), (GetScreenWidth() / 2) - (textSize.x / 4), (GetScreenHeight() / 2) - textSize.y * 2, fontSize, BLACK);
    //     break;
}

void Game::renderLevelMenu()
{
    // DrawTexture(menuBG, 0, 0, WHITE);
    // int count = 0;
    // for (int i = 0; i < (totalNoOfLevels / 5); i++)
    // {
    //     for (int j = 0; j < totalNoOfLevels / (totalNoOfLevels / 5); j++)
    //     {
    //         int x = j * levelTextureWidthDiff + levelIconSize,
    //             y = i * levelTextureHeightDiff + levelIconSize;

    //         int tempX = GetMousePosition().x, tempY = GetMousePosition().y;

    //         if (count < unlockedLevels.size())
    //         {
    //             DrawTexture(levelsTexture.at(count), x, y, WHITE);
    //             if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    //             {
    //                 if ((tempX >= x && tempX <= x + levelIconSize) && (tempY >= y && tempY <= y + levelIconSize))
    //                 {
    //                     string levelToRead = "level" + to_string(count + 1) + ".txt";
    //                     initializeLevel(levelToRead.c_str());
    //                     currentState = levels;
    //                 }
    //             }
    //         }
    //         else
    //             DrawTexture(lockedLevel, x, y, WHITE);
    //         count++;
    //     }
    // }
}
