#include "game.h"

Game::Game(){}

Game::Game(int width, int height, int fps, string title)
{
    SetTargetFPS(fps);
    InitWindow(width, height, title.c_str());
    currentScreen = NULL;
    unlockedLevels = 1;
}

Game::~Game() noexcept
{
    delete currentScreen;
    CloseWindow();
    UnloadTexture(gameOver);
}

void Game::setUnlockedLevels(int unlockedLevels)
{
    this -> unlockedLevels = unlockedLevels;
}

int Game::getUnlockedLevels()
{
    return unlockedLevels;
}

// void Game::loadTextures()
// {
//     gameOver = LoadTexture("./resources/gameOver.png");
//     gameOver.width = GetScreenWidth();
//     gameOver.height = GetScreenHeight();
// }

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
    if (currentScreen)
    {
        currentScreen -> ~Screen();
    }
    currentScreen = &(*screen);

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