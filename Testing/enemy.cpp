#include "enemy.h"

Enemy::Enemy()  : elapsedTimeAfterShooting(0), posXPlayer(0), posYPlayer(0), maxPosX(0), minPosX(0), distanceToPlayer(0), mainState(Peace), directionState(Right) {
    // Инициализация полей родительского класса
    xInTexture = 0;
    yInTexture = 0;
    width = 0;
    height = 0;
    distanceBetweenTiles = 0;
    scaleX = 0;
    scaleY = 0;
    posX = 0;
    posY = 0;
    health = 0;
    speedX = 0;
    speedY = 0;
    currentSpeedX = 0;
    currentSpeedY = 0;
    dTime = 0;
    countFrames = 0;
    motionFrame = 0;

    damage = 0;

    isLive = true;

    bullet = nullptr;
}

Enemy::Enemy(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height, int DistanceBetweenTiles,
             int CountFrames, TileMap& map, float PosX, float PosY, float Health, float SpeedX, float SpeedY,
             int DistanceToPlayer, int MovementArea, float ScaleX, float ScaleY, int Damage)
    : damage(Damage), elapsedTimeAfterShooting(0), distanceToPlayer(DistanceToPlayer), mainState(Peace), directionState(Right) {

    // Инициализация полей родительского класса

    filePath = FilePath;
    xInTexture = XInTexture;
    yInTexture = YInTexture;
    width = Width;
    height = Height;
    distanceBetweenTiles = DistanceBetweenTiles;
    scaleX = ScaleX;
    scaleY = ScaleY;
    posX = PosX;
    posY = PosY;
    health = Health;
    speedX = SpeedX;
    speedY = SpeedY;
    currentSpeedX = 0;
    currentSpeedY = 0;
    dTime = 0;
    countFrames = CountFrames;
    motionFrame = 0;

    objectsOnMap = map.getAllObjects();

    maxPosX = PosX + MovementArea;
    minPosX = PosX;

    isLive = true;

    bullet = nullptr;

    // Добавление врага
    if(!texture.loadFromFile(FilePath + "images/Sprites/Enemy.png"))
        throw 1;

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture, width, height));
    sprite.setScale(scaleX,scaleY);
    sprite.setPosition(posX,posY);

    //Звук
    shootBuffer.loadFromFile(FilePath + "sound/Shoot.ogg");
    shootSound.setBuffer(shootBuffer);
}

Enemy &Enemy::operator=(const Enemy &other) {
    this->filePath = other.filePath;

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
    this->speedY = other.speedY;
    this->currentSpeedX = other.currentSpeedX;
    this->currentSpeedY = other.currentSpeedY;

    this->dTime = other.dTime;

    this->countFrames = other.countFrames;
    this->motionFrame = other.motionFrame;

    this->objectsOnMap = other.objectsOnMap;

    this->scaleX = other.scaleX;
    this->scaleY = other.scaleY;

    this->posXPlayer = other.posXPlayer;
    this->posYPlayer = other.posYPlayer;

    this->maxPosX = other.maxPosX;
    this->minPosX = other.minPosX;

    this->distanceToPlayer = other.distanceToPlayer;

    this->mainState = other.mainState;
    this->directionState = other.directionState;

    this->bullet = other.bullet;

    this->elapsedTimeAfterShooting = other.elapsedTimeAfterShooting;

    this->isLive = other.isLive;

    this->damage = other.damage;

    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(this->xInTexture, this->yInTexture, this->width, this->height));
    this->sprite.setScale(this->scaleX,this->scaleY);
    this->sprite.setPosition(this->posX,this->posY);

    this->shootBuffer = other.shootBuffer;
    this->shootSound.setBuffer(this->shootBuffer);

    return *this;
}

void Enemy::setPosPlayer(float posX, float posY) {
    posXPlayer = posX;
    posYPlayer = posY;
}

void Enemy::collisionX() {
    for (auto& object : objectsOnMap) {
        if(getRect().intersects(object.rect)) {
            if(object.name == "ground") {
                if(currentSpeedX > 0) {
                    posX = object.rect.left - scaleX*width;
                    currentSpeedX = 0;

                    directionState = Left;
                }
                else if(currentSpeedX < 0) {
                    posX = object.rect.left + object.rect.width;
                    currentSpeedX = 0;

                    directionState = Right;
                }
            }
        }
    }
}

void Enemy::collisionY() {
    for (auto& object : objectsOnMap) {
        if(getRect().intersects(object.rect)) {
            if(object.name == "ground") {
                if(currentSpeedY > 0) {
                    posY = object.rect.top - scaleY*height;
                    currentSpeedY = 0;
                }
            }
        }
    }
}

void Enemy::update(sf::RenderWindow& window, float dTime) {
    this->dTime = dTime;
    recharge(window, dTime);

    motionFrameChange();
    drawControl();

    stateDrop();

    sprite.setPosition(posX, posY);
    window.draw(sprite);
}

void Enemy::drawControl() {
    if (directionState == Right){
        switch(mainState){
        case Peace:
            sprite.setTextureRect(sf::IntRect(xInTexture + (distanceBetweenTiles + width) * int(motionFrame),
                                              yInTexture, width, height));                        break;
        case Shooting:
            sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture, width, height));            break;
        }
    }
    else { // directionState == Left
        switch(mainState){
        case Peace:
            sprite.setTextureRect(sf::IntRect(xInTexture + (distanceBetweenTiles + width) * int(motionFrame) + width,
                                              yInTexture, -width, height));                       break;
        case Shooting:
            sprite.setTextureRect(sf::IntRect(xInTexture + width, yInTexture, -width, height));   break;
        }
    }

}

void Enemy::stateDrop() {
    currentSpeedX = 0;
    currentSpeedY = speedY;

    posY += currentSpeedY * dTime;

    collisionY();

    switch (mainState){
    case Peace:
        statePeace();     break;
    case Shooting:
        stateShooting();  break;
    }
}

void Enemy::statePeace() {
    switch (directionState) {
    case Right:
        currentSpeedX = speedX;
        posX += currentSpeedX * dTime;

        if (posX > maxPosX){
            directionState = Left;
        }
        break;

    case Left:
        currentSpeedX = -speedX;
        posX += currentSpeedX * dTime;

        if(posX < minPosX){
            directionState = Right;
        }
        break;
    }

    collisionX();

    if (posXPlayer > posX - distanceToPlayer && posXPlayer < posX + distanceToPlayer && posYPlayer >= posY - (height * scaleY) / 2 && posYPlayer <= posY + (height * scaleY) / 2){
        mainState = Shooting;
    }
}

void Enemy::stateShooting() {
    if (posX>posXPlayer) {
        directionState = Left;
    }
    else {
        directionState = Right;
    }

    shoot();

    if (posXPlayer < posX - distanceToPlayer || posXPlayer > posX + distanceToPlayer ||  posYPlayer < posY - (height * scaleY) || posYPlayer > posY + (height * scaleY) / 2){
        mainState = Peace;
    }
}

void Enemy::shoot() {
    if(bullet == nullptr && elapsedTimeAfterShooting >= 625) {
        shootSound.play();

        switch (directionState) {
        case Left:
            bullet = new Bullet(filePath, 0,0, 31, 13, damage, posX - scaleX * 216, posY + scaleY * 218, objectsOnMap, -0.5,400,0.3, 0.3);
            break;
        case Right:
            bullet = new Bullet(filePath, 0,0, 31, 13, damage, posX + scaleX * 216, posY + scaleY * 218, objectsOnMap, 0.5,400,0.3, 0.3/*0.153846154*/);
            break;
        }

        elapsedTimeAfterShooting = 0;
    }
}

void Enemy::recharge(sf::RenderWindow &window, float dTime) {
    if(elapsedTimeAfterShooting < 625){
        elapsedTimeAfterShooting += dTime;
    }

    if(bullet != nullptr && !bullet->getIsLive()){
        delete bullet;
        bullet = nullptr;
    }
    else if(bullet != nullptr && bullet->getIsLive()) {
        bullet->update(window, dTime);
    }
}

void Enemy::healthChange(int damage) {
    health -= damage;
    if(health <= 0){
        isLive = false;
    }
}




