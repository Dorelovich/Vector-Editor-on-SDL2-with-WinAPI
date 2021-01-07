#include "Text_Menu.h"

#pragma warning(disable:4996) /*обижается на itoa*/

Text_Menu::Text_Menu(const char* fon, char inscription, int size)
{
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);

	x = 100;
	y = 100;
	w_window = DM.w;
	h_window = DM.h;
	swap = '0';
	_press = false;
	this->inscription = inscription;
	this->size = size; 
	font = fon;
	winapi_file_search(files);
	for (int i = 0; i < files.size(); i++)
		if (fon == "fonts/" + files[i])
			index_file = i;

	next_font = new Button(x + 110, y + 120, 50, 50, "images/next_arrow1.png", "images/next_arrow2.png");
	solid = new Button(x + 40, y + 220, 30, 30, "images/checkbox1.png", "images/checkbox2.png");
	shaded = new Button(x + 120, y + 220, 30, 30, "images/checkbox1.png", "images/checkbox2.png");
	blended = new Button(x + 200, y + 220, 30, 30, "images/checkbox1.png", "images/checkbox2.png");
	plus_size = new Button(x + 202, y + 335, 30, 30, "images/plus1.png", "images/plus2.png");
	minus_size = new Button(x + 41, y + 337, 25, 25, "images/minus1.png", "images/minus2.png");
	up = new Button(x + 40, y + 140, 30, 30, "images/up1.png", "images/up2.png");
	down = new Button(x + 200, y + 140, 30, 30, "images/down1.png", "images/down2.png");

	t_size = new Text(225, 435);
	t_font = new Text(155, 172);

	if (inscription == 's')
		solid->press();
	else
		if (inscription == 'h')
			shaded->press();
		else
			blended->press();
}

Text_Menu::~Text_Menu()
{
	delete next_font;
	delete solid;
	delete shaded;
	delete blended;
	delete plus_size;
	delete minus_size;
	delete up;
	delete down;

	delete t_size;
	delete t_font;
}

void Text_Menu::draw(SDL_Renderer* renderer)
{
	Image image(renderer, x, y, "images/text_menu.png");
	next_font->draw(renderer);
	solid->draw(renderer);
	shaded->draw(renderer);
	blended->draw(renderer);
	plus_size->draw(renderer);
	minus_size->draw(renderer);
	up->draw(renderer);
	down->draw(renderer);

	char c_size[8];
	_itoa(size, c_size, 10);
	t_size->print(renderer, c_size);
	
	winapi_file_search(files);
	if (files.size() > 0)
	{
		string name = files[index_file];
		t_font->print(renderer, name.c_str());
		SDL_Color c = { 0, 0, 0 };
		t_font->resize(140, 35);
		font = "fonts/" + name;
	}
}

void Text_Menu::move(int dx, int dy)
{
	if (x + dx > 0 && x + dx < w_window - w_menu)
		if (y + dy > 60 && y + dy < h_window - h_menu)
		{
			x += dx;
			y += dy;
			next_font->move(dx, dy);
			solid->move(dx, dy);
			shaded->move(dx, dy);
			blended->move(dx, dy);
			plus_size->move(dx, dy);
			minus_size->move(dx, dy);
			up->move(dx, dy);
			down->move(dx, dy);
			t_font->move(dx, dy);
			t_size->move(dx, dy);
		}
}

bool Text_Menu::in(int x, int y)
{	
	bool b = false;
	if (in_button(x, y, next_font))
	{
		next_font->press();
		if (index_file + 1 < files.size())
			index_file++;
		else
			index_file = 0;
		b = true;
	}
	if (in_button(x, y, solid))
	{
		inscription = 's';
		b = true;
	}
	if (in_button(x, y, shaded))
	{
		inscription = 'h';
		b = true;
	}
	if (in_button(x, y, blended))
	{
		inscription = 'b';
		b = true;
	}
	if (in_button(x, y, plus_size))
	{
		size += 2;
		b = true;
	}
	if (in_button(x, y, minus_size))
	{
		if (size > 8)
			size -= 2;
		b = true;
	}
	if (in_button(x, y, up))
	{
		swap = 'u';
		b = true;
	}
	if (in_button(x, y, down))
	{
		swap = 'd';
		b = true;
	}
	if (inscription == 's')
		solid->press();
	else
		if (inscription == 'h')
			shaded->press();
		else
			blended->press();
	if (b)
		return true;
	/*проверка клика по панельке*/
	if (x > this->x && x < this->x + w_menu)
		if (y > this->y && y < this->y + h_menu)
			return true;
	return false;
}

bool Text_Menu::in_button(int x, int y, Button* batton)
{
	bool b = batton->return_press();
	if (batton->in(x, y))
	{
		if (!b)
			batton->press();
		else
			batton->unpress();
		return true;
	}
	else
		if (b)
			batton->unpress();
	return false;
}

void Text_Menu::unpress()
{
	if (this)
	{
		swap = '0';
		next_font->unpress();
		plus_size->unpress();
		minus_size->unpress();
		up->unpress();
		down->unpress();
	}
}

int Text_Menu::return_size()
{
	return size;
}

char Text_Menu::return_inscription()
{
	return inscription;
}

std::string Text_Menu::return_font()
{
	return font;
}

#include <windows.h>

void Text_Menu::winapi_file_search(vector<string>& vec)
{
	WIN32_FIND_DATA findfile;
	// Нахождение самого первого файла
	HANDLE hFind = FindFirstFile("fonts/*.ttf", &findfile);
	if (hFind == INVALID_HANDLE_VALUE)
		return;
	vec.push_back(findfile.cFileName);
	// Поиск других файлов
	while (FindNextFile(hFind, &findfile))
		vec.push_back(findfile.cFileName);
	FindClose(hFind);
}

string Text_Menu::return_file_name()
{
	return files[index_file];
}

char Text_Menu::return_swap()
{
	if (this)
		return swap;
	else
		return '0';
}