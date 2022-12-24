#include "game.h"

// MAIN FUNCTION
//--------------------------------------------------------------------------------------
int main()
{
    const int screenWidth = 1200, screenHeight = 600;

    // Initialization
    //--------------------------------------------------------------------------------------
    Game game(screenWidth, screenHeight, 60, "Type On A Mole");
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!game.gameShouldClose()) // Detect window close button or ESC key
    {
        game.tick();
    }

    //--------------------------------------------------------------------------------------
    // CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
