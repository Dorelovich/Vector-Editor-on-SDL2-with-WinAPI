#include "Toolbar.h"

Toolbar::Toolbar(int w)
{
	this->w = w;
	press_button = nullptr;
	index_button = 0;

	int interval = (w - 200) / 7;
	save = new Button(100, 15, 35, 35, "images/save1.png", "images/save2.png");
	open = new Button(100 + interval, 15, 35, 35, "images/open1.png", "images/open2.png");
	del = new Button(100 + 2 * interval, 15, 35, 35, "images/delete1.png", "images/delete2.png");
	ellips = new Button(100 + 3 * interval, 15, 50, 30, "images/ellips1.png", "images/ellips2.png");
	line = new Button(100 + 4 * interval, 15, 35, 35, "images/line1.png", "images/line2.png");
	point = new Button(100 + 5 * interval, 20, 25, 25, "images/point1.png", "images/point2.png");
	rectangle = new Button(100 + 6 * interval, 15, 35, 35, "images/rectangle1.png", "images/rectangle2.png");
	text = new Button(100 + 7 * interval, 15, 35, 35, "images/text1.png", "images/text2.png");
}

Toolbar::~Toolbar()
{
	delete save;
	delete open;
	delete del;
	delete ellips;
	delete line;
	delete point;
	delete rectangle;
	delete text;
}

void Toolbar::draw(SDL_Renderer* renderer)
{
	/*отрисовка фона панели инструментов*/
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.b);
	SDL_Rect toolbar = { 0, 0, w, 60 };
	SDL_RenderFillRect(renderer, &toolbar);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	toolbar = { 0, 57, w, 3 };
	SDL_RenderFillRect(renderer, &toolbar);
	/*отрисовка всех кнопок*/
	save->draw(renderer);
	open->draw(renderer);
	del->draw(renderer);
	ellips->draw(renderer);
	line->draw(renderer);
	point->draw(renderer);
	rectangle->draw(renderer);
	text->draw(renderer);
}

void Toolbar::unpress()
{
	press_button->unpress();
}

bool Toolbar::in(int x, int y)
{
	int interval = (w - 200) / 6;

	if (save->in(x, y))
	{
		index_button = 1;
		press_button = save;
		return true;
	}
	if (open->in(x, y))
	{
		index_button = 2;
		press_button = open;
		return true;
	}
	if (del->in(x, y))
	{
		index_button = 3;
		press_button = del;
		return true;
	}
	if (ellips->in(x, y))
	{
		index_button = 4;
		press_button = ellips;
		return true;
	}
	if (line->in(x, y))
	{
		index_button = 5;
		press_button = line;
		return true;
	}
	if (point->in(x, y))
	{
		index_button = 6;
		press_button = point;
		return true;
	}
	if (rectangle->in(x, y))
	{
		index_button = 7;
		press_button = rectangle;
		return true;
	}
	if (text->in(x, y))
	{
		index_button = 8;
		press_button = text;
		return true;
	}
	press_button = nullptr;
	index_button = 0;
	return false;
}
