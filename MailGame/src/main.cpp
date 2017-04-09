#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "App.h"
#include "windows.h"


int main()
{

	// sets the W and H
	const int W = 800;
	const int H = 600;

	// creates a new window
	sf::RenderWindow window(sf::VideoMode(W, H), "Mail Game");

	// creates the GUI for the window
	tgui::Gui gui { window };

	// creates app
	App app = App(W, H, &window, &gui);

	// initializes the game
	app.init();

	// creates clock to get delta time
	sf::Clock deltaClock;

	deltaClock.restart();

	// runs the main loop while the window is open
	while (window.isOpen())
	{
		// gets delta time
		sf::Time dt = deltaClock.restart();

		// checks any events that happen
		sf::Event event;
		while (window.pollEvent(event))
		{

			// closes if the exit button is pressed
			if (event.type == sf::Event::Closed)
				window.close();

			// checks for the GUI to handle the event
			gui.handleEvent(event);
		}

		// updates everything
		app.update(dt);

		// clears the window
		window.clear();

		// draws gui
		gui.draw();

		// draws stuff
		app.render(&window);

		// updates the window
		window.display();

	}

	// destroys all elements
	app.destroy();

	return 0;
}