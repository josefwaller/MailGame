#pragma once
#include "Building.h"

class PostOffice : public Building
{
public:
	PostOffice(App * app, Vector2i pos, Direction d);
	void update(Time dt);
};