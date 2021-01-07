#include "Slider.h"

Slider::Slider(int x, int y)
{
	this->x = x;
	this->y = y;
	_press = false;
	value = 0;
}

void Slider::draw(SDL_Renderer* renderer)
{
	Image fon(renderer, x, y, "images/Slider_fon.png");
	Image button(renderer, x + value, y - 3, "images/Slider_button.png");
}

bool Slider::in(int x, int y)
{
	if (this->x + value <= x && this->x + value + 20 >= x)
		if (this->y <= y && this->y + 20 >= y)
		{
			press();
			return true;
		}
	unpress();
	return false;
}

void Slider::move(int dx, int dy)
{
	x += dx;
	y += dy;
}

void Slider::recolor(int dx)
{
	if (value + dx >= 0 && value + dx <= 185)
		value += dx;
}

int Slider::return_value()
{
	if (value + value * value / 485 >= 128)
		return value + value * value / 485;
	else
		return value - value * value / 485;
}

void Slider::press()
{
	_press = true;
}

void Slider::unpress()
{
	_press = false;
}

bool Slider::return_press()
{
	return _press;
}

void Slider::set_value(int x)
{
	value = x;
}
