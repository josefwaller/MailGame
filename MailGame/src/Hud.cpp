#include "Hud.h"
#include "App.h"

Hud::Hud() {}
Hud::Hud(App * app)
{

	app = app;

	// sets colors
	mainColor = Color(255, 165, 56);

	ascryClrOne = Color(255, 210, 155);
	ascryClrTwo = Color(168, 93, 1);
}

void Hud::render(RenderWindow * window)
{

}

void Hud::drawBorderedRect(RenderWindow * window, FloatRect r) 
{

}

