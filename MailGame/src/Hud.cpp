#include "Hud.h"
#include "App.h"
#include <iostream>

using namespace tgui;

Hud::Hud() {}
Hud::Hud(App * app)
{

	// saves app
	this->app = app;

	// gets theme
	this->theme = Theme::create("assets/gui/theme.txt");

	// creates toolbar
	this->toolbar = theme->load("MenuBar");
	this->toolbar->setSize(app->getW(), 20);

	// sets up menuStrings
	menuStrings = map<string, string>();
	menuStrings.insert({ {"file", "File"} });
	menuStrings.insert({"file_load", "Load"});
	menuStrings.insert({"file_save", "Save"});
	menuStrings.insert({"file_exit", "Exit"});

	menuStrings.insert({"build", "Build"});
	menuStrings.insert({"build_office", "Office"});
	menuStrings.insert({"build_mailbox", "mailbox"});

	// adds file menu
	this->toolbar->addMenu(menuStrings["file"]);
	this->toolbar->addMenuItem(menuStrings["file_save"]);
	this->toolbar->addMenuItem(menuStrings["file_load"]);
	this->toolbar->addMenuItem(menuStrings["file_exit"]);

	// adds build menu
	this->toolbar->addMenu(menuStrings["build"]);
	this->toolbar->addMenuItem(menuStrings["build_office"]);
	this->toolbar->addMenuItem(menuStrings["build_mailbox"]);

	// creates button
	this->app->getGui()->add(toolbar);

}

void Hud::init()
{

	this->toolbar->connect("MenuItemClicked", &Hud::onMenuSelect, this);
}

void Hud::onMenuSelect(vector<String> vals)
{
	if (vals[0] == menuStrings["file"]) {

		if (vals[1] == menuStrings["file_save"]) {

		}
		else if (vals[1] == menuStrings["file_load"]) {

		} 
		else if (vals[1] == menuStrings["file_exit"]) {
			this->app->getWindow()->close();
		}
	}
	else if (vals[0] == menuStrings["build"]) {
	
		if (vals[1] == menuStrings["build_office"]) {


		}
		else if (vals[1] == menuStrings["build_mailbox"]) {

		}
	}
}

void Hud::render(RenderWindow * window)
{
}

