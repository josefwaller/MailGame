#include "Hud.h"
#include "App.h"

using namespace tgui;

Hud::Hud() {}
Hud::Hud(App * app)
{
	// saves app
	this->app = app;

	// creates toolbar
	this->toolbar = ChildWindow::create();
	this->toolbar->setSize(app->getW(), 20);

	// creates the layout for the buttons
	HorizontalLayout::Ptr layout = HorizontalLayout::create();
	layout->setSize(bindWidth(this->toolbar) / 3, 20);
	this->toolbar->add(layout);

	// creates file button
	Button::Ptr fileButton = Button::create();
	fileButton->setSize(bindSize(this->toolbar) / 2);
	fileButton->setText("File");
	layout->add(fileButton);

	// creates build button
	Button::Ptr buildButton = Button::create();
	buildButton->setSize(bindSize(this->toolbar) / 2);
	buildButton->setText("Build");
	layout->add(buildButton);

	// creates button
	this->app->getGui()->add(toolbar);

}

void Hud::render(RenderWindow * window)
{

}

