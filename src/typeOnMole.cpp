#include "game.h"
#include "MainMenuScreen.h"

/*
    Screen.h k parameterized function mai error aa rha hai
    
*/

// MAIN FUNCTION
//--------------------------------------------------------------------------------------
int main()
{
    const int screenWidth = 1200, screenHeight = 600;

    // Initialization
    //--------------------------------------------------------------------------------------
    Game game(screenWidth, screenHeight, 60, "Type On A Mole");
    //--------------------------------------------------------------------------------------
    
    Screen * mainMenu = new MainMenuScreen(game);

    game.changeScreen(mainMenu);
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
