#include <SFML/Graphics.hpp>

int main()
{
	// creates a new window
	sf::RenderWindow window(sf::VideoMode(200, 200), "Mail Game");

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

		// clears the window
		window.clear();

		// draws new stuff

		// updates the window
		window.display();

	}

	return 0;
}