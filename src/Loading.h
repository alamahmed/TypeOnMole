#ifndef LOADING
#define LOADING

#include "Screen.h"
#include "MainMenuScreen.h"


class Loading : public Screen
{

    public:
    Loading();
    Loading(Game *game);
    ~Loading();
    void initializeVariables();
    void loadTextures();
    void unloadTextures();
    void update();
    void draw();
    private:
    int totalNoOfFrames, currentFrame;
    Texture2D FirstTexture, FinalTexture;

};

#endif //LOADING