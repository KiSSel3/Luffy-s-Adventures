#include "Spike.h"

Spike::Spike(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height,
    float PosX, float PosY, float ScaleX, float ScaleY) {

    xInTexture = XInTexture;
    yInTexture = YInTexture;
    width = Width;
    height = Height;
    posX = PosX;
    posY = PosY;
    scaleX = ScaleX;
    scaleY = ScaleY;

    dTime = 0;
    frameLimit = 0;
    motionFrame = 0;

    if (!texture.loadFromFile(FilePath + "images/Sprites/Spike.png")) {
        throw 1;
    }

    sprite.setTexture(texture);
    sprite.setScale(scaleX, scaleY);
    sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture, width, height));
    sprite.setPosition(posX, posY);
}

Spike::Spike() {

    xInTexture = 0;
    yInTexture = 0;
    width = 0;
    height = 0;
    posX = 0;
    posY = 0;
    scaleX = 0;
    scaleY = 0;
    dTime = 0;
    frameLimit = 0;
    motionFrame = 0;
}

void Spike::update(sf::RenderWindow& window, float dTime)
{
    motionFrame += dTime * 0.0025;

    if (motionFrame > 3) {
        motionFrame = 0;
    }

    sprite.setTextureRect(sf::IntRect(xInTexture + width * int(motionFrame), yInTexture, width, height));

    sprite.setPosition(posX, posY);

    window.draw(sprite);
}

sf::FloatRect Spike::getRect() {

    return sf::FloatRect(posX, posY, scaleX * width, scaleY * height);
}

void Spike::dTimeSet(float dTime) {
    this->dTime = dTime;
}

float Spike::getPosX() {
    return posX;
}
float Spike::getPosY() {
    return posY;
}

int Spike::getWidth() {
    return width;
}
int Spike::getHeight() {
    return height;
}

Spike& Spike::operator=(const Spike& other) {

    this->texture = other.texture;
    this->xInTexture = other.xInTexture;
    this->yInTexture = other.yInTexture;
    this->width = other.width;
    this->height = other.height;
    this->posX = other.posX;
    this->posY = other.posY;
    this->dTime = other.dTime;
    this->frameLimit = other.frameLimit;
    this->scaleX = other.scaleX;
    this->scaleY = other.scaleY;
    this->motionFrame = other.motionFrame;

    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(this->xInTexture, this->yInTexture, this->width, this->height));
    this->sprite.setScale(this->scaleX, this->scaleY);
    this->sprite.setPosition(this->posX, this->posY);

    return *this;
}
