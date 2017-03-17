#include "UiButton.h"

UiButton::UiButton(int x, int y, int w, int h, string text, Color baseColor = Color::Red) : UiElement(x, y, w, h)
{
	this->text = text;
	this->color = baseColor;
}

void UiButton::onEvent(Event e)
{

}

// renders the button
void UiButton::render(RenderWindow * window)
{
	RectangleShape r({ (float)w, (float)h });
	r.setPosition({ (float)x, (float)y });
	r.setFillColor(color);
	window->draw(r);

}