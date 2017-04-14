#include "Hud.h"
#include "App.h"
#include <iostream>

using namespace tgui;

Hud::Hud() {}
Hud::Hud(App * app)
{

	this->isCorrect = false;
	// saves app
	this->app = app;

	// creates toolbar
	this->toolbar = MenuBar::create();
	this->toolbar->setSize(app->getW(), 20);

	// adds file menu
	this->toolbar->addMenu("File");
	this->toolbar->addMenuItem("Load");
	this->toolbar->addMenuItem("Save");
	this->toolbar->addMenuItem("Exit");

	// adds build menu
	this->toolbar->addMenu("Build");
	this->toolbar->addMenuItem("Post Office");
	this->toolbar->addMenuItem("Mailbox");
	this->toolbar->addMenuItem("Dinosaur");

	// creates button
	this->app->getGui()->add(toolbar);


}

void Hud::init()
{

	this->toolbar->connect("MenuItemClicked", &Hud::onMenuSelect, this);
}

void Hud::onMenuSelect(vector<String> vals)
{
	if (vals[0] == "File" && vals[1] == "Exit") {
		this->app->getWindow()->close();
	}
}

void Hud::render(RenderWindow * window)
{
}

