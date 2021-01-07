#pragma once

#include <SDL.h>
#include "Image.h"

class Slider
{
	int x, y, value;
	bool _press;

public:
	Slider(int x, int y);
	int return_value();
	void draw(SDL_Renderer* renderer);
	bool in(int x, int y);
	void move(int dx, int dy);
	void recolor(int dx);
	void press();
	void unpress();
	bool return_press();
	void set_value(int);
};
