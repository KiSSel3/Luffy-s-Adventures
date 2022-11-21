#pragma once

#include "SFML/Graphics.hpp"
#include "Entity.h"

class Coin : public Entity {
public:
    Coin(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height,
         float PosX, float PosY, float ScaleX = 1, float ScaleY = 1);
    Coin();

    void update(sf::RenderWindow& window, float dTime) override;

    void dTimeSet(float dTime);

    int getWidth();
    int getHeight();

    float getPosX();
    float getPosY();

    void setPosX(float PosX);

    sf::FloatRect getRect();

    Coin& operator= (const Coin& other);
};
