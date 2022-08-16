#ifndef PLAYER_H
#define PLAYER_H

#include "personages.h"

class Player : public Personages {
public:
    Player(std::string Path, int XInTexture, int YInTexture, int Width, int Height,
           int DistanceBetweenTiles, float PosX, float PosY,float Health, float SpeedX);

    void update() override ;

private:
    int maxJumpHeight;
    float scaleX;
    float scaleY;

    enum StateEnum {Stand, MovingLeft, MovingRight, Jump, Drop,
                    StandGun, MovingLeftGun, MovingRightGun, JumpGun, DropGun,
                   } state;

    void collision()            override;  // = 0
    void healthChange()         override;  // = 0
    void motionFrameChange()    override;  // = 0

    void stateControl();

    void stateStand();
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
