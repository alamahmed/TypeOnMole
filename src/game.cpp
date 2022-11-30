#include "game.h"
#include <string>
#include <raylib.h>
// #include <assert.h>
#include <vector>
#include <fstream>
#include <iostream>
using std::cout;
using std::to_string;
using std::string;
using std::ifstream;
using std::vector;
using std::copy;
using std::back_inserter;

// g++ Game.cpp -std=c++20 `pkg-config --libs --cflags raylib` -o Game

Game::Game(int width, int height, int fps, string title)
{
    // assert(!GetWindowHandle());               // If assertion Triggers : Window is already opened
    SetTargetFPS(fps);
    InitWindow(width, height, title.c_str());
    readLvl("level.txt");
}

Game::~Game() noexcept
{
    // assert(GetWindowHandle());               // If assertion Triggers : Window is already Closed
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
    // DrawCircle(GetMousePosition().x, GetMousePosition().y, 30 ,RED);
    renderLevel();
}

void Game::Update()
{
    // renderLevel();
}

void Game::readLvl(string levelName)
{
    ifstream level("src/" + levelName);
    vector<vector<char> > lvl;
    string line;
    if(!level)
        cout << "Failed to read file " << levelName << "\n";
    while (getline(level, line))
    {
        vector <char> temp;

        copy(line.begin(), line.end(), back_inserter(temp));

        lvl.push_back(temp);
    }
    currentLevel = lvl;
}

void Game::renderLevel()
{
    // -------------------------------------------------------------------------------------
    ClearBackground(RAYWHITE);
    // ADDING BACKGROUND COLOR
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), RAYWHITE);
    // --------------------------------------------------------------------------------------

    // --------------------------------------------------------------------------------------
    // Draw Text
    int levelNum = 1;
    string levelName = "LEVEL " + to_string(levelNum);
    DrawText(levelName.c_str(), 0, 0, 50, BLACK);
    // --------------------------------------------------------------------------------------
    
    // --------------------------------------------------------------------------------------
    // DRAW LEVEL
    for(int i = 0; i < int(currentLevel.size()); i++)
    {
        for(int j = 0; j < int(currentLevel.at(i).size()); j++)
        {
            if(currentLevel.at(i).at(j) == '1')
                DrawCircle(i * 30 + 350, j * 30 + 200, 15, BLACK);
            else
                DrawCircle(i * 30 + 350, j * 30 + 200, 15, RED);
        }
    }
}

