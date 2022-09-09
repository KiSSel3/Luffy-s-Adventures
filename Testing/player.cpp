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

    isLive = true;
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

    isLive = true;
    bullet = nullptr;

    objectsOnMap = map.getAllObjects();

    // Добавление персонажа
    if(!texture.loadFromFile(filePath + "images/sprites/Luffy.png"))
        throw 1;

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture, width, height));
    sprite.setScale(scaleX,scaleY);
    sprite.setPosition(posX,posY);

    //Звук
    shootBuffer.loadFromFile(FilePath + "sound/Shoot.ogg");
    shootSound.setBuffer(shootBuffer);

//    //Сердца
//    heartTexture.loadFromFile(filePath + "images/sprites/Heart.png");
//    for (short int i = 0, x = 0, y = 0; i < 5; ++i) {
//        sf::Sprite heartSprite;
//        heartSprite.setTexture(heartTexture);
//        heartSprite.setTextureRect(sf::IntRect(4, 8, 503, 462));
//        heartSprite.setScale(0.1,0.1);
//        heartSprite.setPosition(x, y);
//        heartList.push_back(heartSprite);

//        x+=100;
//    }
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

    this->isLive = other.isLive;

    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(this->xInTexture, this->yInTexture, this->width, this->height));
    this->sprite.setScale(this->scaleX,this->scaleY);
    this->sprite.setPosition(this->posX,this->posY);

    this->shootBuffer = other.shootBuffer;
    this->shootSound.setBuffer(this->shootBuffer);

//    this->heartTexture = other.heartTexture;
//    this->heartList = other.heartList;

    return *this;
}

void Player::update(sf::RenderWindow& window, float dTime) {
    this->dTime = dTime;
    recharge(window, dTime);

    motionFrameChange();
    stateDrop();
    collisionX();

    drawControl();
    sprite.setPosition(posX,posY);

//    for(auto& object : heartList){
//        window.draw(object);
//    }

    window.draw(sprite);
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
    if(bullet == nullptr && elapsedTimeAfterShooting >= 625) {
        shootSound.play();

        switch (directionState) {
        case Left:
            bullet = new Bullet(filePath, 0,0, 31, 13, 50, posX - scaleX * 186, posY + scaleY * 210, objectsOnMap, -0.5,450,0.3, 0.3);
            break;
        case Right:
            bullet = new Bullet(filePath, 0,0, 31, 13, 50, posX + scaleX * 186, posY + scaleY * 210, objectsOnMap, 0.5,450,0.3, 0.3/*0.153846154*/);
            break;
        }

        elapsedTimeAfterShooting = 0;
    }
}

void Player::recharge(sf::RenderWindow &window, float dTime) {
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

void Player::healthChange(int damage) {
    health -= damage;
    if(health <= 0){
        isLive = false;
    }
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
        else if (gunState == WithGun && (sf::Keyboard::isKeyPressed(sf::Keyboard::F) || sf::Mouse::isButtonPressed(sf::Mouse::Left))){
            shoot();
        }
    }
}

void Player::stateStand() {
    currentSpeedX = 0;
    currentSpeedY = 0;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        maxJumpHeight = posY - scaleY * height;
        stateJump();        mainState = Jump;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        stateMovingRight(); mainState = MovingRight;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        stateMovingLeft();  mainState = MovingLeft;
    }
    else if (gunState == WithGun && (sf::Keyboard::isKeyPressed(sf::Keyboard::F) || sf::Mouse::isButtonPressed(sf::Mouse::Left))){
        shoot();
    }
}

void Player::stateMovingLeft() {
    directionState = Left;

    currentSpeedY = 0;
    currentSpeedX = -speedX;

    posX += currentSpeedX * dTime;

    if (gunState == WithGun && (sf::Keyboard::isKeyPressed(sf::Keyboard::F) || sf::Mouse::isButtonPressed(sf::Mouse::Left))){
        shoot();
    }
}

void Player::stateMovingRight() {
    directionState = Right;

    currentSpeedY = 0;
    currentSpeedX = speedX;

    posX += currentSpeedX * dTime;

    if (gunState == WithGun && (sf::Keyboard::isKeyPressed(sf::Keyboard::F) || sf::Mouse::isButtonPressed(sf::Mouse::Left))){
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
    else if (gunState == WithGun && (sf::Keyboard::isKeyPressed(sf::Keyboard::F) || sf::Mouse::isButtonPressed(sf::Mouse::Left))){
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
                sprite.setTextureRect(sf::IntRect(xInTexture + width, yInTexture + height, -width, height));  break;

            case MovingRight:
                sprite.setTextureRect(sf::IntRect(xInTexture + (distanceBetweenTiles + width) * int(motionFrame),
                                                  yInTexture + height, width, height));                       break;

            case MovingLeft:
                sprite.setTextureRect(sf::IntRect(xInTexture + (distanceBetweenTiles + width) * int(motionFrame) + width,
                                                  yInTexture + height, -width, height));                      break;

            case Jump:
                sprite.setTextureRect(sf::IntRect(xInTexture + width, yInTexture + height, -width, height));  break;

            case Drop:
                sprite.setTextureRect(sf::IntRect(xInTexture + width, yInTexture + height, -width, height));  break;
            }
        }
        else { //directionState == Right
            switch (mainState) {
            case Stand:
                sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture + height, width, height));           break;

            case MovingRight:
                sprite.setTextureRect(sf::IntRect(xInTexture + (distanceBetweenTiles + width) * int(motionFrame),
                                                  yInTexture + height, width, height));                       break;

            case MovingLeft:
                sprite.setTextureRect(sf::IntRect(xInTexture + (distanceBetweenTiles + width) * int(motionFrame) + width,
                                                  yInTexture + height, -width, height));                      break;

            case Jump:
                sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture + height, width, height));           break;

            case Drop:
                sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture + height, width, height));           break;
            }
        }
    }
    else { //gunState == WithGun
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
}
