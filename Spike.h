#pragma once

#include "SFML/Graphics.hpp"

class Spike : public sf::Drawable {

private:

	sf::Texture texture;
	sf::Sprite sprite;

	int xInTexture;
	int yInTexture;
	int width;
	int height;

	float posX;
	float posY;
	float dTime;
	float frameLimit;
	float scaleX;
	float scaleY;
	float motionFrame;

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override final;

public:

	Spike(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height,
		float PosX, float PosY, float SpeedX = 0, float ScaleX = 0.5, float ScaleY = 0.5);
	Spike();

	void update(float dTime);
	void dTimeSet(float dTime);

	int getWidth();
	int getHeight();

	float getPosX();
	float getPosY();

	sf::FloatRect getRect();

	Spike& operator= (const Spike& other);

};