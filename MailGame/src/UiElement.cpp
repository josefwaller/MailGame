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

// draws a bordered rect at a specified location
void UiElement::drawBorderedRect(FloatRect r, RenderWindow * window)
{
	// draws a lighter rectangle for the top-left border
	RectangleShape topLeft({ r.width - 1, r.height - 1 });

	// sets position and color
	topLeft.setPosition({ r.left, r.top });
	topLeft.setFillColor(UiElement::colorOne);

	// draws
	window->draw(topLeft);

	// does the same for the bottom right
	RectangleShape botRight({ r.width - 1, r.height - 1 });
	botRight.setPosition({ r.left + 1, r.top + 1 });
	botRight.setFillColor(UiElement::colorTwo);
	window->draw(botRight);

	// draws a main rectangle in the middle
	RectangleShape mainRect({r.width - 2, r.height - 2});
	mainRect.setPosition({ r.left + 1, r.top + 1 });
	mainRect.setFillColor(mainColor);
	window->draw(mainRect);

}