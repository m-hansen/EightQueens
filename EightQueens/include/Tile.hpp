#pragma once
#include <stdio.h>
#include <SFML/Graphics.hpp>

class Tile
{
public:
	Tile();
	~Tile();
	void LoadResources();
	void Render(sf::RenderWindow* window);
	bool IsOccupied();
	void SetAsOccupied(bool occupied);
	sf::Vector2<float> GetPosition();
	void SetPosition(float x, float y);
	sf::Color GetColor();
	void SetColor(sf::Color c);
	float size;
	sf::RectangleShape boundingRect;
	sf::Texture texture;
	sf::Sprite sprite;
private:
	bool isOccupied;
	sf::Vector2<float> position;
};