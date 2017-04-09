#include <SFGUI/Widget.hpp>

#include "Hud.h"
#include "App.h"

Hud::Hud() {}
Hud::Hud(App * app, sfg::Desktop * d)
{
	// saves app
	this->app = app;

	// creates the toolbar window
	this->toolbar = sfg::Window::Create();
	toolbar->SetTitle("ToolBar");
	(*d).Add(toolbar);

	// creates box
	auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	box->Pack(sfg::Button::Create("Testing!"));
	toolbar->Add(box);

}

void Hud::render(RenderWindow * window)
{

}

