#include "enemy.h"

Enemy::Enemy(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height,
             int DistanceBetweenTiles, float PosX, float PosY, float Health, float SpeedX, int distanceToPlayer, int movementArea)
    : scaleX(0.3), scaleY(0.3), distanceToPlayer(distanceToPlayer), state(Peace), direction(Right) {

    // Инициализация полей родительского класса
    xInTexture = XInTexture;
    yInTexture = YInTexture;
    width = Width;
    height = Height;
    distanceBetweenTiles = DistanceBetweenTiles;
    posX = PosX;
    posY = PosY;
    health = Health;
    speedX = SpeedX;
    dTime = 0;
    motionFrame = 0;

    maxPosX = PosX + movementArea;
    minPosX = PosX;

    // Добавление врага
    if(!texture.loadFromFile(FilePath))
        throw 1;

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture, width, height));
    sprite.setScale(scaleX,scaleY);
    sprite.setPosition(posX,posY);
}

void Enemy::setPosPlayer(float posX, float posY) {
    posXPlayer = posX;
    posYPlayer = posY;
}

void Enemy::update() {
    motionFrameChange();
    stateContol();

    sprite.setPosition(posX, posY);
}

void Enemy::stateContol() {
    switch (state){
    case Peace:
        statePeace(); break;

    case Shooting:
        stateShooting(); break;
    }
}

void Enemy::statePeace() {
    if (posXPlayer > posX - distanceToPlayer && posXPlayer < posX + distanceToPlayer){
        state = Shooting;
    }
    else {
        switch (direction) {
        case Right:
            posX += speedX*dTime;

            if (posX>maxPosX){
                direction = Left;
            }

            sprite.setTextureRect(sf::IntRect(xInTexture + (distanceBetweenTiles + width) * int(motionFrame), yInTexture, width, height)); break;

        case Left:
            posX -= speedX*dTime;

            if(posX<minPosX){
                direction = Right;
            }

            sprite.setTextureRect(sf::IntRect(xInTexture + (distanceBetweenTiles + width) * int(motionFrame) + width, yInTexture, -width, height)); break;
        }
    }
}

void Enemy::stateShooting() {

}

void Enemy::motionFrameChange() {
    motionFrame += 0.005 * dTime;

    if (motionFrame > 4){
        motionFrame = 0;
    }
}

void Enemy::collision()
{

}

void Enemy::healthChange()
{

}




