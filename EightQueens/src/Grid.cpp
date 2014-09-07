#include "Grid.hpp"

Grid::Grid()
{
	defaultTileColor = sf::Color::White;
}

Grid::~Grid()
{
}

void Grid::CreateGrid(ResourceManager* rm, int width, int height)
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
	Tile tile;
	tile.size = size;
	//tile.LoadResources();
	
	sf::RectangleShape tileRect(sf::Vector2f(size, size));
	tileRect.setFillColor(defaultTileColor);
	tileRect.setOutlineColor(sf::Color::Black);
	tileRect.setOutlineThickness(1.0f);

	tile.boundingRect = tileRect;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			tile.SetPosition(j * size, i * size);
			tileList.push_back(tile);
			tileList.back().sprite.setTexture(*rm->GetTexture("resources/crown.jpg"));
			tileList.back().sprite.setPosition(sf::Vector2<float>(tile.GetPosition()));
		}
	}
}

void Grid::Update(sf::RenderWindow* window)
{
	float mousePosX = sf::Mouse::getPosition(*window).x;
	float mousePosY = sf::Mouse::getPosition(*window).y;

	// Highlight the cell the mouse is in
	for (std::vector<Tile>::iterator it = tileList.begin(); it != tileList.end(); ++it)
	{
		float cellPosX = it->GetPosition().x;
		float cellPosY = it->GetPosition().y;
		float size = it->size;

		if (mousePosX < (cellPosX + size) && mousePosX > cellPosX && 
			mousePosY < (cellPosY + size) && mousePosY > cellPosY)
		{
			it->SetColor(sf::Color(60, 200, 255));
		}
		else
		{
			it->SetColor(defaultTileColor);
		}
	}
}

Tile* Grid::GetMouseTileLocation(sf::RenderWindow* window)
{
	int mousePosX = sf::Mouse::getPosition(*window).x;
	int mousePosY = sf::Mouse::getPosition(*window).y;

	for (std::vector<Tile>::iterator it = tileList.begin(); it != tileList.end(); ++it)
	{
		float cellPosX = it->GetPosition().x;
		float cellPosY = it->GetPosition().y;

		if (mousePosX < (cellPosX + it->size) && mousePosX > cellPosX && 
			mousePosY < (cellPosY + it->size) && mousePosY > cellPosY)
		{
			return &(*it);
		}
	}
	return NULL;
}

void Grid::Render(sf::RenderWindow* window)
{
	for (std::vector<Tile>::iterator it = tileList.begin(); it != tileList.end(); ++it)
	{
		it->Render(window);
	}
}

void Grid::HandleMouseClick(sf::Event* event, sf::RenderWindow* window)
{
	// Check which grid space
	Tile* tile = GetMouseTileLocation(window);

	if (event->mouseButton.button == sf::Mouse::Left)
	{
		if (tile->IsOccupied())
		{
			tile->SetAsOccupied(false);
		}
		else
		{
			tile->SetAsOccupied(true);
		}
	}
}

std::vector<Tile>* Grid::GetTiles()
{
	return &tileList;
}