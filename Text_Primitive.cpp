#include "Text_Primitive.h"

Text_Primitive::Text_Primitive(int x, int y)
{
	x0 = x;
	y0 = y;
	w = h = 25;
	box = new Box(0, 0, 0, 0);
	text = new Text(x, y);
	SDL_Color c = { 0, 0, 0, 255 };
	clr_menu = new Color_Menu(c, c, 0, 0);
	text_menu = new Text_Menu("fonts/CharisSILR.ttf", 's', 20);
	_press_shift = false;
	_press = false;
	_paint = false;
	_focus = true;
}

Text_Primitive::Text_Primitive(int x0, int y0, string font, int size, char inscription, deque<char> deq)
{
	for (int i = 0; i < deq.size();i++)
		this->deq.push_back(deq[i]);
	this->x0 = x0;
	this->y0 = y0;
	w = h = 25;
	box = new Box(0, 0, 0, 0);
	text = new Text(x0, y0);
	SDL_Color c = { 0, 0, 0, 255 };
	clr_menu = new Color_Menu(c, c, 0, 0);
	text_menu = new Text_Menu(font.c_str(), inscription, size);
	_press_shift = false;
	_press = false;
	_paint = false;
	_focus = false;
}

Text_Primitive::~Text_Primitive()
{
	delete box;
	delete clr_menu;
	delete text;
}

void Text_Primitive::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, clr_menu->return_color_border().r, clr_menu->return_color_border().g, clr_menu->return_color_border().b, clr_menu->return_color_border().a);
	SDL_Color c = { 0,0,0,255 };
	text->refont(text_menu->return_font());
	text->resize(text_menu->return_size());
	text->reins(text_menu->return_inscription());
	text->print(renderer, return_file_name().c_str());
	w = text->return_ttf_w();
	h = text->return_ttf_h();
	if (w < 10)
		w = h = 25;
	text->resize(w, h);
	if (_focus)
		text->draw_border(renderer, c);
}

void Text_Primitive::move(double x, double y)
{
	if (y0 + y > 60) /*проверка того, что не выходим на toolbar*/
	{
		x0 += x;
		y0 += y;
		text->move(x, y);
	}
}

bool Text_Primitive::in(int x, int y)
{
	if (x >= x0 && x <= x0 + w)
		if (y >= y0 && y <= y0 + h)
		{
			press();
			return true;
		}
	unfocus();
	return false; 
}

void Text_Primitive::add_char(char c)
{
	deq.push_back(c);
}

void Text_Primitive::delete_char()
{
	if (!deq.size())
		return;
	if (!single_byte_symbol(deq[deq.size() - 1]))
		deq.pop_back();
	deq.pop_back();
}

string Text_Primitive::return_file_name()
{
	string str;
	for (int i = 0; i < deq.size(); i++)
		str.push_back(deq[i]);
	return str;
}

void Text_Primitive::press_shift()
{
	_press_shift = true;
}

void Text_Primitive::unpress_shift()
{
	_press_shift = false;
}

bool Text_Primitive::return_press_shift()
{
	return _press_shift; 
}

bool Text_Primitive::single_byte_symbol(char c) /*английские буквы,цифры и внеязыковые символы представляются одним байтом, русские символы - двумя. Эта проверка нужна для того, чтобы при удалении
												  русского символа удалялось сразу два байта, а при удалении английского - только один*/
{
	if (c >= '0' && c <= '9')
		return true;
	if (c >= 'a' && c <= 'z')
		return true;
	if (c >= 'A' && c <= 'Z')
		return true;
	if (c == '`' || c == '~' || c == '!' || c == '@' || c == '"' || c == '#' || c == '$' || c == ';' || c == '%' || c == '^' || c == ':' || c == '&' || c == '?' || c == '*' || c == '(' ||
		c == ')' || c == '_' || c == '-' || c == '=' || c == '+' || c == ' ' || c == ' [' || c == ']' || c == '{' || c == '}' || c == ':' || c == '\'' || c == ',' || c == '<' || c == '>' ||
		c == '.' || c == '/' || c == '?' || c == '\\' || c == '|')
		return true;
	return false;
}

bool Text_Primitive::its_text()
{
	return true;
}

void Text_Primitive::fwrite(std::ofstream& out)
{
	if (out.is_open())
	{
		out << "txt" << ' ' << x0 << ' ' << y0 << ' ' << text->return_font() << ' ' << text->return_size() << ' ' << text->return_inscription() << ' ';
		for (int i = 0; i < deq.size(); i++)
			out << deq[i];
		out << std::endl;
	}
}