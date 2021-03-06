#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <vector>
#include "Global.hpp"
#include "ResourceManager.hpp"
#include "Tile.hpp"

class Grid
{
public:
	Grid();
	~Grid();
	std::vector<Tile>* GetTiles();
	void CreateGrid(ResourceManager* rm, int size);
	void CreateGrid(ResourceManager* rm, int width, int height);
	void ClearQueens();
	bool Solve(sf::RenderWindow* window);
	bool SolveRecursive(int col, sf::RenderWindow* window);
	void Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	Tile* GetMouseTileLocation(sf::RenderWindow* window);
	void HandleMouseClick(sf::Event* event, sf::RenderWindow* window);
	void ValidateAllTiles();
private:
	int size;
	std::vector<Tile> tileList;
	sf::Color defaultTileColor;
	std::map<int, Tile*> tileMap;
	bool IsValidMove(const int tileId);
};