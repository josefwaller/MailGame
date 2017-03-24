#pragma once
#include "UiElement.h"

// A square in the Ui which, by default, is rendered with a bordered rect
class UiBlock : public UiElement
{
public:
	UiBlock(int x, int y, int w, int h);

	void render(RenderWindow * window);

private:
	FloatRect shape;
};