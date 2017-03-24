#include "UiButton.h"

UiButton::UiButton(int x, int y, int w, int h, string text) : UiElement(x, y, w, h)
{
	this->text = text;

	bounds = FloatRect((float)x, (float)y, (float)w, (float)h);
	
}

void UiButton::onEvent(Event e)
{

}

// renders the button
void UiButton::render(RenderWindow * window)
{
	drawBorderedRect(bounds, window);
}