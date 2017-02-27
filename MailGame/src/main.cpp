#include <SFML/Graphics.hpp>
#include "App.h"
#include "windows.h"


int main()
{

	// sets the W and H
	const int W = 800;
	const int H = 600;

	// creates a new window
	sf::RenderWindow window(sf::VideoMode(W, H), "Mail Game");

	App app = App(W, H, &window);

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