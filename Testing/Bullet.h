#ifndef BULLET_H
#define BULLET_H

#include "map.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Bullet {
public:
    Bullet() : isLive(false), xInTexture(0), yInTexture(0), width(0), height(0), maxFlightLength(0),
        damage(0), posX(0), posY(0), speedX(0), scaleX(0), scaleY(0), maxPosX(0), minPosX(0) { };

    Bullet(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height, int Damage, float PosX,
           float PosY, std::vector<Object>& ObjectsOnMap, float SpeedX, int MaxFlightLength = 200, float ScaleX = 0.3, float ScaleY = 0.3);

    ~Bullet() { };

    Bullet &operator=(const Bullet& other);

    bool getIsLive();
    void changeIsLive();

    void update(sf::RenderWindow &window, float dTime);

    int getDamage();

    sf::FloatRect getRect();

private:
    bool isLive;

    sf::Texture texture;
    sf::Sprite sprite;

    int xInTexture;
    int yInTexture;
    int width;
    int height;
    int maxFlightLength;
    int damage;

    float posX;
    float posY;
    float speedX;

    float scaleX;
    float scaleY;

    int maxPosX;
    int minPosX;

    std::vector<Object> objectsOnMap;

    void collision();
};

#endif //BULLET_H

