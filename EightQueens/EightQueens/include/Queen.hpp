#pragma once
#include "SFML/Graphics.hpp"

class Queen
{
public:
	Queen();
	~Queen();
private:
	void LoadResources();
	sf::Sprite sprite;
};