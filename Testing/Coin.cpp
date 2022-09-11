#include "Coin.h"

Coin::Coin(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height,
           float PosX, float PosY, float ScaleX, float ScaleY) {
    filePath = FilePath;
    xInTexture = XInTexture;
    yInTexture = YInTexture;
    width = Width;
    height = Height;
    scaleX = ScaleX;
    scaleY = ScaleY;
    posX = PosX;
    posY = PosY;
    dTime = 0;
    motionFrame = 0;

    if (!texture.loadFromFile(FilePath + "images/Sprites/Coin.png")) {
        throw 1;
    }

    sprite.setTexture(texture);
    sprite.setScale(scaleX, scaleY);
    sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture, width, height));
    sprite.setPosition(posX, posY);
}

Coin::Coin() {
    xInTexture = 0;
    yInTexture = 0;
    width = 0;
    height = 0;
    scaleX = 0;
    scaleY = 0;
    posX = 0;
    posY = 0;
    dTime = 0;
    motionFrame = 0;
}

void Coin::update(sf::RenderWindow& window, float dTime)
{
    motionFrame += dTime * 0.005;

    if (motionFrame > 4) {
        motionFrame = 0;
    }

    sprite.setTextureRect(sf::IntRect(xInTexture + width * int(motionFrame), yInTexture, width, height));

    sprite.setPosition(posX, posY);

    window.draw(sprite);
}

sf::FloatRect Coin::getRect() {
    return sf::FloatRect(posX, posY, scaleX * width, scaleY * height);
}

void Coin::dTimeSet(float dTime) {
    this->dTime = dTime;
}

float Coin::getPosX() {
    return posX;
}
float Coin::getPosY() {
    return posY;
}

void Coin::setPosX(float PosX) {
    posX = PosX;
}

int Coin::getWidth() {
    return width;
}
int Coin::getHeight() {
    return height;
}

Coin& Coin::operator=(const Coin &other) {

    this->texture = other.texture;
    this->xInTexture = other.xInTexture;
    this->yInTexture = other.yInTexture;
    this->width = other.width;
    this->height = other.height;
    this->posX = other.posX;
    this->posY = other.posY;
    this->dTime = other.dTime;
    this->scaleX = other.scaleX;
    this->scaleY = other.scaleY;
    this->motionFrame = other.motionFrame;

    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(this->xInTexture, this->yInTexture, this->width, this->height));
    this->sprite.setScale(this->scaleX, this->scaleY);
    this->sprite.setPosition(this->posX, this->posY);

    return *this;
}
