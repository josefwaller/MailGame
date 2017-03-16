#pragma once
#include "UiElement.h"

#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

// a button on the UI
class UiButton : public UiElement
{
public:
	UiButton(int x, int y, int w, int h, string text);

	void render(RenderWindow * window) override;

	// get/set methods
	string getText();
	void setText(string newText);

private:

	// the text to draw on the button
	string text;
};