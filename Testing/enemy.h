#ifndef ENEMY_H
#define ENEMY_H

#include "personages.h"

class Enemy : public Personages {
public:
    Enemy();

    Enemy(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height,
          int DistanceBetweenTiles, TileMap& map, float PosX = 0, float PosY = 0, float Health = 100, float SpeedX = 0.3,
          int DistanceToPlayer = 400, int MovementArea = 400, float ScaleX = 0.3, float ScaleY = 0.3);

    virtual ~Enemy() { };

    Enemy &operator=(const Enemy& other);

    void update(sf::RenderWindow& window) override;
    void setPosPlayer(float posX,float posY);

private:
    float posXPlayer;
    float posYPlayer;

    int maxPosX;
    int minPosX;

    int distanceToPlayer;

    enum StateEnum {Peace, Shooting} state; //покой, стреляет
    enum DirectionEnum {Left, Right} direction;

    void collisionX()           override;  // = 0
    void collisionY()           override;  // = 0
    void healthChange()         override;  // = 0
    void motionFrameChange()    override;  // = 0

    void stateContol();

    void statePeace();
    void stateShooting();
};

#endif // ENEMY_H
