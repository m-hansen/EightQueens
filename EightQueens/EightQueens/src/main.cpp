#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <process.h>
#include "Global.hpp"
#include "Grid.hpp"
#include "ResourceManager.hpp"

Grid grid;
/*
Note: the two solution booleans are not connected to each other

isSolutionRunning is true if the solution has been started
but not completed (it is true even if the solution is paused)

isSolutionPaused is only to determine if the solution should
actively work or temporarily pause
*/
bool isSolutionRunning; // true if stated and not finished
bool isSolutionPaused; // true if paused
HANDLE solutionHandle;

void ThreadEntry(void *arg);
void HandleSolutionPause();

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Eight Queens");

	ResourceManager resourceManager;

	// Create an 8x8 Grid
	grid.CreateGrid(&resourceManager, 8);
	isSolutionRunning = false;
	isSolutionPaused = false;

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

					if (!isSolutionRunning)
					{
						grid.HandleMouseClick(&event, &window);
					}

					else
					{
						fprintf(stdout, "Cannot modify board until solution is finished\n");
					}

					break;

				case sf::Event::KeyPressed:

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					{
						window.close();
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{
						if (!isSolutionRunning)
						{
							solutionHandle = (HANDLE)_beginthread(ThreadEntry, 0, &window);
						}
						else
						{
							// If we have already started solving the grid
							// treat this as a pause or resume
							HandleSolutionPause();
						}
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

void ThreadEntry(void* window)
{
	isSolutionRunning = true;
	fprintf(stdout, "Spawning a new thread to solve the grid\n");
	grid.Solve((sf::RenderWindow*)window);
	isSolutionRunning = false;
}

void HandleSolutionPause()
{
	if (isSolutionPaused)
	{
		fprintf(stdout, "-SOLUTION UNPAUSED-\n");
		isSolutionPaused = false;
		ResumeThread(solutionHandle);
	}
	else
	{
		fprintf(stdout, "-SOLUTION PAUSED-\n");
		isSolutionPaused = true;
		SuspendThread(solutionHandle);
	}
}