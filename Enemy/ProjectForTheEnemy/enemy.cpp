#include "enemy.h"

Enemy::Enemy() : scaleX(0), scaleY(0), posXPlayer(0), posYPlayer(0), maxPosX(0), minPosX(0), distanceToPlayer(0), state(Peace), direction(Right) {
    // Инициализация полей родительского класса
    xInTexture = 0;
    yInTexture = 0;
    width = 0;
    height = 0;
    distanceBetweenTiles = 0;
    posX = 0;
    posY = 0;
    health = 0;
    speedX = 0;
    dTime = 0;
    motionFrame = 0;
}

Enemy::Enemy(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height, int DistanceBetweenTiles, float PosX,
             float PosY, float Health, float SpeedX, int distanceToPlayer, int movementArea, float scaleX, float scaleY)
    : scaleX(scaleX), scaleY(scaleY), distanceToPlayer(distanceToPlayer), state(Peace), direction(Right) {

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

Enemy &Enemy::operator=(const Enemy &other) {
    this->texture = other.texture;

    this->xInTexture = other.xInTexture;
    this->yInTexture = other.yInTexture;
    this->width = other.width;
    this->height = other.height;
    this->distanceBetweenTiles = other.distanceBetweenTiles;

    this->posX = other.posX;
    this->posY = other.posY;

    this->health = other.health;

    this->speedX = other.speedX;

    this->dTime = other.dTime;

    this->motionFrame = other.motionFrame;

    this->scaleX = other.scaleX;
    this->scaleY = other.scaleY;

    this->posXPlayer = other.posXPlayer;
    this->posYPlayer = other.posYPlayer;

    this->maxPosX = other.maxPosX;
    this->minPosX = other.minPosX;

    this->distanceToPlayer = other.distanceToPlayer;

    this->state = other.state;
    this->direction = other.direction;

    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(this->xInTexture, this->yInTexture, this->width, this->height));
    this->sprite.setScale(this->scaleX,this->scaleY);
    this->sprite.setPosition(this->posX,this->posY);

    return *this;
}

void Enemy::setPosPlayer(float posX, float posY) {
    posXPlayer = posX;
    posYPlayer = posY;
}

void Enemy::update() {
    motionFrameChange();
    collision();
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
    switch (direction){
    case Right:
        if (posX>posXPlayer) {
            direction = Left;
        }

        // Bullet.shoot();

        sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture, width, height)); break;

    case Left:
        if (posX>posXPlayer) {
            direction = Right;
        }

        // Bullet.shoot();

        sprite.setTextureRect(sf::IntRect(xInTexture + width, yInTexture, -width, height)); break;
    }

    if (posXPlayer < posX - distanceToPlayer || posXPlayer > posX + distanceToPlayer){
        state = Peace;
    }
}

void Enemy::motionFrameChange() {
    motionFrame += 0.005 * dTime;

    if (motionFrame > 4){
        motionFrame = 0;
    }
}

void Enemy::collision() {
    if(posY+scaleY*height<1080){
        posY += 0.3 * dTime;
    }
}

void Enemy::healthChange()
{

}




