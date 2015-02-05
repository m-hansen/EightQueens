#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <process.h>
#include "Global.hpp"
#include "Grid.hpp"
#include "ResourceManager.hpp"

Grid grid;
bool wasSolutionStarted; // true if stated and not finished
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
	wasSolutionStarted = false;
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

					if (!wasSolutionStarted)
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
						if (!wasSolutionStarted)
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
	wasSolutionStarted = true;
	fprintf(stdout, "Spawning a new thread to solve the grid\n");
	grid.Solve((sf::RenderWindow*)window);
	wasSolutionStarted = false;
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