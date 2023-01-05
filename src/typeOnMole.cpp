#include "game.h"
#include "Loading.h"

// MAIN FUNCTION
//--------------------------------------------------------------------------------------
int main()
{
    const int screenWidth = 1200, screenHeight = 600;

    // Initialization
    //--------------------------------------------------------------------------------------
    Game * game = new Game(screenWidth, screenHeight, 60, "Type On A Mole");
    //--------------------------------------------------------------------------------------
    
    Screen * loading = new Loading(game);
    // Screen * s = new Survival(game, "level0");

    game -> changeScreen(loading);
    // game -> changeScreen(s);
    // Main game loop
    while (!game->gameShouldClose()) // Detect window close button or ESC key
    {
        game->tick();
    }

    //--------------------------------------------------------------------------------------
    // CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
