#include "personages.h"

void Personages::draw(sf::RenderTarget &target, sf::RenderStates state) const {
    target.draw(sprite, state);
}

void Personages::dTimeSet(float dTime) {
    this->dTime = dTime;
}

void Personages::speedChange(float speedX) {
    this->speedX = speedX;
}

sf::FloatRect Personages::getRect() {
    return sf::FloatRect(posX, posY, scaleX*width, scaleY*height);
}

