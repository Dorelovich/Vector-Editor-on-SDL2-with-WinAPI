#pragma once

#include "SDL.h"
#include "Box.h"
#include "Color_Menu.h"
#include "Text_Menu.h"

class Point
{
protected:
	double x0, y0;
	int angle;
	bool _paint;
	bool _press;
	bool _focus;

	void DrawLine(SDL_Renderer* renderer, double x0, double y0, double x1, double y1);
	int sign(double x);
public:
	Box* box;
	Color_Menu* clr_menu;
	Text_Menu* text_menu;

	void paint();
	void unpaint();
	void press();
	void unpress();
	void unfocus();
	bool return_paint();
	bool retrun_press();
	bool retrun_focus();

	virtual ~Point() = 0 {};
	virtual void draw(SDL_Renderer* renderer);
	virtual void move(double x0, double y0);
	virtual void rotation(int angle);
	virtual bool in(int x, int y);
	virtual void resize(double x, double y);
	virtual void fwrite(std::ofstream& out);

	virtual void add_char(char c);
	virtual void delete_char();
	virtual void press_shift();
	virtual void unpress_shift();
	virtual bool return_press_shift();
	virtual bool its_text();
};

