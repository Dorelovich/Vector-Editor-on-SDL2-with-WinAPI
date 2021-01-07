#pragma once

#include "Button.h"
#include "Text.h"
#include <string>

class Text_Menu
{
	int x, y;
	const int w_menu = 270;
	const int h_menu = 400;
	int w_window, h_window;
	char swap; /*'u' - up, 'd' - down, '0' - nothing*/

	bool _press;
	char inscription; /*не нашёл аналога точного аналога слова начертания на английском, буду использовать это. Solid, sHaded или Blended*/
	int size; 
	std::string font;

	Button* next_font;
	Button* solid;
	Button* shaded;
	Button* blended; 
	Button* plus_size;
	Button* minus_size;
	Button* up;
	Button* down;

	Text* t_size;
	Text* t_font;

	vector<string> files;
	int index_file;

	bool in_button(int x, int y, Button* batton);
	void winapi_file_search(vector<string>& vec);
public:

	Text_Menu(const char* fon, char inscription, int size);
	~Text_Menu();
	void draw(SDL_Renderer* renderer);
	void move(int dx, int dy);
	bool in(int x, int y);
	void unpress();
	int return_size();
	char return_inscription();
	std::string return_font();
	string return_file_name();
	char return_swap();
};

