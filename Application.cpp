#include <iostream>
#include "Application.h"

Application::Application()
	: window(sf::VideoMode(1200, 800), "Paper Marbler")
{
	font.loadFromFile("arial.ttf");
	inkDropsAmount.setFont(font);
	inkDropsAmount.setCharacterSize(24);
	inkDropsAmount.setFillColor(sf::Color::Red);
}

void Application::Run()
{
	window.setFramerateLimit(60);

	bool mouseHold = false;
	int erasedCount = 0;
	int x = 0, y = 0;

	while (window.isOpen())
	{
		HandleEvents(mouseHold, x, y);

		for (size_t i = 0; i < inkDrops.size(); i++)
		{
			if (inkDrops[i].VertsOutOfWindow(window)) {
				inkDrops.erase(inkDrops.begin() + i);
				erasedCount++;
				std::cout << "erase# " <<  std::to_string(erasedCount) << "\n";
			}
		}

		// draw
		window.clear();
		

		// draw everything here
		// EVERYTHING
		for (auto& ink : inkDrops)
		{
			ink.Draw(window);
		}

		inkDropsAmount.setString(std::to_string(inkDrops.size()));
		window.draw(inkDropsAmount);


		window.display();
	}
}

void Application::HandleEvents(bool& mouseHold, int& x, int& y)
{
	int circleDetail = 100;

	// Get events
	sf::Event evt;
	while (window.pollEvent(evt))
	{
		if (evt.type == sf::Event::Closed)
		{
			window.close();
		}

		if (evt.mouseButton.button == sf::Mouse::Button::Left)
		{
			if (evt.type == sf::Event::MouseButtonReleased)
			{
				auto pos = sf::Mouse::getPosition(window);
				DropInk(pos.x, pos.y, 50, circleDetail);
			}
		}
		else if (evt.mouseButton.button == sf::Mouse::Button::Right)
		{
			if (evt.type == sf::Event::MouseButtonPressed)
			{
				mouseHold = true;
			}
			if (evt.type == sf::Event::MouseButtonReleased)
			{
				mouseHold = false;
			}
		}

		if (evt.type == evt.KeyReleased)
		{
			if (evt.key.code == sf::Keyboard::Up)
			{
				circleDetail++;
			}
			if (evt.key.code == sf::Keyboard::Down)
			{
				circleDetail--;
			}
		}
	}

	if (mouseHold)
	{
		auto pos = sf::Mouse::getPosition(window);
		DropInk(pos.x, pos.y, rand() % 50 + 10, circleDetail);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		DropInk(rand() % window.getSize().x, rand() % window.getSize().y, rand() % 50 + 10, circleDetail);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		FramePoints(x, y, window);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		inkDrops.clear();
	}
}

void Application::DropInk(int x, int y, int radius, int circleDetail)
{
	Ink drop(x, y, radius, circleDetail);
	for (auto& other : inkDrops)
	{
		other.Marble(drop);
	}
	inkDrops.push_back(drop);
}

void Application::FramePoints(int& x, int& y, sf::RenderWindow& window)
{
	int innerFrame = 0;
	auto wX = window.getSize().x;
	auto wY = window.getSize().y;
	int stepSize = 10;
	
	int offset = 100;
	innerFrame += offset;
	wX -= offset;
	wY -= offset;

	if (y <= wY && x <= innerFrame)
	{
		y += stepSize;
	}
	if (y >= wY && x <= wX)
	{
		x += stepSize;
	}
	if (y >= innerFrame && x >= wX)
	{
		y -= stepSize;
	}
	if (y <= innerFrame && x >= innerFrame)
	{
		x -= stepSize;
	}

	DropInk(x, y, 50, 100);
}
