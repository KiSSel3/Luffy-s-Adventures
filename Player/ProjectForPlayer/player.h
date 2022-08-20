#ifndef PLAYER_H
#define PLAYER_H

#include "personages.h"

class Player : public Personages {
public:
    Player();

    Player(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height,
           int DistanceBetweenTiles, float PosX = 0, float PosY = 0, float Health = 100,
           float SpeedX = 0.3, float scaleX = 0.3, float scaleY = 0.3);

    virtual  ~Player() { };

    Player& operator=(const Player& other);

    void update() override ;

    float getPosX();
    float getPosY();

private:
    int maxJumpHeight;
    float scaleX;
    float scaleY;

    enum StateEnum {Stand, MovingLeft, MovingRight, Jump, Drop,
                    StandGun, MovingLeftGun, MovingRightGun, JumpGun, DropGun,
                   } state;

    enum DirectionEnum {Right, Left} direction;

    void collision()            override;  // = 0
    void healthChange()         override;  // = 0
    void motionFrameChange()    override;  // = 0

    void stateControl();

    void stateStand(DirectionEnum& direction);
    void stateMovingLeft();
    void stateMovingRight();
    void stateJump();
    void stateDrop();
    void stateStandGun();
    void stateMovingLeftGun();
    void stateMovingRightGun();
    void stateJumpGun();
    void stateDropGun();
};

#endif // PLAYER_H
