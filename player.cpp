#include "player.h"

Player::Player() : elapsedTimeAfterShooting(0), directionState(Right), mainState(Stand), gunState(NotGun) {
    // Инициализация полей родительского класса
    xInTexture = 0;
    yInTexture = 0;
    width = 0;
    height = 0;
    distanceBetweenTiles = 0;
    countFrames = 0;
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
    motionFrame = 0;

    bullet = nullptr;
}

Player::Player(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height,int DistanceBetweenTiles, int CountFrames,
               TileMap& map, float PosX, float PosY, float Health, float SpeedX, float SpeedY, float ScaleX, float ScaleY)
    : elapsedTimeAfterShooting(0), directionState(Right), mainState(Stand), gunState(NotGun) {
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

    bullet = nullptr;

    objectsOnMap = map.getAllObjects();

    // Добавление персонажа
    if(!texture.loadFromFile(filePath + "images/sprites/Luffy.png"))
        throw 1;

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture, width, height));
    sprite.setScale(scaleX,scaleY);
    sprite.setPosition(posX,posY);
}

Player& Player::operator=(const Player& other) {
    this->texture = other.texture;

    this->xInTexture = other.xInTexture;
    this->yInTexture = other.yInTexture;
    this->width = other.width;
    this->height = other.height;
    this->distanceBetweenTiles = other.distanceBetweenTiles;
    this->objectsOnMap = other.objectsOnMap;

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

    this->bullet = other.bullet;
    this->elapsedTimeAfterShooting = other.elapsedTimeAfterShooting;

    this->maxJumpHeight = other.maxJumpHeight;

    this->scaleX = other.scaleX;
    this->scaleY = other.scaleY;

    this->mainState = other.mainState;
    this->directionState = other.directionState;
    this->gunState = other.gunState;

    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(this->xInTexture, this->yInTexture, this->width, this->height));
    this->sprite.setScale(this->scaleX,this->scaleY);
    this->sprite.setPosition(this->posX,this->posY);

    return *this;
}

void Player::update() {
    elapsedTimeAfterShooting += dTime;

    if(elapsedTimeAfterShooting >= 500000. / 800){
        elapsedTimeAfterShooting = 500000. / 800;
    }

    if(bullet != nullptr && !bullet->getIsLive()){
        delete bullet;
        bullet = nullptr;
    }

    motionFrameChange();
    stateDrop();
    collisionX();

    drawControl();

    sprite.setPosition(posX,posY);
}

void Player::collisionX() {
    for (auto& object : objectsOnMap) {
        if(getRect().intersects(object.rect)) {
            if(object.name == "Ground") {
                if(currentSpeedX > 0) {
                    posX = object.rect.left - scaleX*width;
                    currentSpeedX = 0;
                }
                else if(currentSpeedX < 0) {
                    currentSpeedX = 0;
                    posX = object.rect.left + object.rect.width;
                }
            }
        }
    }
}

void Player::collisionY() {
    for (auto& object : objectsOnMap) {
        if(getRect().intersects(object.rect)) {
            if(object.name == "Ground") {
                if(currentSpeedY > 0) {
                    posY = object.rect.top - scaleY*height;
                    currentSpeedY = 0;
                    mainState = Stand;
                }
                else if(currentSpeedY < 0) {
                    posY = object.rect.top + object.rect.height;
                    currentSpeedY = 0;
                    mainState = Drop;
                }
            }
        }
    }
}

void Player::shoot() {
    if(bullet == nullptr && elapsedTimeAfterShooting >= 500000. / 800) {
        elapsedTimeAfterShooting = 0;
        switch (directionState) {
        case Left:
            bullet = new Bullet(filePath + "images/sprites/bullet.png", 0,0, 31, 13, 20, posX - scaleX * 167, posY + scaleY * 234, objectsOnMap, -0.5,400,0.3, 0.3);
            break;
        case Right:
            bullet = new Bullet(filePath + "images/sprites/bullet.png", 0,0, 31, 13, 20, posX + scaleX * 167, posY + scaleY * 234, objectsOnMap, 0.5,400,0.3, 0.3/*0.153846154*/);
            break;
        }
    }
}

void Player::healthChange() {
    //...
}

float Player::getPosX() {
    return posX;
}

float Player::getPosY() {
    return posY;
}

void Player::stateDrop() {
    if (mainState == Jump) {
        stateJump();
    }
    else {
        mainState = Drop;

        currentSpeedX = 0;
        currentSpeedY = speedY;

        posY += currentSpeedY * dTime;

        collisionY();

        if (mainState == Stand){
            stateStand();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            stateMovingRight();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            stateMovingLeft();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) || sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            shoot();
        }
    }
}

void Player::stateStand() {
    currentSpeedX = 0;
    currentSpeedY = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
        changeGunState();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        maxJumpHeight = posY - scaleY * height;
        stateJump();        mainState = Jump;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        stateMovingRight(); mainState = MovingRight;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        stateMovingLeft();  mainState = MovingLeft;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) || sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        shoot();
    }
}

void Player::stateMovingLeft() {
    directionState = Left;

    currentSpeedY = 0;
    currentSpeedX = -speedX;

    posX += currentSpeedX * dTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) || sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        shoot();
    }
}

void Player::stateMovingRight() {
    directionState = Right;

    currentSpeedY = 0;
    currentSpeedX = speedX;

    posX += currentSpeedX * dTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) || sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        shoot();
    }
}

void Player::stateJump() {
    currentSpeedX = 0;
    currentSpeedY = -speedY;

    posY += currentSpeedY * dTime;

    if(posY < maxJumpHeight) {
        posY = maxJumpHeight;
        mainState = Drop;
    }

    collisionY();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        stateMovingRight();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        stateMovingLeft();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) || sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        shoot();
    }
}

void Player::changeGunState() {
    if(gunState == WithGun){
        gunState = NotGun;
    }
    else {
        gunState = WithGun;
    }
}

void Player::drawControl() {
    if(gunState == NotGun) {
        if (directionState == Left){
            switch (mainState) {
            case Stand:
                sprite.setTextureRect(sf::IntRect(xInTexture + width, yInTexture, -width, height));  break;

            case MovingRight:
                sprite.setTextureRect(sf::IntRect(xInTexture + (distanceBetweenTiles + width) * int(motionFrame),
                                                  yInTexture, width, height));                       break;

            case MovingLeft:
                sprite.setTextureRect(sf::IntRect(xInTexture + (distanceBetweenTiles + width) * int(motionFrame) + width,
                                                  yInTexture, -width, height));                      break;

            case Jump:
                sprite.setTextureRect(sf::IntRect(xInTexture + width, yInTexture, -width, height));  break;

            case Drop:
                sprite.setTextureRect(sf::IntRect(xInTexture + width, yInTexture, -width, height));  break;
            }
        }
        else { //directionState == Right
            switch (mainState) {
            case Stand:
                sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture, width, height));           break;

            case MovingRight:
                sprite.setTextureRect(sf::IntRect(xInTexture + (distanceBetweenTiles + width) * int(motionFrame),
                                                  yInTexture, width, height));                       break;

            case MovingLeft:
                sprite.setTextureRect(sf::IntRect(xInTexture + (distanceBetweenTiles + width) * int(motionFrame) + width,
                                                  yInTexture, -width, height));                      break;

            case Jump:
                sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture, width, height));           break;

            case Drop:
                sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture, width, height));           break;
            }
        }
    }
    else { //gunState == WithGun
        sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture, width, height)); // заглушка
    }
}
