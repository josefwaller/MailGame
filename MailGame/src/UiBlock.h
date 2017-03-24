#pragma once
#include "UiElement.h"

// A square in the Ui which, by default, is rendered with a bordered rect
class UiBlock : public UiElement
{
public:

	// sets colors
	static const Color mainColor;

	static const Color colorOne;
	static const Color colorTwo;

	UiBlock(int x, int y, int w, int h);

	void render(RenderWindow * window);

protected:

	void drawBorderedRect(FloatRect r, RenderWindow * window);
};