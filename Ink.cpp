#include "Ink.h"

Ink::Ink(int x, int y, int radius, int circleDetail)
{
	Position.x = x;
	Position.y = y;
	this->Radius = radius;

	CreateCircle(circleDetail);
}

void Ink::CreateCircle(int circleDetail)
{
	auto slice = 2 * M_PI / circleDetail;
	for (size_t i = 0; i < circleDetail; i++)
	{
		auto angle = slice * i;
		auto v = sf::Vector2f(cos(angle), sin(angle));
		v.x *= this->Radius;
		v.y *= this->Radius;

		v.x += Position.x;
		v.y += Position.y;

		vertices.push_back(v);
	}
}

void Ink::Draw(sf::RenderWindow& window)
{
	sf::VertexArray vertexArray(sf::TriangleFan, vertices.size());
	
	for (size_t i = 0; i < vertices.size(); i++)
	{
		vertexArray[i] = (vertices[i]);
		vertexArray[i].color = color;
	}
	window.draw(vertexArray);
}

void Ink::Marble(Ink other)
{
	for (auto& vert : vertices)
	{
		// our p
		vert = vert - other.Position;

		auto magnitude = sqrt(vert.x * vert.x + vert.y * vert.y);

		auto root = sqrt(1 + pow(other.Radius, 2) / pow(magnitude, 2));

		vert.x *= root;
		vert.y *= root;

		vert += other.Position;
	}
}

bool Ink::VertsOutOfWindow(sf::RenderWindow& window)
{
	auto counter = 0;
	for (auto& vert : vertices)
	{
		if (vert.x > window.getSize().x * 1.5
			|| vert.y > window.getSize().y * 1.5
			|| vert.x < 0
			|| vert.y < 0)
		{
			counter++;
		}
	}

	if (counter >= vertices.size())
	{
		return true;
	}

	return false;
}
