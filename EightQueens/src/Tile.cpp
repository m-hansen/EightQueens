#include "Tile.hpp"

Tile::Tile()
{
	boundingRect.setSize(sf::Vector2<float>(size,size));
	boundingRect.setFillColor(sf::Color::White);
	boundingRect.setOutlineColor(sf::Color::Black);
	boundingRect.setOutlineThickness(1.0f);
	marker.setRadius(size/3);
	marker.setFillColor(sf::Color::Green);
	marker.setOutlineColor(sf::Color::Black);
	marker.setOutlineThickness(1.0f);
	isOccupied = false;
	size = 0.0f;
}

Tile::~Tile()
{
}

void Tile::Render(sf::RenderWindow* window)
{
	window->draw(boundingRect);
	if (isOccupied)
	{
		window->draw(sprite);
	}
}

bool Tile::IsOccupied()
{
	return isOccupied;
}

void Tile::SetAsOccupied(bool occupied)
{
	isOccupied = occupied;
}

sf::Vector2<float> Tile::GetPosition()
{
	return position;
}

void Tile::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	boundingRect.setPosition(position);
}

//sf::Color Tile::GetColor()
//{
//	return color;
//}

void Tile::SetColor(sf::Color color)
{
	boundingRect.setFillColor(color);
}