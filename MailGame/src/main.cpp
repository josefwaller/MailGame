#include <SFML/Graphics.hpp>
#include "App.h"
#include "windows.h"


int main()
{
	// creates a new window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Mail Game");

	App app = App();

	// initializes the game
	app.init();

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
		app.update();

		// clears the window
		window.clear();

		// draws new stuff
		app.render(&window);

		// updates the window
		window.display();

	}

	// destroys all elements
	app.destroy();

	return 0;
}