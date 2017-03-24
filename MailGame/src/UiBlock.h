#pragma once
#include "UiElement.h"

// A square in the Ui which, by default, is rendered with a bordered rect
class UiBlock : public UiElement
{
public:

	// these are the colors used for an UiBlock
	static const Color blockMainColor;
	static const Color blockLightColor;
	static const Color blockDarkColor;

	// these are the colors that will actually be used
	// may be overridden in a child class
	const Color * mainColor;
	const Color * colorOne;
	const Color * colorTwo;

	UiBlock(int x, int y, int w, int h);

	void render(RenderWindow * window);

protected:

	void drawBorderedRect(FloatRect r, RenderWindow * window);
};