#include "UiElement.h"

// sets up colors
const Color UiElement::mainColor = Color(255, 165, 56);
const Color UiElement::colorOne = Color(255, 210, 155);
const Color UiElement::colorTwo = Color(168, 93, 1);

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