#pragma once
#include "MySprite.h"


struct Line
{
	sf::Vertex pts[2];
	void Draw(sf::RenderWindow* window) { window->draw(pts, 2, sf::LineStrip); }
};