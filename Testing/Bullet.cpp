#include "Bullet.h"

Bullet::Bullet(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height,
               int Damage, float PosX, float PosY, std::vector<Object>& ObjectsOnMap, float SpeedX, int MaxFlightLength, float ScaleX, float ScaleY)
    : isLive(true), xInTexture(XInTexture), yInTexture(YInTexture), width(Width), height(Height), maxFlightLength(MaxFlightLength),
      damage(Damage), posX(PosX), posY(PosY), speedX(SpeedX), scaleX(ScaleX), scaleY(ScaleY) {

    if (!texture.loadFromFile(FilePath + "images/Sprites/Bullet.png")) {
        throw 1;
    }

    maxPosX = posX + maxFlightLength;
    minPosX = posX - maxFlightLength;

    objectsOnMap = ObjectsOnMap;

    sprite.setTexture(texture);

    if(speedX > 0){
        sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture, width, height));
    }
    else {
        sprite.setTextureRect(sf::IntRect(xInTexture + width, yInTexture, -width, height));
    }

    sprite.setScale(scaleX,scaleY);
    sprite.setPosition(posX,posY);
}

Bullet &Bullet::operator=(const Bullet &other) {
    this->isLive = other.isLive;

    this->texture = other.texture;

    this->xInTexture = other.xInTexture;
    this->yInTexture = other.yInTexture;
    this->width = other.width;
    this->height = other.height;

    this->maxFlightLength = other.maxFlightLength;
    this->damage = other.damage;

    this->posX = other.posX;
    this->posY = other.posY;
    this->speedX = other.speedX;

    this->scaleX = other.scaleX;
    this->scaleY = other.scaleY;

    this->maxPosX = other.maxPosX;
    this->minPosX = other.minPosX;

    this->objectsOnMap = other.objectsOnMap;

    this->sprite.setTexture(this->texture);

    if(speedX > 0){
        this->sprite.setTextureRect(sf::IntRect(this->xInTexture, this->yInTexture, this->width, this->height));
    }
    else {
        this->sprite.setTextureRect(sf::IntRect(this->xInTexture + this->width, this->yInTexture, -(this->width), this->height));
    }

    this->sprite.setScale(this->scaleX,this->scaleY);
    this->sprite.setPosition(this->posX,this->posY);

    return *this;
}

bool Bullet::getIsLive() {
    return isLive;
}

void Bullet::changeIsLive() {
    isLive = false;
}

void Bullet::update(sf::RenderWindow &window, float dTime) {
    if(posX > maxPosX || posX < minPosX) {
        isLive = false;
    }
    else {
        posX += speedX * dTime;

        collision();

        sprite.setPosition(posX, posY);
        window.draw(sprite);
    }
}

void Bullet::collision() {
    for (auto& object : objectsOnMap) {
        if(getRect().intersects(object.rect)) {
            if(object.name == "ground") {
                if(speedX > 0) {
                    posX = object.rect.left - scaleX*width;
                }
                else if(speedX < 0) {
                    posX = object.rect.left + object.rect.width;
                }

                isLive = false;
            }
        }
    }
}

int Bullet::getDamage() {
    return damage;
}

sf::FloatRect Bullet::getRect() {
    return sf::FloatRect(posX, posY, scaleX*width, scaleY*height);
}

