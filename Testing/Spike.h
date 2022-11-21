#pragma once

#include "SFML/Graphics.hpp"
#include "Entity.h"

class Spike : public Entity {

private:

	float frameLimit;

public:

	Spike(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height,
		float PosX, float PosY, float ScaleX = 0.5, float ScaleY = 0.5);
	Spike();

	void update(sf::RenderWindow& window, float dTime) override;

	void dTimeSet(float dTime);

	int getWidth();
	int getHeight();

	float getPosX();
	float getPosY();

	sf::FloatRect getRect();

	Spike& operator= (const Spike& other);

};