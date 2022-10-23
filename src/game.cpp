#include "game.h"
#include <string>
#include <raylib.h>
#include <assert.h>

// g++ Game.cpp -std=c++20 `pkg-config --libs --cflags raylib` -o Game

Game::Game(int width, int height, int fps, std::string title)
{
    assert(!GetWindowHandle());               // If assertion Triggers : Window is already opened
    SetTargetFPS(fps);
    InitWindow(width, height, title.c_str());
}

Game::~Game() noexcept
{
    assert(GetWindowHandle());               // If assertion Triggers : Window is already Closed
    CloseWindow();
}

bool Game::GameShouldClose() const
{
    return WindowShouldClose();
}
void Game::Tick()
{
    BeginDrawing();
    Update();
    Draw();
    EndDrawing();
}

void Game::Draw()
{
    ClearBackground(BLACK);
    DrawFPS(10, 20);
}

void Game::Update()
{

}
