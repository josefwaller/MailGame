#include "Hud.h"
#include "App.h"

Hud::Hud() {}
Hud::Hud(App * app)
{
	// saves app
	this->app = app;

	buttons = {
		UiButton(0, 0, 40, 40, "ASDF")
	};
}

void Hud::render(RenderWindow * window)
{

	// draws the buttons
	for (UiButton b : buttons) {
		b.render(window);
	}
}

