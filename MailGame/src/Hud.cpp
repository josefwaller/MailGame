#include "Hud.h"
#include "App.h"

Hud::Hud() {}
Hud::Hud(App * app)
{
	// saves app
	this->app = app;

	// sets colors
	mainColor = Color(255, 165, 56);

	ascryClrOne = Color(255, 210, 155);
	ascryClrTwo = Color(168, 93, 1);
}

void Hud::render(RenderWindow * window)
{
	// draws the top bar
	drawBorderedRect(window, { 0, 0, (float) app->getW(), 20.0 });
}

void Hud::drawBorderedRect(RenderWindow * window, FloatRect r) 
{
	// creates a backgorund rect
	RectangleShape rect({ r.width - 2, r.height - 2});
	rect.setPosition({ r.left + 1, r.top + 1 });

	// sets color
	rect.setFillColor(mainColor);

	// sets outline color and thickness
	rect.setOutlineColor(ascryClrOne);
	rect.setOutlineThickness(1);

	// draws it
	window->draw(rect);

}

