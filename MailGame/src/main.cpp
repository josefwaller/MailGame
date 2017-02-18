#include "game.h"

#include <SFML/Graphics.hpp>

int main()
{
	// creates a new window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Mail Game");

	// initializes the game
	gameInit();

	// runs the main loop while the window is open
	while (window.isOpen())
	{
		// checks any events that happen
		sf::Event event;
		while (window.pollEvent(event))
		{
			// closes if the exit button is pressed
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// updates everything
		gameUpdate();

		// clears the window
		window.clear();

		// draws new stuff
		//gameRender(&window);

		// updates the window
		window.display();

	}

	// destroys all elements
	gameDestroy();

	return 0;
}