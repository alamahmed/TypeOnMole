#include "preProcessors.h"

class Sprite
{

    public:
    Sprite(Texture2D texture,Vector2 position, Vector2 size);
    void setPosition(Vector2 position);
    void setXPosition(float positionX);
    void setYPosition(float positionY);
    void setSize(Vector2 size);
    void setTexture(Texture2D texture);
    Vector2 getPosition();
    Vector2 getSize();
    Vector2 getTexture();
    void draw();

    private:
    Vector2 position, size;
    Texture2D texture;

};
