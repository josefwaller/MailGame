#include "Hud.h"
#include "App.h"

Hud::Hud() {}
Hud::Hud(App * app)
{
	// saves app
	this->app = app;

	this->button = tgui::ChildWindow::create();

	// creates button
	this->app->getGui()->add(button);

}

void Hud::render(RenderWindow * window)
{

}

