#include "Entity.h"

sf::FloatRect Entity::getRect() {
    return sf::FloatRect(posX, posY, scaleX * width, scaleY * height);
}

