#include "UiElement.h"

#include "App.h"


UiElement::UiElement(int x, int y, int w, int h, Hud * hud)
{
	// sets position
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->hud = hud;
}