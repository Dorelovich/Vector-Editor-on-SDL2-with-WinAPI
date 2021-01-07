#pragma once
#include "Button.h"

class Toolbar
{
	int w; /*ширина экрана*/
	SDL_Color color = { 170, 160, 200, 255 }; 

	Button *save;
	Button* open;
	Button *del;
	Button *point;
	Button *line;
	Button *rectangle;
	Button *ellips;
	Button* text;

	Button* press_button;
public:
	int index_button;

	Toolbar(int w);
	~Toolbar();
	void draw(SDL_Renderer* renderer);
	void unpress();
	bool in(int x, int y);
};

