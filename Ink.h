#pragma once

#include <SFML/Graphics.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

class Ink
{
	//int circleDetail = 10;
	sf::Color color = sf::Color(rand() % 256, rand() % 256, rand() % 256, 255);
	
	void CreateCircle(int circleDetail);

public:
	sf::Vector2f Position;
	int Radius;
	std::vector<sf::Vector2f> vertices;

	Ink(int x, int y, int radius, int circleDetail);

	void Draw(sf::RenderWindow& window);
	void Marble(Ink other);
	bool VertsOutOfWindow(sf::RenderWindow& window);
};
