#include "Rectangle.h"

Rectangle::Rectangle(double x, double y, double w, double h)
{
	box = new Box(x - 20, y - 20, w + 40, h + 40);
	SDL_Color c = { 0,0,0,255 };
	clr_menu = new Color_Menu(c, c, 0, 0);
	_press = false;
	_paint = false;
	_focus = true;
	x0 = x;
	y0 = y;
	x1 = x + w;
	y1 = y;
	x2 = x;
	y2 = y + h;
	x3 = x + w;
	y3 = y + h;
	angle = 0;
}

Rectangle::Rectangle(int angle, double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, bool _fill, bool _broken, SDL_Color fon, SDL_Color border,
	double b_x0, double b_y0, double b_x1, double b_y1, double b_x2, double b_y2, double b_x3, double b_y3)
{
	clr_menu = new Color_Menu(fon, border, _fill, _broken);
	box = new Box(angle, b_x0, b_y0, b_x1, b_y1, b_x2, b_y2, b_x3, b_y3);
	this->angle = angle;
	this->x0 = x0;
	this->y0 = y0;
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->x3 = x3;
	this->y3 = y3;
}

Rectangle::~Rectangle()
{
	delete box;
	delete clr_menu;
}

void Rectangle::draw(SDL_Renderer* renderer)
{
	if (clr_menu->return_fill())
		draw_fill(renderer);
	draw_unfill(renderer);
	if (_focus)
		box->draw(renderer);
}

void Rectangle::draw_fill(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, clr_menu->return_color_fon().r, clr_menu->return_color_fon().g, clr_menu->return_color_fon().b, clr_menu->return_color_fon().a);
	double copy_x0 = x0;
	double copy_y0 = y0;
	double copy_x1 = x1;
	double copy_y1 = y1;
	double copy_x2 = x2;
	double copy_y2 = y2;

	double h;

	if (fabs(y0 - y3) > fabs(y1 - y2))
		h = fabs(y0 - y3);
	else
		h = fabs(y1 - y2);

	if (fabs(x0 - x3) > fabs(x1 - x2) && h < fabs(x0 - x3))
		h = fabs(x0 - x3);
	else 
		if (h < fabs(x1 - x2))
			h = fabs(x1 - x2);

	double dx = (x0 - x2) / h;
	double dy = (y2 - y0) / h;

	for (int i = 0; i < h; i++)
	{
		copy_x0 -= dx;
		copy_x1 -= dx;
		copy_y0 += dy;
		copy_y1 += dy;
		SDL_RenderDrawLine(renderer, copy_x0, copy_y0, copy_x1, copy_y1);
		SDL_RenderDrawLine(renderer, copy_x0, copy_y0 + 1, copy_x1, copy_y1 + 1);
		SDL_RenderDrawLine(renderer, copy_x0 + 1, copy_y0 + 1, copy_x1 + 1, copy_y1 + 1);
	}
}

void Rectangle::draw_unfill(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, clr_menu->return_color_border().r, clr_menu->return_color_border().g, clr_menu->return_color_border().b, clr_menu->return_color_border().a);
	if (clr_menu->return_broken())
	{
		DrawLine(renderer, x0, y0, x1, y1);
		DrawLine(renderer, x0, y0, x2, y2);
		DrawLine(renderer, x1, y1, x3, y3);
		DrawLine(renderer, x2, y2, x3, y3);
	}
	else
	{
		SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
		SDL_RenderDrawLine(renderer, x0, y0, x2, y2);
		SDL_RenderDrawLine(renderer, x1, y1, x3, y3);
		SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
	}
}

void Rectangle::move(double x, double y)
{
	if (y0 + y > 60 + 20 && y1 + y > 60 + 20 && y2 + y > 60 + 20 && y3 + y > 60 + 20) /*проверка того, что не выходим на toolbar*/
	{
		x0 += x;
		y0 += y;
		x1 += x;
		y1 += y;
		x2 += x;
		y2 += y;
		x3 += x;
		y3 += y;
		box->move(x, y);
	}
}

void Rectangle::rot_point(double& x, double& y, double x_c, double y_c, int angle)
{
	double tx = x - x_c;
	double ty = y - y_c;

	x = tx * cos(angle * M_PI / 180) - ty * sin(angle * M_PI / 180) +(x - tx);
	y = tx * sin(angle * M_PI / 180) + ty * cos(angle * M_PI / 180) +(y - ty);
}

void Rectangle::resize(double dx, double dy)
{
	int t = angle;
	rotation(-angle);

	if (box->return_circle() == 0)
	{
		if (sign(x0 - x1) == sign(x0 + dx - x1 + 1) && sign(x0 - x1) == sign(x0 + dx - x1 - 1))
		{
			x0 += dx;
			x2 += dx;
		}
		if (sign(y0 - y2) == sign(y0 + dy - y2 + 1) && sign(y0 - y2) == sign(y0 + dy - y2 - 1))
		{
			y0 += dy;
			y1 += dy;
		}
	}
	if (box->return_circle() == 1)
	{
		if (sign(x1 - x0) == sign(x1 + dx - x0 + 1) && sign(x1 - x0) == sign(x1 + dx - x0 - 1))
		{
			x1 += dx;
			x3 += dx;
		}
		if (sign(y1 - y3) == sign(y1 + dy - y3 + 1) && sign(y1 - y3) == sign(y1 + dy - y3 - 1))
		{
			y1 += dy;
			y0 += dy;
		}
	}
	if (box->return_circle() == 2)
	{
		if (sign(x2 - x3) == sign(x2 + dx - x3 + 1) && sign(x2 - x3) == sign(x2 + dx - x3 - 1))
		{
			x2 += dx;
			x0 += dx;
		}
		if (sign(y2 - y0) == sign(y2 + dy - y0 + 1) && sign(y2 - y0) == sign(y2 + dy - y0 - 1))
		{
			y2 += dy;
			y3 += dy;
		}
	}
	if (box->return_circle() == 3)
	{
		if (sign(x3 - x2) == sign(x3 + dx - x2 + 1) && sign(x3 - x2) == sign(x3 + dx - x2 - 1))
		{
			x3 += dx;
			x1 += dx;
		}
		if (sign(y3 - y1) == sign(y3 + dy - y1 + 1) && sign(y3 - y1) == sign(y3 + dy - y1 - 1))
		{
			y3 += dy;
			y2 += dy;
		}
	}
	rotation(t);
}

int Rectangle::half_space(double x1, double y1, double x2, double y2, double xt, double yt, double xp, double yp) /*проверяет, лежат ли точки t и p в одном полупространстве прямой 12*/
{
	double k = (y2 - y1)/(x2 - x1);
	double b = (x2*y1 - y2*x1)/(x2 - x1);
	if (k == 0 && b != 0) /*небольшой костыльчик*/
		if (!(xt > x1 && xt < x2) && !(xt < x1 && xt > x2))
			return 0;/*конец костыльчика*/
	if (sign(yt - k * xt - b) == sign(yp - k * xp - b))
		return 1;
	else
		return 0;
}

void Rectangle::rotation(int angle)
{
	this->angle += angle;
	if (this->angle > 360)
		this->angle = 0;
	else
		if (this->angle < 0)
			this->angle = 359;

	double dx = x0 - ( x0 - x3 ) / 2;
	double dy = y0 - ( y0 - y3 ) / 2;

	rot_point(x0, y0, dx, dy, angle);
	rot_point(x1, y1, dx, dy, angle);
	rot_point(x2, y2, dx, dy, angle);
	rot_point(x3, y3, dx, dy, angle);

	box->rotation(angle);
}

bool Rectangle::in(int x, int y)
{
	if (half_space(x0, y0, x1, y1, x, y, x2, y2))
		if (half_space(x0, y0, x2, y2, x, y, x3, y3))
			if (half_space(x1, y1, x3, y3, x, y, x0, y0))
				if (half_space(x2, y2, x3, y3, x, y, x0, y0))
				{
					press();
					return true;
				}
	unfocus();
	return false;
}

void Rectangle::fwrite(std::ofstream& out)
{
	int b1, b2;
	if (clr_menu->return_fill())
		b1 = 1;
	else
		b1 = 0;
	if (clr_menu->return_broken())
		b2 = 1;
	else
		b2 = 0;

	if (out.is_open())
	{
		out << "rec" << ' ' << angle << ' ' << x0 << ' ' << y0 << ' ' << x1 << ' ' << 
			y1 << ' ' << x2 << ' ' << y2 << ' ' << x3 << ' ' << y3 << ' ' << b1 << ' ' << /*имя класса, угол, координаты, булева величина заливки*/
			b2 << ' ' << (int)clr_menu->return_color_fon().r << ' ' << (int)clr_menu->return_color_fon().g << ' ' << /*булева величина границ и цвет фона*/
			(int)clr_menu->return_color_fon().b << ' ' << (int)clr_menu->return_color_fon().a << ' ' << (int)clr_menu->return_color_border().r << ' ' << /*цвет фона и цвет границ*/
			(int)clr_menu->return_color_border().g << ' ' << (int)clr_menu->return_color_border().b << ' ' << (int)clr_menu->return_color_border().a << /*цвет границ*/
			std::endl;
		out << box->return_point(0, 'x') << ' ' << box->return_point(0, 'y') << ' ' << box->return_point(1, 'x') << ' ' << box->return_point(1, 'y') << ' ' << /*координаты box*/
			box->return_point(2, 'x') << ' ' << box->return_point(2, 'y') << ' ' << box->return_point(3, 'x') << ' ' << box->return_point(3, 'y') << std::endl;
	}
}