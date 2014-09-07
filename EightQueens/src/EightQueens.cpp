#include <SFML/Graphics.hpp>
#include "Global.hpp"
#include "Grid.hpp"
#include "ResourceManager.hpp"

void Render(sf::RenderWindow* window, Grid* grid);

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Eight Queens");

	ResourceManager resourceManager;
	//resourceManager.GetTexture("resources/crown.jpg");

	// Create an 8x8 Grid
	Grid grid;
	grid.CreateGrid(&resourceManager, 8, 8);

	// Main loop
	while (window.isOpen())
	{
		sf::Event event;

		// Event loop
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::MouseMoved:
					grid.Update(&window);
					break;

				case sf::Event::MouseButtonPressed:
					grid.HandleMouseClick(&event, &window);
					break;

				default:
					break;
			}
		}

		Render(&window, &grid);
	}

	return 0;
}

void Render(sf::RenderWindow* window, Grid* grid)
{
	window->clear();

	// Draw the grid
	for (int i = 0; i < grid->GetTiles()->size(); i++)
	{
		window->draw(grid->GetTiles()->at(i).boundingRect);
	}

	grid->Render(window);

	window->display();
}