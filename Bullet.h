#pragma once

#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable {

private:

	sf::Texture texture;
	sf::Sprite sprite;

	int xInTexture; 
	int yInTexture;
	int width;
	int height;
	int maxFlightLength;
	int damage;

	float posX;
	float posY;
	float speedX;
	float dTime;
	float timeLimit;
	float recharge;

	float scaleX;
	float scaleY;

    enum StateBullet {Flying, Calm} stateBullet;

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override final;
	
public:

	Bullet(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height, 
		                int Damage, float PosX, float PosY, float SpeedX, float Recharge = 2000000, int MaxFlightLength = 200, float ScaleX = 0.3, float ScaleY = 0.3);
	Bullet();

	void shot(bool direction);
	void dTimeSet(float dTime);

	int getDamage();
	int getWidth();
	int getHeight();

	float getPosX();
	float getPosY();


    StateBullet getStateBullet();
};

