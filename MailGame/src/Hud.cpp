#include "Hud.h"
#include "App.h"

Hud::Hud() {}
Hud::Hud(App * app)
{
	// saves app
	this->app = app;

	buttons = {
		UiButton(10, 10, 20, 20, "ASDF", this)
	};
}

void Hud::render(RenderWindow * window)
{

	// draws the buttons
	for (UiButton b : buttons) {
		b.render(window);
	}
}

