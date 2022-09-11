#pragma once

#include "SFML/Graphics.hpp"
#include "Entity.h"

class Fruit : public Entity {
public:
	Fruit(std::string FilePath, int XInTexture, int YInTexture, int Width, int Height,
		float PosX, float PosY, float ScaleX = 1, float ScaleY = 1);
	Fruit();

	void update(sf::RenderWindow& window, float dTime) override;

	int getWidth();
	int getHeight();

	float getPosX();
	float getPosY();

	sf::FloatRect getRect();

	Fruit& operator= (const Fruit& other);
};

