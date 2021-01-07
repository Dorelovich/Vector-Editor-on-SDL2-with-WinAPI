#include "Ellipse.h"

Ellipse::Ellipse(double x0, double y0, double a, double b)
{
	box = new Box(x0 - a - 20, y0 - b - 20, 2 * a + 40, 2 * b + 40);
	SDL_Color c = { 0,0,0,255 };
	clr_menu = new Color_Menu(c, c, 0, 0);
	_press = false;
	_paint = false;
	_focus = false;
	this->x0 = x0;
	this->y0 = y0;
	this->a = a;
	this->b = b;
	angle = 0;
}

Ellipse::Ellipse(int angle, int x0, int y0, int a, int b, bool _fill, bool _broken, SDL_Color fon, SDL_Color border)
{
	clr_menu = new Color_Menu(fon, border, _fill, _broken);
	box = new Box(-angle, x0 - a - 20, y0 - b - 20, 2 * a + 40, 2 * b + 40);
	this->angle = angle;
	this->x0 = x0;
	this->y0 = y0;
	this->a = a;
	this->b = b;
}

Ellipse::~Ellipse()
{
	delete box;
	delete clr_menu;
}

void Ellipse::draw(SDL_Renderer* renderer)
{
	if (clr_menu->return_fill())
		draw_fill(renderer);
	draw_unfill(renderer);
	if (_focus)
		box->draw(renderer);
}

void Ellipse::draw_fill(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, clr_menu->return_color_fon().r, clr_menu->return_color_fon().g, clr_menu->return_color_fon().b, clr_menu->return_color_fon().a);
	double x, y;
	double copy_x;
	double N;
	if (a > b)
		N = a;
	else
		N = b;

	for (int i = -N; i < N; i++)
	{
		for (int j = -N; j < N; j++)
		{
			if (i * i / (a * a) + j * j / (b * b) <= 1)
			{
				x = copy_x = i;
				y = j;
				x = x * cos(angle * M_PI / 180) + y * sin(angle * M_PI / 180);
				y = -copy_x * sin(angle * M_PI / 180) + y * cos(angle * M_PI / 180);
				SDL_RenderDrawPoint(renderer, x + x0 + 1, y + y0 + 1);
				SDL_RenderDrawPoint(renderer, x + x0, y + y0 + 1);
			}
		}
	}
}

void Ellipse::draw_unfill(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, clr_menu->return_color_border().r, clr_menu->return_color_border().g, clr_menu->return_color_border().b, clr_menu->return_color_border().a);
	double x, y;
	double first_x, first_y;
	double pred_x, pred_y;
	for (int i = 0; i < 360; i++)
	{
		/*Рисуем эллипс*/
		x = a * cos(i * M_PI / 180) + 1;
		y = b * sin(i * M_PI / 180) + 1;
		/*Поворачиваем его путём поворота координат*/
		double copy_x = x;
		x = x * cos(angle * M_PI / 180) + y * sin(angle * M_PI / 180);
		y = -copy_x * sin(angle * M_PI / 180) + y * cos(angle * M_PI / 180);
		/*Рисуем эллипс*/
		if (i > 0)
			if (clr_menu->return_broken())
				if (i % 4 == 0)
					SDL_RenderDrawLine(renderer, pred_x + x0, pred_y + y0, x + x0, y + y0);
				else;
			else
				SDL_RenderDrawLine(renderer, pred_x + x0, pred_y + y0, x + x0, y + y0);
		else
		{
			pred_x = x;
			pred_y = y;
			first_x = pred_x;
			first_y = pred_y;
			continue;
		}
		pred_x = x;
		pred_y = y;
	}
	SDL_RenderDrawLine(renderer, pred_x + x0, pred_y + y0, first_x + x0, first_y + y0);
}

void Ellipse::move(double x, double y)
{
	if (y0 + y - b> 60 + 20) /*проверка того, что не выходим на toolbar*/
	{
		x0 += x;
		y0 += y;
		box->move(x, y);
	}
}

void Ellipse::rotation(int angle)
{
	this->angle -= angle; 
	if (this->angle > 360)
		this->angle = 0;
	else
		if (this->angle < 0)
			this->angle = 359;
	box->rotation(angle);
}

void Ellipse::rot_point(double& x, double& y, double x_c, double y_c, int angle)
{
	double tx = x - x_c;
	double ty = y - y_c;

	x = tx * cos(angle * M_PI / 180) - ty * sin(angle * M_PI / 180) + (x - tx);
	y = tx * sin(angle * M_PI / 180) + ty * cos(angle * M_PI / 180) + (y - ty);
}

int Ellipse::half_space(double x1, double y1, double x2, double y2, double xt, double yt, double xp, double yp) /*проверяет, лежат ли точки t и p в одном полупространстве прямой 12*/
{
	double k = (y2 - y1) / (x2 - x1);
	double b = (x2 * y1 - y2 * x1) / (x2 - x1);
	if (k == 0 && b != 0) /*небольшой костыльчик*/
		if (!(xt > x1 && xt < x2) && !(xt < x1 && xt > x2))
			return 0;/*конец костыльчика*/
	if (sign(yt - k * xt - b) == sign(yp - k * xp - b))
		return 1;
	else
		return 0;
}

int Ellipse::sign(double x)
{
	if (x > 0.0001)
		return 1;
	else
		if (x < -0.0001)
			return -1;
		else
			return 0;
}

void Ellipse::resize(double dx, double dy)
{
	if (box->return_circle() == 0)
	{
		if ((a - dx + 1 > 0) && (a - dx - 1 > 0))
		{
			a -= dx / 2;
			x0 += dx / 2;
		}
		if ((b - dy + 1 > 0) && (b - dy - 1 > 0))
		{
			b -= dy / 2;
			y0 += dy / 2;
		}
	}
	if (box->return_circle() == 1)
	{
		if ((a + dx / 2 + 1 > 0) && (a + dx / 2 - 1 > 0))
		{
			a += dx / 2;
			x0 += dx / 2;
		}
		if ((b - dy / 2 + 1 > 0) && (b - dy / 2 - 1 > 0))
		{
			b -= dy / 2;
			y0 += dy / 2;
		}
	}
	if (box->return_circle() == 2)
	{
		if ((a - dx / 2 + 1 > 0) && (a - dx / 2 - 1 > 0))
		{
			a -= dx / 2;
			x0 += dx / 2;
		}
		if ((b + dy / 2 + 1 > 0) && (b + dy / 2 - 1 > 0))
		{
			b += dy / 2;
			y0 += dy / 2;
		}
	}
	if (box->return_circle() == 3)
	{
		if ((a + dx / 2 + 1 > 0) && (a + dx / 2 - 1 > 0))
		{
			a += dx / 2;
			x0 += dx / 2;
		}
		if ((b + dy / 2 + 1 > 0) && (b + dy / 2 - 1 > 0))
		{
			b += dy / 2;
			y0 += dy / 2;
		}
	}
}

bool Ellipse::in(int x, int y) /*выражаю особую признательность этому господину https://stackru.com/questions/45278563/test-tochki-i-ellipsa-povernutyij-algoritm */
{
	double alfa = angle * M_PI / 180;
	if ( pow(cos(alfa)*(x - x0) + sin(alfa)*(y - y0),2) / (a*a) + pow(sin(alfa) * (x - x0) + cos(alfa) * (y - y0), 2) / (b * b) - 1 <= 0.0001)
		if ( half_space(box->return_point(1,'x'), box->return_point(1,'y'), box->return_point(3,'x'), box->return_point(3,'y'), x, y, x0, y0) )
			if (half_space(box->return_point(0, 'x'), box->return_point(0, 'y'), box->return_point(2, 'x'), box->return_point(2, 'y'), x, y, x0, y0))
			{
				press();
				return true;
			}
	unfocus();
	return false;
}

void Ellipse::fwrite(std::ofstream& out)
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
		out << "ell" << ' ' << angle << ' ' << x0 << ' ' << y0 << ' ' << a << ' ' << b << ' ' << b1 << ' ' << b2 << ' ' << /*имя класса, угол, координаты, булева величина заливки*/
		(int)clr_menu->return_color_fon().r << ' ' << (int)clr_menu->return_color_fon().g << ' ' << /*булева величина границ и цвет фона*/
		(int)clr_menu->return_color_fon().b << ' ' << (int)clr_menu->return_color_fon().a << ' ' << (int)clr_menu->return_color_border().r << ' ' << /*цвет фона и цвет границ*/
		(int)clr_menu->return_color_border().g << ' ' << (int)clr_menu->return_color_border().b << ' ' << (int)clr_menu->return_color_border().a << /*цвет границ*/
		std::endl;
}
