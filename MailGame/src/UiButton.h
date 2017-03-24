#pragma once
#include "UiBlock.h"

#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

// a button on the UI
class UiButton : public UiBlock
{
public:
	UiButton(int x, int y, int w, int h, string text);

	void onEvent(Event e);
	void render(RenderWindow * window) override;

	// get/set methods
	string getText();
	void setText(string newText);

private:

	// the text to draw on the button
	string text;

	// the bounds the button takes
	FloatRect bounds;
};