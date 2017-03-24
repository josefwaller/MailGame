#include "UiButton.h"

const Color UiButton::btnMainColor(127, 127, 127);
const Color UiButton::btnLightColor(255, 255, 255);
const Color UiButton::btnDarkColor(0, 0, 0);

UiButton::UiButton(int x, int y, int w, int h, string text) : UiBlock(x, y, w, h)
{
	// sets text
	this->text = text;

	// sets bounds
	bounds = FloatRect((float)x, (float)y, (float)w, (float)h);
	
	// sets colors
	mainColor = &btnMainColor;
	lightColor = &btnLightColor;
	darkColor = &btnDarkColor;
}

void UiButton::onEvent(Event e)
{

}

// renders the button
void UiButton::render(RenderWindow * window)
{
	drawBorderedRect(bounds, window);
}