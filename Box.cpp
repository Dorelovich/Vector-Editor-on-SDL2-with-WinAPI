#include "Box.h"

Box::Box(double x, double y, double w, double h)
{
	angle = 0;
	circle = -1;
	x0 = x2 = x;
	y0 = y1 = y;
	x1 = x3 = x0 + w;
	y2 = y3 = y0 + h;
}

Box::Box(int angle, double x, double y, double w, double h)
{
	circle = -1;
	x0 = x2 = x;
	y0 = y1 = y;
	x1 = x3 = x0 + w;
	y2 = y3 = y0 + h;
	this->angle = angle;
	rotation(angle);
}

Box::Box(int angle, double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3)
{
	circle = -1;
	this->x0 = x0;
	this->x1 = x1;
	this->x2 = x2;
	this->x3 = x3;
	this->y0 = y0;
	this->y1 = y1;
	this->y2 = y2;
	this->y3 = y3;
	this->angle = angle;
}

void Box::rot_point(double& x, double& y, double x_c, double y_c, int angle)
{
	double tx = x - x_c;
	double ty = y - y_c;

	x = tx * cos(angle * M_PI / 180) - ty * sin(angle * M_PI / 180) + (x - tx);
	y = tx * sin(angle * M_PI / 180) + ty * cos(angle * M_PI / 180) + (y - ty);
}

void Box::DrawLine(SDL_Renderer* renderer, double x0, double y0, double x1, double y1)
{
	const int deltaX = fabs(x1 - x0);
	const int deltaY = fabs(y1 - y0);
	const int signX = x0 < x1 ? 1 : -1;
	const int signY = y0 < y1 ? 1 : -1;
	int error = deltaX - deltaY;
	SDL_RenderDrawPoint(renderer, x1, y1);
	int i = 0;
	while ( fabs(x0 - x1) > 1 || fabs(y0 - y1) > 1)
	{
		if (i % 2 == 0)
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

void Box::DrawCircle(SDL_Renderer* renderer, double x0, double y0, double r)
{
	for (double i = 0; i < 2 * M_PI; i += 0.4)
		SDL_RenderDrawPoint(renderer, r * cos(i) + x0, r * sin(i) + y0);
	
}

void Box::rotation(int angle)
{
	this->angle += angle;
	if (this->angle > 360)
		this->angle = 0;
	else
		if (this->angle < 0)
			this->angle = 359;

	double dx = x0 - (x0 - x3) / 2;
	double dy = y0 - (y0 - y3) / 2;

	rot_point(x0, y0, dx, dy, angle);
	rot_point(x1, y1, dx, dy, angle);
	rot_point(x2, y2, dx, dy, angle);
	rot_point(x3, y3, dx, dy, angle);
}

void Box::draw(SDL_Renderer* renderer)
{
	SDL_Color color { 0, 0, 0, 255 };
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	DrawLine(renderer, x0, y0, x1, y1);
	DrawLine(renderer, x0, y0, x2, y2);
	DrawLine(renderer, x1, y1, x3, y3);
	DrawLine(renderer, x2, y2, x3, y3);
	DrawCircle(renderer, x0, y0, 5);
	DrawCircle(renderer, x1, y1, 5);
	DrawCircle(renderer, x2, y2, 5);
	DrawCircle(renderer, x3, y3, 5);
}

void Box::move(double x, double y)
{
	x0 += x;
	y0 += y;
	x1 += x;
	y1 += y;
	x2 += x;
	y2 += y;
	x3 += x;
	y3 += y;
}

void Box::resize(double dx, double dy)
{
	int t = angle;
	rotation(-angle);

	if (circle == 0)
	{
		if (sign(x0 - x1) == sign(x0 + dx - x1 + 41) && sign(x0 - x1) == sign(x0 + dx - x1 - 41))
		{
			x0 += dx;
			x2 += dx;
		}
		if (sign(y0 - y2) == sign(y0 + dy - y2 + 41) && sign(y0 - y2) == sign(y0 + dy - y2 - 41))
		{
			y0 += dy;
			y1 += dy;
		}
	}
	if (circle == 1)
	{
		if (sign(x1 - x0) == sign(x1 + dx - x0 + 41) && sign(x1 - x0) == sign(x1 + dx - x0 - 41))
		{
			x1 += dx;
			x3 += dx;
		}
		if (sign(y1 - y3) == sign(y1 + dy - y3 + 41) && sign(y1 - y3) == sign(y1 + dy - y3 - 41))
		{
			y1 += dy;
			y0 += dy;
		}
	}
	if (circle == 2)
	{
		if (sign(x2 - x3) == sign(x2 + dx - x3 + 41) && sign(x2 - x3) == sign(x2 + dx - x3 - 41))
		{
			x2 += dx;
			x0 += dx;
		}
		if (sign(y2 - y0) == sign(y2 + dy - y0 + 41) && sign(y2 - y0) == sign(y2 + dy - y0 - 41))
		{
			y2 += dy;
			y3 += dy;
		}
	}
	if (circle == 3)
	{
		if (sign(x3 - x2) == sign(x3 + dx - x2 + 41) && sign(x3 - x2) == sign(x3 + dx - x2 - 41))
		{
			x3 += dx;
			x1 += dx;
		}
		if (sign(y3 - y1) == sign(y3 + dy - y1 + 41) && sign(y3 - y1) == sign(y3 + dy - y1 - 41))
		{
			y3 += dy;
			y2 += dy;
		}
	}
	rotation(t);
}

int Box::sign(double x)
{
	if (x > 0.0001)
		return 1;
	else
		if (x < -0.0001)
			return -1;
		else
			return 0;
}

bool Box::in(int x, int y)
{
	circle = -1;
	if (fabs(x - x0) <= 5 && fabs(y - y0) <= 5)
		circle = 0;
	if (fabs(x - x1) <= 5 && fabs(y - y1) <= 5)
		circle = 1;
	if (fabs(x - x2) <= 5 && fabs(y - y2) <= 5)
		circle = 2;
	if (fabs(x - x3) <= 5 && fabs(y - y3) <= 5)
		circle = 3;
	if (circle >= 0)
	{
		press();
		return true;
	}
	unfocus();
	return false;
}

void Box::press()
{
	_focus = true;
	_press = true;
}

void Box::unpress()
{
	_press = false;
}

void Box::unfocus()
{
	_press = false;
	_focus = false;
}

bool Box::retrun_press()
{
	return _press;
}

bool Box::retrun_focus()
{
	if (this)
		return _focus;
	else
		return false;
}

int Box::return_circle()
{
	return circle;
}

double Box::return_point(int index, char axis)
{
	switch (index)
	{
	case 0:
		if (axis == 'x')
			return x0;
		else
			return y0;
		break;
	case 1:
		if (axis == 'x')
			return x1;
		else
			return y1;
		break;
	case 2:
		if (axis == 'x')
			return x2;
		else
			return y2;
		break;
	case 3:
		if (axis == 'x')
			return x3;
		else
			return y3;
		break;
	}
}