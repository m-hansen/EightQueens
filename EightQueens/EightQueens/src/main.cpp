#include <SFML/Graphics.hpp>
#include "Global.hpp"
#include "Grid.hpp"
#include "ResourceManager.hpp"

Grid grid;

void threadEntry(void *arg);

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Eight Queens");

	ResourceManager resourceManager;

	// Create an 8x8 Grid
	grid.CreateGrid(&resourceManager, 8);

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

				case sf::Event::KeyPressed:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					{
						window.close();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{
						fprintf(stdout, "Space pressed\n");
						_beginthread(threadEntry, 0, &window);
						//grid.Solve(&window);
					}
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

void threadEntry(void* window)
{
	fprintf(stdout, "Spawning a new thread to solve the grid\n");
	grid.Solve((sf::RenderWindow*)window);
}