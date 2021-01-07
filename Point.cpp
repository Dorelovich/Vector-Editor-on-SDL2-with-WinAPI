#include "Point.h"

void Point::draw(SDL_Renderer* renderer) {}

void Point::DrawLine(SDL_Renderer* renderer, double x0, double y0, double x1, double y1)
{
	const int deltaX = fabs(x1 - x0);
	const int deltaY = fabs(y1 - y0);
	const int signX = x0 < x1 ? 1 : -1;
	const int signY = y0 < y1 ? 1 : -1;
	int error = deltaX - deltaY;
	SDL_RenderDrawPoint(renderer, x1, y1);
	int i = 0;
	while (fabs(x0 - x1) > 1 || fabs(y0 - y1) > 1)
	{
		if (i % 10 != 0)
			SDL_RenderDrawPoint(renderer, x0, y0);
		const int error2 = error * 2;
		if (error2 > -deltaY)
		{
			error -= deltaY;
			x0 += signX;
		}
		if (error2 < deltaX)
		{
			error += deltaX;
			y0 += signY;
		}
		i++;
	}
}

int Point::sign(double x)
{
	if (x > 0.0001)
		return 1;
	else
		if (x < -0.0001)
			return -1;
		else
			return 0;
}

void Point::paint()
{
	_focus = true;
	_paint = true;
}

void Point::unpaint()
{
	_paint = false;
}

void Point::press()
{
	_focus = true;
	_press = true;
}

void Point::unpress()
{
	_press = false;
}

void Point::unfocus()
{
	_paint = false;
	_press = false;
	_focus = false;
}

bool Point::return_paint()
{
	if (this)
		return _paint;
	return false;
}

bool Point::retrun_press()
{
	 return _press;
}

bool Point::retrun_focus()
{
	if (this)
		return _focus;
	else
		return false;
}

void Point::resize(double x, double y) {}

void Point::move(double x, double y) {}

void Point::rotation(int angle) {}

bool Point::in(int x, int y) { return false; }

void Point::fwrite(std::ofstream& out) {}

void Point::add_char(char c) {}

void Point::delete_char() {}

void Point::press_shift() {}

void Point::unpress_shift() {}

bool Point::return_press_shift() { return false; }

bool Point::its_text() { return false; }