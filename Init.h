#pragma once

#include "SDL.h"
#include "Window.h"
#include "Point.h"
#include "Text_Primitive.h"
#include <cctype>

class Init
{
	int fps = 1000 / 60; /*60 fps*/
	void main_cycle();
	void click_L(Window& w, int x, int y);
	void click_R(Window& w, int x, int y);
	void up(Window& W);
	void mothion(Window& W, int xrel, int yrel);
	void wheel(Window& w,  int angle);
	void key_down(Window& W, SDL_Keycode c);
	void key_up(Window&  W, SDL_Keycode c);
	bool winapi_return_language();
	string covert_to_russian(char c, char reg);
	char convert_shift_symbol(char c, char lang);
	char convert_symbol(char c, char lang);
public:
	Init();
	~Init();
};

