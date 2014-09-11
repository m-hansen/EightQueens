#include "Grid.hpp"

Grid::Grid()
{
	defaultTileColor = sf::Color::White;
	size = 0;
}

Grid::~Grid()
{
}

void Grid::CreateGrid(ResourceManager* rm, int gridSize)
{
	size = gridSize;
	CreateGrid(rm, gridSize, gridSize);
}

void Grid::CreateGrid(ResourceManager* rm, int width, int height)
{
	float tileSize = 0;

	// Calculate the maximum possible size for both width and height
	float maxTileWidth = (float)(WINDOW_WIDTH / width);
	float maxTileHeight = (float)(WINDOW_HEIGHT / height);

	// All tiles should be squares so we will
	// select the smaller size if they are not equal
	if (maxTileWidth <= maxTileHeight)
	{
		tileSize = maxTileWidth;
	}
	else
	{
		tileSize = maxTileHeight;
	}
	
	// Set up the template for each location in the grid
	Tile tile;
	tile.size = tileSize;
	
	sf::RectangleShape tileRect(sf::Vector2f(tileSize, tileSize));
	tileRect.setFillColor(defaultTileColor);
	tileRect.setOutlineColor(sf::Color::Black);
	tileRect.setOutlineThickness(1.0f);

	tile.boundingRect = tileRect;

	int count = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			tile.id = count;
			fprintf(stdout, "id = %d\n", tile.id);
			tile.SetPosition(j * tileSize, i * tileSize);
			tileList.push_back(tile);
			tileList.back().sprite.setTexture(*rm->GetTexture("resources/crown.jpg"));
			tileList.back().sprite.setPosition(sf::Vector2<float>(tile.GetPosition()));
			tileMap.insert(std::make_pair(tileList.back().id, &tileList.back()));
			count++;
		}
	}
}

void Grid::ClearQueens()
{
	for (std::vector<Tile>::iterator it = tileList.begin(); it != tileList.end(); ++it)
	{
		it->SetAsOccupied(false);
	}
}

//bool Grid::Solve(const int tileId)
//{
//	Clear();
//
//	// if we have tried the last col
//	if ((tileId % size) >= size)
//	{
//		return true;
//	}
//	
//	
//
//	// Current col
//	for (int i = 0; i < size; i++)
//	{
//		
//		if (IsValidMove(tileId))
//		{
//			
//		}
//	}
//
//	int queensPlaced = 0;
//	if (queensPlaced < numQueens)
//	{
//		PlaceQueen();
//	}
//}

bool Grid::IsValidMove(const int tileId)
{
	int boardSize = size * size;

	// Calculate starting and ending indicies for each row, column, and diagonal
	int rowBeginIndex = tileId;
	while (rowBeginIndex % size != 0)
	{
		rowBeginIndex--;
	}

	int rowEndIndex = rowBeginIndex + size - 1;

	int colEndIndex = tileId;
	while (colEndIndex < (boardSize - size))
	{
		colEndIndex += size;
	}

	int colBeginIndex = tileId;
	while (colBeginIndex >= size)
	{
		colBeginIndex -= size;
	}

	int diagUpperLeft = tileId;
	while (diagUpperLeft >= (size+1))
	{
		diagUpperLeft -= (size+1);
	}

	int diagLowerRight = tileId;
	while (diagLowerRight < (boardSize-size+1))
	{
		diagLowerRight += (size+1);
	}

	int diagLowerLeft = tileId;
	while (diagLowerLeft % size != 0)
	{
		diagLowerLeft += (size-1);
	}

	int diagUpperRight = tileId;
	while ((diagUpperRight > (size-1)) && (diagUpperRight % size) != (size-1))//> (size-1))
	{
		diagUpperRight -= (size-1);
	}

	// construct the invalid id list
	std::vector<int> invalidIdList;

	// check each row
	for (int i = rowBeginIndex; i <= rowEndIndex; i++)
	{
		invalidIdList.push_back(i);
	}

	// check each col
	for (int i = colBeginIndex; i <= colEndIndex; i += size)
	{
		invalidIdList.push_back(i);
	}

	// check the diagonal from the top left to bottom right
	for (int i = diagUpperLeft; i <= diagLowerRight; i += (size+1))
	{
		invalidIdList.push_back(i);
	}

	// check the diagonal from the lower left to upper right
	for (int i = diagLowerLeft; i >= diagUpperRight; i -= (size-1))
	{
		invalidIdList.push_back(i);
	}

	// Check the list of conflicts
	for (std::vector<Tile>::iterator it = tileList.begin(); it != tileList.end(); ++it)
	{
		if (it->IsOccupied() && it->id != tileId)
		{
			for (std::vector<int>::iterator valIter = invalidIdList.begin(); valIter != invalidIdList.end(); ++valIter)
			{
				if (it->id == *valIter)
				{
					return false;
				}
			}
		}
	}

	return true;
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
			it->boundingRect.setFillColor(sf::Color(60, 200, 255));
			it->sprite.setColor(sf::Color(60, 200, 255));
		}
		else
		{
			it->boundingRect.setFillColor(it->GetColor());
			it->sprite.setColor(it->GetColor());
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

	if (tile != NULL && event->mouseButton.button == sf::Mouse::Left)
	{
		if (tile->IsOccupied())
		{
			tile->SetAsOccupied(false);
		}
		else
		{
			tile->SetAsOccupied(true);
			if (!IsValidMove(tile->id))
			{
				tile->SetColor(sf::Color::Red);
				fprintf(stdout, "Not a valid move!\n");
			}
		}
	}
}

std::vector<Tile>* Grid::GetTiles()
{
	return &tileList;
}