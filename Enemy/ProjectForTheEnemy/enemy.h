#ifndef ENEMY_H
#define ENEMY_H

#include "personages.h"

class Enemy : public Personages {
public:
    Enemy(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height,
          int DistanceBetweenTiles, float PosX, float PosY, float Health = 100, float SpeedX = 0.3, int distanceToPlayer = 400, int movementArea = 400);

    void update() override;
    void setPosPlayer(float posX,float posY);

private:
    float scaleX;
    float scaleY;

    float posXPlayer;
    float posYPlayer;

    int maxPosX;
    int minPosX;

    int distanceToPlayer;

    enum StateEnum {Peace, Shooting} state; //покой, стреляет
    enum DirectionEnum {Left, Right} direction;

    void collision()            override;  // = 0
    void healthChange()         override;  // = 0
    void motionFrameChange()    override;  // = 0

    void stateContol();

    void statePeace();
    void stateShooting();
};

#endif // ENEMY_H
