#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

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
	window.resetGLStates();

	// initializes sfgui
	sfg::SFGUI sfgui;

	// creates sfgui desktop
	sfg::Desktop desktop;

	// creates app
	App app = App(W, H, &window, &desktop);

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
			desktop.HandleEvent(event);

			// closes if the exit button is pressed
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// updates everything
		app.update(dt);

		// clears the window
		window.clear();

		// updates SFGUI

		window.setView(window.getDefaultView());
		desktop.Update(dt.asSeconds());

		// draws new stuff
		// first saves opengl state so that the gui is not distorted 
		window.pushGLStates();
		app.render(&window);

		// restores original opengl state for gui
		window.popGLStates();

		// draws gui elements
		sfgui.Display(window);

		// updates the window
		window.display();

	}

	// destroys all elements
	app.destroy();

	return 0;
}