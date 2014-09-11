#include "Tile.hpp"

Tile::Tile()
{
	id = -1;
	fprintf(stdout, "Tile id = %d\n", id);
	boundingRect.setSize(sf::Vector2<float>(size,size));
	boundingRect.setFillColor(sf::Color::White);
	boundingRect.setOutlineColor(sf::Color::Black);
	boundingRect.setOutlineThickness(1.0f);
	isOccupied = false;
	size = 0.0f;
	color = sf::Color::White;
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

sf::Color Tile::GetColor()
{
	return color;
}

void Tile::SetColor(sf::Color c)
{
	boundingRect.setFillColor(c);
	//sprite.setColor(c);
	color = c;
}