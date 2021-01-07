#include "Save_Menu.h"

Save_Menu::Save_Menu()
{
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	w_window = DM.w;
	h_window = DM.h;

	_focus = false;
	_press_button = false;
	save_file = new Button(w_window / 2 - 45, h_window / 2 + 40, 100, 35, "images/save_file1.png", "images/save_file2.png");
	text = new Text(w_window / 2 - 135 + 35, h_window / 2 - 97 + 70);
	text->resize(205, 40);
}

Save_Menu::~Save_Menu()
{
	delete save_file;
	delete text;
}

void Save_Menu::draw(SDL_Renderer* renderer)
{
	Image image(renderer, w_window / 2 - 135, h_window / 2 - 97, "images/save_menu.png");
	save_file->draw(renderer);

	SDL_Color color;
	if (text->return_focus())
		color = { 0, 0, 0 };
	else
		color = { 128, 128, 128 };
	text->draw_border(renderer, color);
	text->print(renderer, return_file_name().c_str());
}

bool Save_Menu::in(int x, int y)
{
	/*проверка клика по кнопке сохранить*/
	if (save_file->in(x, y))
	{
		save_file->press();
		text->unfocus();
		_press_button = true;
		return true;
	}
	else
		save_file->unpress();
	/*проверка клика по области текста*/
	if (text->in(x, y))
	{
		text->focus();
		return true;
	}
	else
		text->unfocus();
	/*проверка клика по панельке*/
	if (x > w_window / 2 - 135 + 5 && x < w_window / 2 + 135 - 5)
		if (y > h_window / 2 - 97 + 5 && y < h_window / 2 + 97 - 5)
			return true;
	return false;
}

void Save_Menu::focus()
{
	_focus = true;
}

void Save_Menu::unfocus()
{
	save_file->unfocus();
	_focus = false;
	deq.clear();
}

bool Save_Menu::return_focus()
{
	return _focus;
}

void Save_Menu::up_buttoms()
{
	save_file->unpress();
}

void Save_Menu::add_char(char c)
{
	if (text->return_ttf_w() > 205 - 15)
		return;
	deq.push_back(c);
}

void Save_Menu::delete_char()
{
	if (deq.size() == 0)
		return;
	deq.pop_back();
}

bool Save_Menu::return_focus_text()
{
	return text->return_focus();
}

bool Save_Menu::return_press_button()
{
	return _press_button;
}

void Save_Menu::unpress_button()
{
	_press_button = false; 
}

string Save_Menu::return_file_name()
{
	string str;
	for (int i = 0; i < deq.size(); i++)
		str.push_back(deq[i]);
	return str;
}