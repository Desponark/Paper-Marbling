#pragma once

#include <SFML/Graphics.hpp>
#include "Ink.h"


class Application
{
	sf::RenderWindow window;
	std::vector<Ink> inkDrops;
	sf::Font font;
	sf::Text inkDropsAmount;

public:
	Application();

	void Run();
	void HandleEvents(bool& mouseHold, int& x, int& y);
	void DropInk(int x, int y, int radius, int circleDetail);
	void FramePoints(int& x, int& y, sf::RenderWindow& window);
};

