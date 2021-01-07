#include "Window.h"

Window::Window()
{
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	w = DM.w;
	h = DM.h;
	press_primitive = nullptr;
	window = SDL_CreateWindow("Vector Editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, 0);
	toolbar = new Toolbar(w);
	open_menu = new Open_Menu();
	save_menu = new Save_Menu();
};

Window::~Window()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	for (Point* index : primitives)
		delete index;

	delete toolbar;
	delete open_menu;
	delete save_menu;
};

void Window::show()
{
	SDL_Color canvas = { 255, 255, 255, 255 };
	SDL_SetRenderDrawColor(renderer, canvas.r, canvas.g, canvas.b, canvas.a);
	SDL_RenderClear(renderer);
	for (Point* index : primitives) /*отрисовка всех примитивов на экране (не кнопок)*/
		index->draw(renderer);
	if (press_primitive->return_paint())
	{
		if (press_primitive->its_text())
			press_primitive->text_menu->draw(renderer);
		else
			press_primitive->clr_menu->draw(renderer);
	}
	toolbar->draw(renderer); /*панель инструментов (в том числе кнопок)*/
	if (open_menu->return_focus() == true)
		open_menu->draw(renderer);
	if (save_menu->return_focus() == true)
		save_menu->draw(renderer);
	SDL_RenderPresent(renderer);
}

void Window::add_prim(Point* p)
{
	if (press_primitive)
		press_primitive->unpress();
	press_primitive = p;
	press_primitive->press();
	press_primitive->unpress();
	primitives.push_back(p);
}

void Window::delete_prim()
{
	if (!press_primitive)
		return;
	if (!press_primitive->retrun_focus())
		return;
	for (Point* index : primitives)
	{
		if (index == press_primitive)
		{
			delete press_primitive;
			press_primitive = nullptr;
			primitives.remove(index);
			return;
		}
	}
}

bool Window::in(int x, int y)
{
	if (open_menu->return_focus() && open_menu->in(x, y))
	{
		if (open_menu->return_press_button())
		{
			open_file(open_menu->return_file_name().c_str());
			open_menu->unpress_button();
		}
		return true;
	}
	else
		open_menu->unfocus();

	if (save_menu->return_focus() && save_menu->in(x, y))
	{	
		if (save_menu->return_press_button())
		{
			save_file(save_menu->return_file_name().c_str());
			save_menu->unpress_button();
		}
		return true;
	}
	else
		save_menu->unfocus();

	if (toolbar->in(x, y))
		return true;
	if (press_primitive)
		if (press_primitive->box->in(x, y))
		{
			press_primitive->press();
			return true;
		}
	if (press_primitive && press_primitive->return_paint() && press_primitive->clr_menu->in(x, y))
	{
		swap_prim();
		if (press_primitive->its_text())
			if (press_primitive->text_menu->in(x, y)) /*проверка нажатий на кнопки меню текста. В случае нажатия будут помечены*/
				swap_prim();
		press_primitive->clr_menu->press();
		return true;
	}
	else
		if (press_primitive)
				press_primitive->clr_menu->unpress();
	std::reverse(primitives.begin(), primitives.end());
	for (Point* index : primitives)
	{
		if (index->in(x, y))
		{
			if (press_primitive)
			{
				press_primitive->unfocus();
				press_primitive = nullptr;
			}
			press_primitive = index;
			press_primitive->press();

			std::reverse(primitives.begin(), primitives.end());
			return true;
		}
	}
	std::reverse(primitives.begin(), primitives.end());
	return false;
}

int Window::press_button()
{
	return toolbar->index_button;
}

void Window::unpress_button()
{
	toolbar->index_button = 0;
}

void Window::save_file(string name_file)
{
	std::ofstream out;
	std::string full_name = "files/" + name_file + ".vec";
	out.open(full_name.c_str());
	for (Point* n : primitives)
		n->fwrite(out);
	out.close();
}

void Window::open_file(string name_file)
{
	while (!primitives.empty())
	{
		delete primitives.front();
		primitives.pop_front();
	}

	std::ifstream in;
	std::string full_name = "files/" + name_file;
	in.open(full_name.c_str());
	std::string name_class; 
	while (in >> name_class )
	{
		int angle;
		double x0, y0;
		bool _fill, _broken;
		struct Vec_Color
		{
			int r, g, b, a;
		};
		Vec_Color fon, border;

		if (name_class == "rec")
		{
			double x1, y1, x2, y2, x3, y3; //координаты прямоугольника
			double b_x0, b_y0, b_x1, b_y1, b_x2, b_y2, b_x3, b_y3; //координаты box
			in >> angle >> x0 >> y0 >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> _fill >> _broken >> fon.r >> fon.g >> fon.b >> fon.a >> border.r >> border.g >> border.b >> border.a;

			in >> b_x0 >> b_y0 >> b_x1 >> b_y1 >> b_x2 >> b_y2 >> b_x3 >> b_y3;
			SDL_Color cl1 = { fon.r, fon.g, fon.b, fon.a };
			SDL_Color cl2 = { border.r, border.g, border.b, border.a };
			Rectangle* rec = new Rectangle(angle, x0, y0, x1, y1, x2, y2, x3, y3, _fill, _broken, cl1, cl2, b_x0, b_y0, b_x1, b_y1, b_x2, b_y2, b_x3, b_y3);
			Point* p;
			p = rec;
			add_prim(p);
			p->unfocus();
		}
		if (name_class == "ell")
		{
			double a, b;
			SDL_Color c = { 0,0,0,255 };
			in >> angle >> x0 >> y0 >> a >> b >> _fill >> _broken >> fon.r >> fon.g >> fon.b >> fon.a >> border.r >> border.g >> border.b >> border.a;
			SDL_Color cl1 = { fon.r, fon.g, fon.b, fon.a };
			SDL_Color cl2 = { border.r, border.g, border.b, border.a };
			Ellipse* ell = new Ellipse(angle, x0, y0, a, b, _fill, _broken, cl1, cl2);
			Point* p;
			p = ell;
			add_prim(p);
			p->unfocus();
		}
		if (name_class == "txt")
		{
			std::deque<char> deq;
			std::string font, str;
			int size;
			char inscription;
			in >> x0 >> y0 >> font >> size >> inscription;
			getline(in, str);
			for (int i = 0; i < str.size()-1; i++)
				deq.push_back(str[i+1]);
			Text_Primitive* txt = new Text_Primitive(x0, y0, font, size, inscription, deq);
			Point* p;
			p = txt;
			add_prim(p);
			p->unfocus();
		}
	}
	in.close();
}

void Window::swap_prim()
{
	char c;
	if (press_primitive->clr_menu->return_swap() != '0')
		c = press_primitive->clr_menu->return_swap();
	else
		c = press_primitive->text_menu->return_swap();

	list<Point*>::iterator it1 = primitives.begin();
	list<Point*>::iterator it2 = it1;

	int index1 = 1; //Номер первого элемента
	int index2; //Номер второго элемента

	for (Point* i : primitives)
		if (i == press_primitive)
			break;
		else
			index1++;
	
	if (c == 'u')
		index2 = index1 + 1;
	else
		if (c == 'd')
			index2 = index1 - 1;
		else
			return;

	for (auto i = 0; i < index1 - 1; i++) it1++; //Смещаем итераторы на нужные позиции
	for (auto i = 0; i < index2 - 1; i++) it2++;

	bool b1 = false, b2 = false;
	for (list<Point*>::iterator it = primitives.begin(); it != primitives.end(); ++it)
		if (it == it1)
		{
			b1 = true;
			break;
		}
	for (list<Point*>::iterator it = primitives.begin(); it != primitives.end(); ++it)
		if (it == it2)
		{
			b2 = true;
			break;
		}
	if (!b1 || !b2)
		return;
	swap(*it1, *it2);  //меняем
}