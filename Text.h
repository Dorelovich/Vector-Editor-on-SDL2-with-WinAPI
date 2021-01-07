#pragma once
#include "SDL_ttf.h"
#include "SDL.h"
#include <string>
#include <vector>

using namespace std;

class Text
{
	int ttf_w, ttf_h; /*нужны дл€ корректной работы ttf, их значени€ она и мен€ет, € с их помощью провер€ю выход за гарницы тектового пол€*/
	TTF_Font* font;

protected:

	int x, y;
	int w, h;
	string name_font;
	int size;
	char inscription;
	bool _focus;

public:

	Text(int x, int y);
	virtual ~Text();
	void print(SDL_Renderer* renderer, const char text[512]);
	void refont(string new_font);
	void resize(int new_size);
	void reins(char c);
	void focus();
	void unfocus();
	bool return_focus();
	int return_ttf_w();
	int return_ttf_h();
	bool in(int x, int y);
	void draw_border(SDL_Renderer* renderer, SDL_Color color);
	void resize(int new_w, int new_h);
	void move(int dx, int dy);
	string return_font();
	int return_size();
	char return_inscription();
};

