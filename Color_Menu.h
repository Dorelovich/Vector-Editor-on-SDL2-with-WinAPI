#pragma once

#include <SDL.h>
#include "Image.h"
#include "Button.h" 
#include "Slider.h"

class Color_Menu
{
	SDL_Color clr_fon;
	SDL_Color clr_border;
	int x, y;
	const int w_menu = 270;
	const int h_menu = 400;
	int w_window, h_window;
	char swap; /*'u' - up, 'd' - down', '0' - nothing*/

	bool _press;
	bool _fill;
	bool _broken;

	Button* filling;
	Button* broken_line;
	Button* up;
	Button* down;

	Slider* slider_f_r;
	Slider* slider_f_g;
	Slider* slider_f_b;

	Slider* slider_b_r;
	Slider* slider_b_g;
	Slider* slider_b_b;
public:
	Color_Menu(SDL_Color fon, SDL_Color border, bool _fill, bool _broken);
	~Color_Menu();
	SDL_Color return_color_fon();
	SDL_Color return_color_border();
	void draw(SDL_Renderer* renderer);
	void move(int dx, int dy);
	bool in(int x, int y);
	char return_swap();

	void press();
	void unpress();
	bool return_press();
	bool return_fill();
	bool return_broken();
	bool return_move_slider();
	void move_slider(int dx);
	void up_sliders();
};

