#include "personages.h"

void Personages::speedChange(float speedX) {
    this->speedX = speedX;
}

bool Personages::getIsLive() {
    return isLive;
}

sf::FloatRect Personages::getRect() {
    return sf::FloatRect(posX, posY, scaleX*width, scaleY*height);
}

Bullet *Personages::getBullet() {
    return bullet;
}

void Personages::motionFrameChange() {
    motionFrame += dTime * 0.005; // 0.005 оптимальная скорость изменения кадров

    if (motionFrame > countFrames) {
        motionFrame = 0;
    }
}

