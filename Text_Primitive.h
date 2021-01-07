#pragma once

#include "Point.h"
#include "Text.h"
#include "vector"
#include <deque>
#include <fstream>

class Text_Primitive : public Point
{
	double w, h;
	Text* text;
	deque<char> deq;
	bool _press_shift;
	bool single_byte_symbol(char c);

public:

	Text_Primitive(int x0, int y0);
	Text_Primitive(int x0, int y0, string font, int size, char inscription, deque<char> deq);
	~Text_Primitive();
	bool in(int x, int y);
	void move(double x, double y);
	void draw(SDL_Renderer* renderer);
	void add_char(char c);
	void delete_char();
	string return_file_name();
	void press_shift();
	void unpress_shift();
	bool return_press_shift();
	bool its_text();
	void fwrite(std::ofstream& out);
};