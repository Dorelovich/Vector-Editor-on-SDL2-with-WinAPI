#pragma once

#include <SDL.h>
#include "Button.h" 
#include <vector>
#include <string>
#include "Text.h"

using namespace std;

class Open_Menu
{
	const int w_menu = 270;
	const int h_menu = 400;
	int w_window, h_window;

	bool _focus;
	bool _press_button;

	Button* next_file;
	Button* open_file;
	vector<string> files;
	int index_file;

	void winapi_file_search(vector<string>& vec); 
public:
	Open_Menu();
	~Open_Menu();
	void draw(SDL_Renderer* renderer);
	bool in(int x, int y);
	void up_buttoms();
	void unpress_button();
	void focus();
	void unfocus();
	bool return_focus();
	bool return_press_button();
	string return_file_name();
};

