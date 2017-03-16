#include "UiButton.h"

UiButton::UiButton(int x, int y, int w, int h, string text) : UiElement(x, y, w, h)
{
	this->text = text;
}

// renders the button
void UiButton::render(RenderWindow * window)
{
	
}