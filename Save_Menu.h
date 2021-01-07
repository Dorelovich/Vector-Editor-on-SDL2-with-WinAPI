#pragma once

#include <SDL.h>
#include "Button.h" 
#include "Text.h"
#include <deque> 

class Save_Menu
{
	const int w_menu = 270;
	const int h_menu = 400;
	int w_window, h_window;

	bool _focus;
	bool _press_button;

	Button* save_file;
	Text* text;
	deque<char> deq;
public:
	Save_Menu();
	~Save_Menu();
	void draw(SDL_Renderer* renderer);
	bool in(int x, int y);
	void up_buttoms();
	void focus();
	void unfocus();
	bool return_focus();
	void add_char(char c);
	void delete_char();
	bool return_focus_text();
	bool return_press_button();
	void unpress_button();
	string return_file_name();
};

