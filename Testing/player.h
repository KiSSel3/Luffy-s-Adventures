#ifndef PLAYER_H
#define PLAYER_H

#include "personages.h"

class Player : public Personages {
public:
    Player();

    Player(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height, /*int XInTextureGun, int YInTextureGun,
           int WidthGun,*/ int DistanceBetweenTiles, int CountFrames, TileMap& map, float PosX = 0, float PosY = 0, float Health = 100,
           float SpeedX = 0.3, float SpeedY = 0.35, float ScaleX = 0.296296296, float ScaleY = 0.296296296);

    Player& operator=(const Player& other);

    virtual  ~Player() { };

    void update(sf::RenderWindow& window, float dTime)  override;
    void healthChange(int damage)                       override;  // = 0

    void changeGunState();
    float getPosX();
    float getPosY();

    void changeCountCoin();

    int getHealth();
    int getCountCoin();

private:
    sf::Texture heartTexture; //временно

    std::list<sf::Sprite> heartList;

    int maxJumpHeight;
    float elapsedTimeAfterShooting;

    int xInTextureGun;
    int yInTextureGun;
    int widthGun;

    enum DirectionStateEnum {Right, Left}                                 directionState;
    enum MainStateEnum      {Stand, MovingLeft, MovingRight, Jump, Drop}  mainState;
    enum GunStateEnum       {NotGun, WithGun}                             gunState;

    int countCoin;

    void drawControl();

    void stateStand();
    void stateMovingLeft();
    void stateMovingRight();
    void stateJump();
    void stateDrop();

    void collisionX()                                    override;
    void collisionY()                                    override;
    void shoot()                                         override;  // = 0
    void recharge(sf::RenderWindow& window, float dTime) override;
};

#endif // PLAYER_H
