#include "Fruit.h"

Fruit::Fruit(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height,
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

    if (!texture.loadFromFile(FilePath + "images/Sprites.png")) {
        throw 1;
    }

    sprite.setTexture(texture);
    sprite.setScale(scaleX, scaleY);
    sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture, width, height));
    sprite.setPosition(posX, posY);
}

Fruit::Fruit () {
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

void Fruit::update(sf::RenderWindow& window, float dTime) {
    sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture, width, height));
    sprite.setPosition(posX, posY);
    window.draw(sprite);
}

sf::FloatRect Fruit::getRect() {
    return sf::FloatRect(posX, posY, scaleX * width, scaleY * height);
}

float Fruit::getPosX() {
    return posX;
}
float Fruit::getPosY() {
    return posY;
}

int Fruit::getWidth() {
    return width;
}
int Fruit::getHeight() {
    return height;
}

Fruit & Fruit::operator=(const Fruit & other) {
    this->texture = other.texture;
    this->xInTexture = other.xInTexture;
    this->yInTexture = other.yInTexture;
    this->width = other.width;
    this->height = other.height;
    this->posX = other.posX;
    this->posY = other.posY;
    this->scaleX = other.scaleX;
    this->scaleY = other.scaleY;

    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(this->xInTexture, this->yInTexture, this->width, this->height));
    this->sprite.setScale(this->scaleX, this->scaleY);
    this->sprite.setPosition(this->posX, this->posY);

    return *this;
}
