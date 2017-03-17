#include "UiElement.h"

UiElement::UiElement(int x, int y, int w, int h)
{
	// sets position
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

void UiElement::render(RenderWindow * window)
{

	RectangleShape r = RectangleShape({ (float)w, (float)h });
	r.setPosition((float)x, (float)y);
	r.setFillColor(Color::Red);

	window->draw(r);
	
}