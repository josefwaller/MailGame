#include "UiBlock.h"

// sets up colors
const Color UiBlock::blockMainColor = Color(255, 165, 56);
const Color UiBlock::blockColorOne = Color(255, 210, 155);
const Color UiBlock::blockColorTwo = Color(168, 93, 1);

UiBlock::UiBlock(int x, int y, int w, int h) : UiElement(x, y, w, h)
{
	mainColor = &blockMainColor;
	colorOne = &blockColorOne;
	colorTwo = &blockColorTwo;
}

void UiBlock::render(RenderWindow * window)
{

}

// draws a bordered rect at a specified location
void UiBlock::drawBorderedRect(FloatRect r, RenderWindow * window)
{
	// draws a lighter rectangle for the top-left border
	RectangleShape topLeft({ r.width - 1, r.height - 1 });

	// sets position and color
	topLeft.setPosition({ r.left, r.top });
	topLeft.setFillColor(*colorOne);

	// draws
	window->draw(topLeft);

	// does the same for the bottom right
	RectangleShape botRight({ r.width - 1, r.height - 1 });
	botRight.setPosition({ r.left + 1, r.top + 1 });
	botRight.setFillColor(*colorTwo);
	window->draw(botRight);

	// draws a main rectangle in the middle
	RectangleShape mainRect({ r.width - 2, r.height - 2 });
	mainRect.setPosition({ r.left + 1, r.top + 1 });
	mainRect.setFillColor(*mainColor);
	window->draw(mainRect);

}