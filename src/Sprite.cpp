#include "Sprite.h"

Sprite::Sprite()
{
    
}
Sprite::Sprite(Texture2D texture, Vector2 position, Vector2 size)
    :
    texture(texture),
    position(position),
    size(size)
{
    setSize(size);
}

Sprite::~Sprite()
{
    UnloadTexture(texture);
}

void Sprite::setPosition(Vector2 position)
{
    this->position = position;
}

void Sprite::setXPosition(float positionX)
{
    this -> position.x = positionX;
}

void Sprite::setYPosition(float positionY)
{
    this -> position.y = positionY;
}

void Sprite::setSize(Vector2 size)
{
    texture.width = size.x;
    texture.height = size.y;
    this->size = size;
}
void Sprite::setTexture(Texture2D texture)
{
    this->texture = texture;
}

Texture2D Sprite::getTexture()
{
    return texture;
}

Vector2 Sprite::getPosition()
{
    return this->position;
}

Vector2 Sprite::getSize()
{
    return this->size;
}
void Sprite::draw(){
    DrawTexture(this->texture,this->position.x,this->position.y,WHITE);
}
