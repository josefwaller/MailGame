#include "Hud.h"
#include "App.h"
#include <iostream>

using namespace tgui;

Hud::Hud() {}
Hud::Hud(App * app)
{
	// saves app
	this->app = app;

	// creates toolbar
	this->toolbar = MenuBar::create();
	this->toolbar->setSize(app->getW(), 20);
	this->toolbar->connect("MenuItemClicked", [&](vector<sf::String> s) { cout << (string)s[0] << " -> " << (string)s[1] << "\n";});

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

void Hud::render(RenderWindow * window)
{

}

