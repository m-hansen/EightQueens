#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Grid
{
public:
	Grid();
	~Grid();
	std::vector<sf::RectangleShape> Grid::GetTiles();
	void CreateGrid(int width, int height);
	void Update(sf::RenderWindow& window);
private:
	std::vector<sf::RectangleShape> tileList;
	sf::Color defaultTileColor;
};