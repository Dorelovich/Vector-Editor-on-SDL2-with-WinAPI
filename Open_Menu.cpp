#include "Open_Menu.h"

#include <windows.h>

Open_Menu::Open_Menu()
{
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	w_window = DM.w;
	h_window = DM.h;

	_focus = false;
	_press_button = false;
	next_file = new Button(w_window / 2 + 65, h_window / 2 - 25, 50, 37, "images/next_arrow1.png", "images/next_arrow2.png");
	open_file = new Button(w_window / 2 - 45, h_window / 2 + 40, 100, 35, "images/open_file1.png", "images/open_file2.png");

	index_file = 0;
}

Open_Menu::~Open_Menu()
{
	delete next_file;
	delete open_file;
}

void Open_Menu::draw(SDL_Renderer* renderer)
{
	Image image(renderer, w_window / 2 - 135, h_window / 2 - 97, "images/open_menu.png");
	next_file->draw(renderer);
	open_file->draw(renderer);

	if (files.size() > 0)
	{
		Text text(w_window / 2 - 135 + 50, h_window / 2 - 97 + 75);
		string name = files[index_file];
		if (name.size() > 11)
		{
			for (int i = 8; i <= 11; i++)
				name[i] = '.';
			name.erase(11);
			name.push_back('v');
			name.push_back('e');
			name.push_back('c');
		}
		text.print(renderer, name.c_str());
		SDL_Color c = { 0, 0, 0 };
		text.resize(140, 35);
		text.draw_border(renderer, c);
	}
}

bool Open_Menu::in(int x, int y)
{
	/*проверка клика по кнопке следующего файла*/
	if (next_file->in(x, y))
	{
		next_file->press();
		if (index_file + 1 < files.size())
			index_file++;
		else
			index_file = 0;
		return true;
	}
	else
		next_file->unpress();
	/*проверка клика по кнопке открытия файла*/
	if (open_file->in(x, y))
	{
		open_file->press();
		_press_button = true;
		return true;
	}
	else
		open_file->unpress();
	/*проверка клика по панельке*/
	if (x > w_window / 2 - 135 + 5 && x < w_window / 2 + 135 - 5)
		if (y > h_window / 2 - 97 + 5 && y < h_window / 2 + 97 - 5)
			return true;
	return false;
}

void Open_Menu::focus()
{
	_focus = true;
	winapi_file_search(files);
}

void Open_Menu::unfocus()
{
	next_file->unfocus();
	open_file->unfocus();
	_focus = false;
}

bool Open_Menu::return_focus()
{
	return _focus;
}

void Open_Menu::up_buttoms()
{
	next_file->unpress();
	open_file->unpress();
}

void Open_Menu::unpress_button()
{
	_press_button = false;
}

void Open_Menu::winapi_file_search(vector<string> &vec)
{
	WIN32_FIND_DATA findfile;
	// Нахождение самого первого файла
	HANDLE hFind = FindFirstFile("files/*.vec", &findfile);
	if (hFind == INVALID_HANDLE_VALUE)
		return;
	vec.push_back(findfile.cFileName);
	// Поиск других файлов
	while (FindNextFile(hFind, &findfile))
		vec.push_back(findfile.cFileName);
	FindClose(hFind);
}

bool Open_Menu::return_press_button()
{
	return _press_button;
}

string Open_Menu::return_file_name()
{
	return files[index_file];
}