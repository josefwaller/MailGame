#pragma once

#include <SFML/Graphics.hpp>

// initializes the game
void gameInit();

// updates the game
void gameUpdate();

// renders the game
void gameRender(sf::RenderWindow * window);

// destroys the game
void gameDestroy();