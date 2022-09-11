#pragma once

#include "SFML/Graphics.hpp"
#include "Entity.h"

class Platform : public Entity {

private:

	int maxFlightLength;

	float speedX;
	float speedY;
	float timeLimit;
	float lengthLimit;

public:

	Platform(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height, 
		float PosX, float PosY, float SpeedX = 0, float SpeedY = 0, int MaxFlightLength = 200, float ScaleX = 1, float ScaleY = 1);
	Platform();

	void update(sf::RenderWindow& window, float dTime) override;

	void dTimeSet(float dTime);

	int getWidth();
	int getHeight();
	
	float getPosX();
	float getPosY();	

	sf::FloatRect getRect();

	Platform& operator= (const Platform& other);
};