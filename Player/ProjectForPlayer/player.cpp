#include "player.h"

Player::Player() : scaleX(0), scaleY(0), state(Drop) {
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

Player::Player(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height,
               int DistanceBetweenTiles, float PosX, float PosY, float Health, float SpeedX, float ScaleX, float ScaleY)
    : scaleX(ScaleX), scaleY(ScaleY), state(Drop), direction(Right) {

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

    // Добавление персонажа
    if(!texture.loadFromFile(FilePath))
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

    this->posX = other.posX;
    this->posY = other.posY;

    this->health = other.health;

    this->speedX = other.speedX;

    this->dTime = other.dTime;

    this->motionFrame = other.motionFrame;

    this->maxJumpHeight = other.maxJumpHeight;

    this->scaleX = other.scaleX;
    this->scaleY = other.scaleY;

    this->state = other.state;
    this->direction = other.direction;

    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(this->xInTexture, this->yInTexture, this->width, this->height));
    this->sprite.setScale(this->scaleX,this->scaleY);
    this->sprite.setPosition(this->posX,this->posY);

    return *this;
}

void Player::update() {
    motionFrameChange();
    stateControl();

    sprite.setPosition(posX,posY);
}

void Player::collision() {
    //...
}

void Player::healthChange() {
    //...
}

void Player::motionFrameChange() {
    motionFrame += 0.005 * dTime;

    if (motionFrame > 4){
        motionFrame = 0;
    }
}

void Player::stateControl() {
    switch (state) {
    case Stand:
        stateStand(direction);  break;

    case MovingRight:
        stateMovingRight();     break;

    case MovingLeft:
        stateMovingLeft();      break;

    case Jump:
        stateJump();            break;

    case Drop:
        stateDrop();            break;

    case StandGun:
        stateStandGun();        break;

    case MovingRightGun:
        stateMovingRightGun();  break;

    case MovingLeftGun:
        stateMovingLeftGun();   break;

    case JumpGun:
        stateJumpGun();         break;

    case DropGun:
        stateDropGun();         break;
    }
}

void Player::stateStand(DirectionEnum& direction) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
        state = StandGun;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        state = Jump;
        maxJumpHeight = posY - scaleY * height;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        state = MovingRight;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        state = MovingLeft;
    }
    else if (direction == Right){
        sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture, width, height));
    }
    else if (direction == Left){
        sprite.setTextureRect(sf::IntRect(xInTexture + width, yInTexture, -width, height));
    }
}

void Player::stateMovingLeft() {
    posX -= dTime * speedX;
    state = Stand;
    direction = Left;

    sprite.setTextureRect(sf::IntRect(xInTexture + (distanceBetweenTiles + width) * int(motionFrame) + width, yInTexture, -width, height));
}

void Player::stateMovingRight() {
    posX += dTime * speedX;
    state = Stand;
    direction = Right;

    sprite.setTextureRect(sf::IntRect(xInTexture + (distanceBetweenTiles + width) * int(motionFrame), yInTexture, width, height));
}

void Player::stateJump() {
    if(posY> maxJumpHeight){
        posY -= dTime * 0.35;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            posX += dTime * speedX;
            direction = Right;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            posX -= dTime * speedX;
            direction = Left;
        }
    }
    else {
        state = Drop;
    }

    if (direction == Right){
        sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture, width, height));
    }
    else if (direction == Left){
        sprite.setTextureRect(sf::IntRect(xInTexture + width, yInTexture, -width, height));
    }
}

void Player::stateDrop() {
    if(posY+scaleY*height >1080){
        posY = 1080 - scaleY * height;
        state = Stand;
    }
    else {
        posY += dTime * 0.2;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            posX += dTime * speedX;
            direction = Right;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            posX -= dTime * speedX;
            direction = Left;
        }
    }

    if (direction == Right){
        sprite.setTextureRect(sf::IntRect(xInTexture, yInTexture, width, height));
    }
    else if (direction == Left){
        sprite.setTextureRect(sf::IntRect(xInTexture + width, yInTexture, -width, height));
    }
}

void Player::stateStandGun() {
    state = Stand; // заглушка
}

void Player::stateMovingLeftGun() {
    state = Stand; // заглушка
}

void Player::stateMovingRightGun() {
    state = Stand; // заглушка
}

void Player::stateJumpGun() {
    state = Stand; // заглушка
}

void Player::stateDropGun() {
    state = Stand; // заглушка
}
