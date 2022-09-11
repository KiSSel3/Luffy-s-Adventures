#include "Platform.h"

Platform::Platform(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height,
    float PosX, float PosY, float SpeedX, float SpeedY, int MaxFlightLength, float ScaleX, float ScaleY) {

    xInTexture = XInTexture;
    yInTexture = YInTexture;
    width = Width;
    height = Height;
    maxFlightLength = MaxFlightLength;
    posX = PosX;
    posY = PosY;
    speedX = SpeedX;
    speedY = SpeedY;
    scaleX = ScaleX;
    scaleY = ScaleY;

    dTime = 0;
    timeLimit = 0;
    lengthLimit = 0;

    if (!texture.loadFromFile(FilePath)) {
        throw 1;
    }

    sprite.setTexture(texture);
    sprite.setScale(scaleX, scaleY);
    sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture, width, height));
}

Platform::Platform() {

    xInTexture = 0;
    yInTexture = 0;
    width = 0;
    height = 0;
    maxFlightLength = 0;
    posX = 0;
    posY = 0;
    speedX = 0;
    speedY = 0;
    scaleX = 0;
    scaleY = 0;
    dTime = 0;
    timeLimit = 0;
    lengthLimit = 0;

}

void Platform::update(sf::RenderWindow& window, float dTime)
{
    posX += speedX * dTime;
    posY += speedY * dTime;

    lengthLimit += speedX * dTime;

    if (maxFlightLength < abs(lengthLimit)) {
        speedX *= -1;
        speedY *= -1;

        timeLimit = 0;
        lengthLimit = 0;
    }
    sprite.setPosition(posX, posY);

    window.draw(sprite);
}

sf::FloatRect Platform::getRect() {

    return sf::FloatRect(posX, posY, scaleX * width, scaleY * height);
}

void Platform::dTimeSet(float dTime) {
    this->dTime = dTime;
}

float Platform::getPosX() {
    return posX;
}
float Platform::getPosY() {
    return posY;
}

int Platform::getWidth() {
    return width;
}
int Platform::getHeight() {
    return height;
}

Platform& Platform::operator=(const Platform& other) {

    this->texture = other.texture;
    this->xInTexture = other.xInTexture;
    this->yInTexture = other.yInTexture;
    this->width = other.width;
    this->height = other.height;
    this->posX = other.posX;
    this->posY = other.posY;
    this->dTime = other.dTime;
    this->maxFlightLength = other.maxFlightLength;
    this->scaleX = other.scaleX;
    this->scaleY = other.scaleY;
    this->lengthLimit = other.lengthLimit;
    this->timeLimit = other.timeLimit;
    this->speedX = other.speedX;
    this->speedY = other.speedY;
    
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(this->xInTexture, this->yInTexture, this->width, this->height));
    this->sprite.setScale(this->scaleX, this->scaleY);
    this->sprite.setPosition(this->posX, this->posY);

    return *this;
}
