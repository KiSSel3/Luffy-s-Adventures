#include "Bullet.h"

Bullet::Bullet(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height,
    int Damage, float PosX, float PosY, float SpeedX, float Recharge, int MaxFlightLength, float ScaleX, float ScaleY)
    : xInTexture(XInTexture), yInTexture(YInTexture), width(Width), height(Height), maxFlightLength(MaxFlightLength),
    damage(Damage), posX(PosX), posY(PosY), speedX(SpeedX), recharge(Recharge), scaleX(ScaleX), scaleY(ScaleY) {

    dTime = 0;
    timeLimit = 0;

    stateBullet = Calm;

    if (!texture.loadFromFile(FilePath)) {
        throw 1;
    }

    sprite.setTexture(texture);
    sprite.setScale(scaleX, scaleY);
}

Bullet::Bullet() : xInTexture(0), yInTexture(0), width(0), height(0), maxFlightLength(0),
damage(0), posX(0), posY(0), speedX(0), recharge(0), scaleX(0), scaleY(0) {

    dTime = 0;
    timeLimit = 0;

    stateBullet = Calm;
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates state) const {
    target.draw(sprite, state);
}

void Bullet::shot(bool direction) {

    if (stateBullet == Calm) {
        timeLimit += dTime;

        if (timeLimit > recharge) {
            stateBullet = Flying;
        }
    }
    else {
        if (direction) {
            this->posX += speedX * dTime;

            sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture, width, height));
        }
        else {
            this->posX -= speedX * dTime;

            sprite.setTextureRect(sf::IntRect(xInTexture + width, yInTexture, -width, height));
        }

        timeLimit = 0;
       
    }
}

void Bullet::dTimeSet(float dTime) {
    this->dTime = dTime;
}

float Bullet::getPosX() {
    return posX;
}
float Bullet::getPosY() {
    return posY;
}

int Bullet::getWidth() {
    return width;
}
int Bullet::getHeight() {
    return height;
}
int Bullet::getDamage() {
    return damage;
}

Bullet::StateBullet Bullet::getStateBullet() {
    return stateBullet;
}