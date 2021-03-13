#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Frame {
	void gameRun(RenderWindow &, int, int);
	void setFrame(RenderWindow &, float, float);
	void setFrame(RenderWindow &, int);
public:
	int run(RenderWindow &, int);
};