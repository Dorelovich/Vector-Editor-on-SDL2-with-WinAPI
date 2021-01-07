#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Image.h"
#include <string>

class Button
{
	int x, y, w, h;
	std::string file1;
	std::string file2;
	bool _focus;
	bool _press;

public:

	Button(int x, int y, int w, int h, const std::string& file1, const std::string& file2);
	void draw(SDL_Renderer* renderer); /*рисование кнопки*/
	void press();
	void unfocus();
	void unpress();
	bool return_press();
	void down(); 
	bool in(int x, int y);
	void move(int x, int y);
};
