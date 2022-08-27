#pragma once

#include "SFML/Graphics.hpp"

class Coin : public sf::Drawable {

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

	Coin(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height,
		float PosX, float PosY, float SpeedX = 0, float ScaleX = 1, float ScaleY = 1);
	Coin();

	void update(float dTime);
	void dTimeSet(float dTime);

	int getWidth();
	int getHeight();

	float getPosX();
	float getPosY();

	sf::FloatRect getRect();

	Coin& operator= (const Coin& other);

};