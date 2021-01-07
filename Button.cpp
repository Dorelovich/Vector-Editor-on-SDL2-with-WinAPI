#include "Button.h"

Button::Button(int x0, int y0, int w0, int h0, const std::string& file1, const std::string& file2) :x(x0),y(y0), w(w0), h(h0)
{
	this->file1 = file1;
	this->file2 = file2;
	_press = false;
	_focus = false;
}

void Button::draw(SDL_Renderer* renderer)
{
	if (_press)
		Image image(renderer, x, y, w, h, file2);
	else
		Image image(renderer, x, y, w, h, file1);
}

void Button::unfocus()
{
	_focus = false;
	_press = false;
}

void Button::press()
{
	_focus = true;
	_press = true;
}

void Button::unpress()
{
	if (this)
		_press = false;
}

void Button::down()
{
	_focus = true;
	_press = true;
}

bool Button::return_press()
{
	return _press;
}

bool Button::in(int x0, int y0)
{
	if (x0 >= x && x0 <= x + w)
		if (y0 >= y && y0 <= y + h)
		{
			press();
			return true;
		}
	unpress();
	return false;
}

void Button::move(int dx, int dy)
{
	x += dx;
	y += dy;
}