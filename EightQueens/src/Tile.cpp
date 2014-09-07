#include "Tile.hpp"

Tile::Tile()
{
	boundingRect.setSize(sf::Vector2<float>(size,size));
	boundingRect.setFillColor(sf::Color::White);
	boundingRect.setOutlineColor(sf::Color::Black);
	boundingRect.setOutlineThickness(1.0f);
	isOccupied = false;
	size = 0.0f;
}

Tile::~Tile()
{
}

void Tile::TempFix()
{
	sprite.setTexture(texture);
}

void Tile::LoadResources()
{
	std::string textName = "resources/crown.jpg";
	if (!texture.loadFromFile(textName))
	{
		// error
		fprintf(stdout, "Error loading %s\n", textName.c_str());
	}

	sprite.setTexture(texture);
	const int spriteWidth = 100;
	float factor = size / spriteWidth;
	sprite.setScale(factor, factor);
	//sprite.setColor(sf::Color::Black);
	//sprite.setTextureRect(sf::IntRect(100, 100, 320, 320));
}

void Tile::Render(sf::RenderWindow* window)
{
	if (isOccupied)
	{
		sprite.setPosition(position);
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