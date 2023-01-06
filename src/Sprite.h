#ifndef SPRITE
#define SPRITE
#include "preProcessors.h"

class Sprite
{
    public:
    Sprite();
    Sprite(Texture2D texture,Vector2 position, Vector2 size);
    ~Sprite();
    void setPosition(Vector2 position);
    void setXPosition(float positionX);
    void setYPosition(float positionY);
    void setSize(Vector2 size);
    void setTexture(Texture2D texture);
    Vector2 getPosition();
    Vector2 getSize();
    Texture2D getTexture();
    void draw();

    private:
    Vector2 position, size;
    Texture2D texture;

};

#endif //SPRITE
