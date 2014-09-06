#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Global.h"

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Eight Queens");

	// Create an 8x8 Grid
	Grid grid;
	grid.CreateGrid(8, 8);

	// Main loop
	while (window.isOpen())
	{
		sf::Event event;

		// Event loop
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		grid.Update(window);

		window.clear();
		// Draw the grid
		for (int i = 0; i < grid.GetTiles().size(); i++)
		{
			window.draw(grid.GetTiles().at(i));
		}

		window.display();
	}

	return 0;
}