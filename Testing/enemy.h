#ifndef ENEMY_H
#define ENEMY_H

#include "personages.h"

class Enemy : public Personages {
public:
    Enemy();

    Enemy(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height, int DistanceBetweenTiles,
          int CountFrames, TileMap& map, float PosX = 0, float PosY = 0, float Health = 100, float SpeedX = 0.3,
          float SpeedY = 0.35, int DistanceToPlayer = 400, int MovementArea = 400, float ScaleX = 0.296296296, float ScaleY = 0.296296296, int Damage = 49);

    virtual ~Enemy() { };

    Enemy &operator=(const Enemy& other);

    void update(sf::RenderWindow& window, float dTime)  override;
    void healthChange(int damage)                       override;  // = 0
    void setPosPlayer(float posX,float posY);

private:
    int damage;

    float elapsedTimeAfterShooting;

    float posXPlayer;
    float posYPlayer;

    int maxPosX;
    int minPosX;

    int distanceToPlayer;

    enum MainStateEnum          {Peace, Shooting}  mainState;
    enum DirectionStateEnum     {Left, Right}      directionState;

    void collisionX()                                    override;
    void collisionY()                                    override;
    void shoot()                                         override;  // = 0
    void recharge(sf::RenderWindow& window, float dTime) override;

    void drawControl();

    void stateDrop();
    void statePeace();
    void stateShooting();
};

#endif // ENEMY_H
