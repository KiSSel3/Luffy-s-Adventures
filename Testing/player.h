#ifndef PLAYER_H
#define PLAYER_H

#include "personages.h"

class Player : public Personages {
public:
    Player();

    Player(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height,
           int DistanceBetweenTiles, int CountFrames, TileMap& map, float PosX = 0, float PosY = 0, float Health = 100,
           float SpeedX = 0.3, float SpeedY = 0.35, float ScaleX = 0.3, float ScaleY = 0.3);

    virtual  ~Player() { };

    Player& operator=(const Player& other);

    void update(sf::RenderWindow& window) override ;

    float getPosX();
    float getPosY();

private:
    int maxJumpHeight;

    enum DirectionStateEnum {Right, Left}                                 directionState;
    enum MainStateEnum      {Stand, MovingLeft, MovingRight, Jump, Drop}  mainState;
    enum GunStateEnum       {NotGun, WithGun}                             gunState;

    void mainStateControl();
    void stateStand();
    void stateMovingLeft();
    void stateMovingRight();
    void stateJump();
    void stateDrop();

    void changeGunState();

    void collisionX()        override;
    void collisionY()        override;
    void healthChange()      override;  // = 0
    void motionFrameChange() override;  // = 0
};

#endif // PLAYER_H
