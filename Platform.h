#pragma once

#include "SFML/Graphics.hpp"

class Platform : public sf::Drawable {

private:

	sf::Texture texture;
	sf::Sprite sprite;

	int xInTexture;
	int yInTexture;
	int width;
	int height;
	int maxFlightLength;

	float posX;
	float posY;
	float speedX;
	float speedY;
	float dTime;
	float timeLimit;
	float lengthLimit;

	float scaleX;
	float scaleY;

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override final;

public:

	Platform(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height, 
		float PosX, float PosY, float SpeedX = 0, float SpeedY = 0, int MaxFlightLength = 200, float ScaleX = 1, float ScaleY = 1);
	Platform();

	void moving(float dTime);
	void dTimeSet(float dTime);

	int getWidth();
	int getHeight();
	
	float getPosX();
	float getPosY();	

};

