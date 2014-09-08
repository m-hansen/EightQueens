#include <SFML/Graphics.hpp>
#include "Global.hpp"
#include "Grid.hpp"
#include "ResourceManager.hpp"

#include "Queen.hpp"

void Render(sf::RenderWindow* window, ResourceManager* rm, Grid* grid);

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Eight Queens");

	ResourceManager resourceManager;

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

		// Draw
		window.clear();
		grid.Render(&window);
		window.display();
	}

	return 0;
}