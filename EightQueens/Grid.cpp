#include "Grid.h"
#include "Global.h"

Grid::Grid()
{
	defaultTileColor = sf::Color::White;
}

Grid::~Grid()
{
}

void Grid::CreateGrid(int width, int height)
{
	float size = 0;

	// Calculate the maximum possible size for both width and height
	float maxTileWidth = (float)(WINDOW_WIDTH / width);
	float maxTileHeight = (float)(WINDOW_HEIGHT / height);

	// All tiles should be squares so we will
	// select the smaller size if they are not equal
	if (maxTileWidth <= maxTileHeight)
	{
		size = maxTileWidth;
	}
	else
	{
		size = maxTileHeight;
	}
	
	// Set up the template for each location in the grid
	sf::RectangleShape tile(sf::Vector2f(size, size));
	tile.setFillColor(defaultTileColor);
	tile.setOutlineColor(sf::Color::Black);
	tile.setOutlineThickness(1.0f);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			tile.setPosition(j * size, i * size);
			tileList.push_back(tile);
		}
	}
}

void Grid::Update(sf::RenderWindow& window)
{
	float mousePosX = sf::Mouse::getPosition(window).x;
	float mousePosY = sf::Mouse::getPosition(window).y;

	// Highlight the cell the mouse is in
	for (std::vector<sf::RectangleShape>::iterator it = tileList.begin(); it != tileList.end(); ++it)
	{
		float cellPosX = (*it).getPosition().x;
		float cellPosY = (*it).getPosition().y;
		float size = (*it).getSize().x;

		if (mousePosX < (cellPosX + size) && mousePosX > cellPosX && 
			mousePosY < (cellPosY + size) && mousePosY > cellPosY)
		{
			(*it).setFillColor(sf::Color(60, 200, 255));
		}
		else
		{
			(*it).setFillColor(defaultTileColor);
		}
	}
}

std::vector<sf::RectangleShape> Grid::GetTiles()
{
	return tileList;
}