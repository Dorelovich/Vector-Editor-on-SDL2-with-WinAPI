#pragma once

#include "SDL.h"
#include "Text.h"
#include "Point.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "Text_Primitive.h"
#include "Toolbar.h"
#include "Open_Menu.h"
#include "Save_Menu.h"
#include <list>
#include <string>

class Window
{
	int w, h; /*размеры экрана*/
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::list <Point*> primitives;

public:
	Open_Menu* open_menu;
	Save_Menu* save_menu;
	Point *press_primitive; /*нажатый примитив*/
	Toolbar* toolbar;

	void add_prim(Point* p);
	void delete_prim();
	void show();
	Window();
	~Window();
	bool in(int x, int y);
	int press_button();
	void unpress_button();
	void save_file(string name_file);
	void open_file(string name_file);
	void swap_prim();
};

/*               W varible
<-------------------------------------->
---------------------------------------- ^
|                toolbar               | |  60 px
|                                      | |  const
---------------------------------------- v
|                                      |
|                                      |
|                                      |
|                canvas                |
|                                      |
|                                      | 
|                                      |
----------------------------------------
*/

