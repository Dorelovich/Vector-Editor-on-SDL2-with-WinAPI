#include "Color_Menu.h"

Color_Menu::Color_Menu(SDL_Color fon, SDL_Color border, bool _fill, bool _broken)
{
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	
	x = 100;
	y = 100;
	w_window = DM.w;
	h_window = DM.h;
	swap = '0';
	_press = false;
	this->_fill = _fill;
	this->_broken = _broken;
	clr_fon = fon;
	clr_border = border;

	filling = new Button(x + 100, y + 25, 75, 50, "images/zalivka1.png", "images/zalivka2.png");
	broken_line = new Button(x + 100, y + 180, 75, 50, "images/broken_line1.png", "images/broken_line2.png");
	up = new Button(x + 80, y + 335, 30, 30, "images/up1.png", "images/up2.png");
	down = new Button(x + 160, y + 335, 30, 30, "images/down1.png", "images/down2.png");

	slider_f_r = new Slider(x + 35, y + 90);
	slider_f_r->set_value(clr_fon.r);
	slider_f_g = new Slider(x + 35, y + 120);
	slider_f_r->set_value(clr_fon.g);
	slider_f_b = new Slider(x + 35, y + 150);
	slider_f_r->set_value(clr_fon.b);

	slider_b_r = new Slider(x + 35, y + 240);
	slider_f_r->set_value(clr_border.r);
	slider_b_g = new Slider(x + 35, y + 270);
	slider_f_r->set_value(clr_border.g);
	slider_b_b = new Slider(x + 35, y + 300);
	slider_f_r->set_value(clr_border.b);

	if (_fill)
		filling->press();
	if (_broken)
		broken_line->press();
}

Color_Menu::~Color_Menu()
{
	delete filling;
	delete broken_line;
	delete up;
	delete down;

	delete slider_f_r;
	delete slider_f_g;
	delete slider_f_b;

	delete slider_b_r;
	delete slider_b_g;
	delete slider_b_b;
}

SDL_Color Color_Menu::return_color_fon()
{
	return clr_fon;
}

SDL_Color Color_Menu::return_color_border()
{
	if (this)
		return clr_border;
	else
	{
		SDL_Color c = { 0,0,0 };
		return c;
	}
}

void Color_Menu::draw(SDL_Renderer* renderer)
{
	Image image(renderer, x, y, "images/color_menu.png");
	filling->draw(renderer);
	broken_line->draw(renderer);
	up->draw(renderer);
	down->draw(renderer);

	slider_f_r->draw(renderer);
	slider_f_g->draw(renderer);
	slider_f_b->draw(renderer);

	slider_b_r->draw(renderer);
	slider_b_g->draw(renderer);
	slider_b_b->draw(renderer);
}

void Color_Menu::move(int dx, int dy)
{
	if (x + dx > 0 && x + dx < w_window - w_menu)
		if (y + dy > 60 && y + dy < h_window - h_menu)
		{
			x += dx;
			y += dy;
			filling->move(dx, dy);
			broken_line->move(dx, dy);
			up->move(dx, dy);
			down->move(dx, dy);

			slider_f_r->move(dx, dy);
			slider_f_g->move(dx, dy);
			slider_f_b->move(dx, dy);

			slider_b_r->move(dx, dy);
			slider_b_g->move(dx, dy);
			slider_b_b->move(dx, dy);
		}
}

bool Color_Menu::in(int x, int y)
{	/*проверка клика по кнопке заливки*/
	bool b = filling->return_press();
	if (filling->in(x, y))
	{
		if (!b)
		{
			_fill = true;
			filling->press();
		}
		else
		{
			_fill = false;
			filling->unpress();
		}
		return true;
	}
	else
		if (b)
			filling->press();
	/*проверка клика по кнопке пунктирной линии*/
	b = broken_line->return_press();
	if (broken_line->in(x, y))
	{
		if (!b)
		{
			_broken = true;
			broken_line->press();
		}
		else
		{
			_broken = false;
			broken_line->unpress();
		}
		return true;
	}
	else
		if (b)
			broken_line->press();
	/*проверка клика по кнопкам вверх вниз*/
	if (up->in(x, y))
	{
		up->press();
		swap = 'u';
		b =  true;
	}
	else
		up->unpress();
	if (down->in(x, y))
	{
		down->press();
		swap = 'd';
		b = true;
	}
	else
		down->unpress();
	/*проверка клика по слайдеру*/
	if (slider_f_r->in(x, y))
		return true;
	if (slider_f_g->in(x, y))
		return true;
	if (slider_f_b->in(x, y))
		return true;

	if (slider_b_r->in(x, y))
		return true;
	if (slider_b_g->in(x, y))
		return true;
	if (slider_b_b->in(x, y))
		return true;
	/*проверка клика по панельке*/
	if (x > this->x && x < this->x + w_menu)
		if (y > this->y && y < this->y + h_menu)
			return true;
	return false;
}

void Color_Menu::press()
{
	_press = true;
}

void Color_Menu::unpress()
{
	_press = false;
	swap = '0';
	up->unpress();
	down->unpress();
}

bool Color_Menu::return_press()
{
	return _press;
}

bool Color_Menu::return_fill()
{
	if (this)
		return _fill;
	else
		return false;
}

bool Color_Menu::return_broken()
{
	if (this)
		return _broken;
	return false;
}

bool Color_Menu::return_move_slider()
{
	if (slider_f_r->return_press())
		return true;
	if (slider_f_g->return_press())
		return true;
	if (slider_f_b->return_press())
		return true;
	
	if (slider_b_r->return_press())
		return true;
	if (slider_b_g->return_press())
		return true;
	if (slider_b_b->return_press())
		return true;

	return false;
}

void Color_Menu::move_slider(int dx)
{
	if (slider_f_r->return_press())
	{
		slider_f_r->recolor(dx);
		clr_fon.r = slider_f_r->return_value();
		return;
	}
	if (slider_f_g->return_press())
	{
		slider_f_g->recolor(dx);
		clr_fon.g = slider_f_g->return_value();
		return;
	}
	if (slider_f_b->return_press())
	{
		slider_f_b->recolor(dx);
		clr_fon.b = slider_f_b->return_value();
		return;
	}

	if (slider_b_r->return_press())
	{
		slider_b_r->recolor(dx);
		clr_border.r = slider_b_r->return_value();
		return;
	}
	if (slider_b_g->return_press())
	{
		slider_b_g->recolor(dx);
		clr_border.g = slider_b_g->return_value();
		return;
	}
	if (slider_b_b->return_press())
	{
		slider_b_b->recolor(dx);
		clr_border.b = slider_b_b->return_value();
		return;
	}
}

void Color_Menu::up_sliders()
{
	slider_f_r->unpress();
	slider_f_g->unpress();
	slider_f_b->unpress();

	slider_b_r->unpress();
	slider_b_g->unpress();
	slider_b_b->unpress();
}

char Color_Menu::return_swap()
{
	if (this)
		return swap;
	else
		return '0';
}