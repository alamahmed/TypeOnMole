#include "game.h"
#include <string>
#include <raylib.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
using std::cout;
using std::to_string;
using std::string;
using std::vector;

Game::Game(int width, int height, int fps, string title)
{
    SetTargetFPS(fps);
    InitWindow(width, height, title.c_str());
    readLvl("level.txt");
    srand(time(0));
}

Game::~Game() noexcept
{
    CloseWindow();
}

bool Game::gameShouldClose() const
{
    return WindowShouldClose();
}

void Game::tick()
{
    calcTime();
    BeginDrawing();
    Update();
    Draw();
    EndDrawing();
}

void Game::Draw()
{
    ClearBackground(BLACK);
    DrawFPS(10, 20);
    renderLevel();
}

void Game::calcTime()
{
    if(seconds == delay && frames == 0)
        generateKey();
    if(seconds == delay + interval)
    {
        seconds = 0;
        key = 0;
    }
    frames++;
    if(frames == 60)
    {
        seconds++;
        frames = 0;
    }
}

void Game::Update()
{
    // renderLevel();
}

void Game::readLvl(string levelName)
{
    std::ifstream level("src/" + levelName);
    vector<vector<char> > lvl;
    string line;
    if(!level)
        cout << "Failed to read file " << levelName << "\n";
    while (getline(level, line))
    {
        vector <char> temp;

        std::copy(line.begin(), line.end(), std::back_inserter(temp));

        lvl.push_back(temp);
    }
    currentLevel = lvl;
}

inline void Game::generateKey()
{
    key = 97 + rand() % (122 - 98);
    interval = 4 + rand() % (8 - 2);
}

void Game::renderLevel()
{
    // -------------------------------------------------------------------------------------
    ClearBackground(RAYWHITE);
    if(seconds == delay)
        holes = { 0, 121, 241, 255 };           // BLUE Mole Is Up
    if(seconds < delay)
        holes = { 230, 41, 55, 255 };           // RED Mole Is Down
    if(seconds >= delay && seconds <= interval)
    {
        if(IsKeyPressed(key - 32))
        {
            seconds = 0;
            key = 0;
            score++;
        }   
    }
        
    // ADDING BACKGROUND COLOR
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), RAYWHITE);
    // --------------------------------------------------------------------------------------

    // --------------------------------------------------------------------------------------
    // Draw Text
    string keyToPress(1, char(key));
    DrawText(keyToPress.c_str(), 10, 10, 50, BLACK);
    string totalScore = "SCORE : " + to_string(score);
    DrawText(totalScore.c_str(), 100, 20, 50, BLACK);
    // --------------------------------------------------------------------------------------
    
    // --------------------------------------------------------------------------------------
    // DRAW LEVEL
    for(int i = 0; i < int(currentLevel.size()); i++)
    {
        for(int j = 0; j < int(currentLevel.at(i).size()); j++)
        {
            if(currentLevel.at(i).at(j) == '1')
                DrawCircle(i * 30 + 350, j * 30 + 200, 15, holes);
            else
                DrawCircle(i * 30 + 350, j * 30 + 200, 15, BLACK);
        }
    }
}

