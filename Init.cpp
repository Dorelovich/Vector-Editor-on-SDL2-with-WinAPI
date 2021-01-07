#include "Init.h"

Init::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	main_cycle();
};

Init::~Init()
{
	SDL_Quit();
};

void Init::click_L(Window& W, int x, int y)
{
	/*проверка на клик по какому-то объекту на экране*/
	if (!W.in(x, y))
		if (W.press_primitive)
		{
			W.press_primitive->unfocus();
			W.press_primitive = nullptr;
		}
	/*Если нажата кнопка сохранения*/
	if (W.press_button() == 1)
		W.save_menu->focus();
	/*Если нажата кнопка открытия файла*/
	if (W.press_button() == 2)
		W.open_menu->focus();
	/*Если нажата кнопка удаления*/
	if (W.press_button() == 3)
		W.delete_prim();
}

void Init::click_R(Window& W, int x, int y)
{
	/*Проверяем, если не выбрана кнопка и клик по примитиву, то вызываем меню для управления цветами примитива*/
	if (!W.press_button())
	{
		if (W.press_primitive)
			if (W.press_primitive->in(x, y))
				W.press_primitive->paint();
			else
			{
				W.press_primitive->unfocus();
				W.press_primitive = nullptr;
			}
	}
	else
		if (W.press_primitive)
			W.press_primitive->unfocus();
	/*Если нажата кнопка эллипса*/
	if (W.press_button() == 4)
	{
		if (y < 60 + 30) /*проверка на попытку рисования на панели инструментов*/
			return;
		Ellipse* ell = new Ellipse(x, y, 60, 30);
		Point* p;
		p = ell;
		W.add_prim(p);
	}
	/*Если нажата кнопка прямой*/
	if (W.press_button() == 5)
	{
		if (y < 60 + 1) /*проверка на рисование на панели инструментов что нельзя*/
			return;
		Rectangle* r = new Rectangle(x - 50, y, 100, 2);
		Point* p;
		p = r;
		W.add_prim(p);
	}
	/*Если нажата кнопка точки*/
	if (W.press_button() == 6)
	{
		if (y < 60 + 10) /*проверка на рисование на панели инструментов что нельзя*/
			return;
		Ellipse* ell = new Ellipse(x, y, 10, 10);
		Point* p;
		p = ell;
		W.add_prim(p);
	}
	/*Если нажата кнопка прямоугольника*/
	if (W.press_button() == 7)
	{
		if (y < 60 + 15) /*проверка на рисование на панели инструментов что нельзя*/
			return;
		Rectangle* r = new Rectangle(x - 30, y - 15, 60, 30);
		Point* p;
		p = r;
		W.add_prim(p);
	}
	/*Если нажата кнопка текста*/
	if (W.press_button() == 8)
	{
		if (y < 60 + 15) /*проверка на рисование на панели инструментов что нельзя*/
			return;
		Text_Primitive* r = new Text_Primitive(x, y);
		Point* p;
		p = r;
		W.add_prim(p);
	}
	W.unpress_button();
}

void Init::up(Window& W)
{
	/*Поднимаем выбранную кнопку на панели инструментов*/
	W.toolbar->unpress();
	/*Поднимаем выделенный примитив*/
	if (W.press_primitive)
	{
		W.press_primitive->unpress();
		W.press_primitive->box->unpress();
		W.press_primitive->clr_menu->unpress();
		W.press_primitive->clr_menu->up_sliders();
		W.press_primitive->text_menu->unpress();
	}
	W.open_menu->up_buttoms();
	W.save_menu->up_buttoms();
}

void Init::mothion(Window& W, int xrel, int yrel)
{
	if (W.press_primitive && W.press_primitive->retrun_press() && !W.press_primitive->box->retrun_press())
		W.press_primitive->move(xrel,yrel);
	if (W.press_primitive && W.press_primitive->box->retrun_focus() && W.press_primitive->box->retrun_press())
	{
		W.press_primitive->resize(xrel, yrel);
		W.press_primitive->box->resize(xrel, yrel);
	}
	if (W.press_primitive && W.press_primitive->return_paint() && W.press_primitive->clr_menu->return_press() && !W.press_primitive->clr_menu->return_move_slider())
	{
		if (W.press_primitive->its_text())
			W.press_primitive->text_menu->move(xrel, yrel);
		W.press_primitive->clr_menu->move(xrel, yrel);
	}
	if (W.press_primitive && W.press_primitive->clr_menu->return_move_slider())
		W.press_primitive->clr_menu->move_slider(xrel);
}

void Init::wheel(Window& W, int angle)
{
	if (W.press_primitive->retrun_focus())
		W.press_primitive->rotation(angle);
}

void Init::key_down(Window& W, SDL_Keycode c)
{
	W.unpress_button();
	if (W.save_menu->return_focus_text())
	{
		if (c >= 'a' && c <= 'z')
			W.save_menu->add_char(c);
		if (c >= '0' && c <= '9')
			W.save_menu->add_char(c);
		if (c == SDLK_BACKSPACE)
			W.save_menu->delete_char();
		return;
	}
	if (W.press_primitive->retrun_focus())
	{
		if (c == SDLK_BACKSPACE) /*нажат escape*/
		{
			W.press_primitive->delete_char();
			return;
		}
		if (c >= 'a' && c <= 'z') /*если нажаты КЛАВИШИ с 'a' по 'z'*/
		{
			if (winapi_return_language()) /*если язык русский*/
			{
				string str;
				if (W.press_primitive->return_press_shift())
					str = covert_to_russian(c, 'u').c_str(); /*перевод в кирилицу верхний регистр*/
				else
					str = covert_to_russian(c, 'l').c_str(); /*перевод в кирилицу нижний регистр*/
				for (int i = 0; i < str.size(); i++)
					W.press_primitive->add_char(str[i]); /*запись двух байтов*/
				return;
			}
			else /*если язык английский*/
			{
				if (W.press_primitive->return_press_shift()) 
					c = toupper(c); /*перевод английский в верхний регистр*/
				W.press_primitive->add_char(c);
				return;
			}
		}
		if ((c == 1093 || c == 1098 || c == 1078 || c == 1101 || c == 1073 || c == 1102 || c == 1105) && winapi_return_language()) /*буквы { х ъ ж э б ю ё }*/
		{
			string str = "tr";
			if (W.press_primitive->return_press_shift())
				str = covert_to_russian(c, 'u').c_str(); /*перевод в кирилицу верхний регистр*/
			else
				str = covert_to_russian(c, 'l').c_str(); /*перевод в кирилицу нижний регистр*/
			for (int i = 0; i < str.size(); i++)
				W.press_primitive->add_char(str[i]);
			return;
		}	
		if ((c >= '0' && c <= '9' || c == '`' || c == '-' || c == '=' || c == '[' || c == ']' || c == '\\' || c == '/' || c == ' ' || c == ',' || c == '.' || c == ';') 
			&& !W.press_primitive->return_press_shift()) /*символы без шифта*/
		{
			if (winapi_return_language())
				W.press_primitive->add_char(convert_symbol(c, 'r'));
			else
				W.press_primitive->add_char(convert_symbol(c, 'e'));
			return;
		}
		if (c == SDLK_SPACE)
			W.press_primitive->add_char(c);
		if ((c >= '0' && c <= '9' || c == '-' || c == '=') || c == '`' || c == ';' || c == '\'' || c == ',' || 
			c == '.' || c == '/' || c == '\\' || c == '[' || c ==']') /*все оставшиеся символы, получаемые шифтом */
		{
			if (winapi_return_language())
				W.press_primitive->add_char(convert_shift_symbol(c, 'r'));
			else
				W.press_primitive->add_char(convert_shift_symbol(c, 'e'));
			return;
		}
		if (c == SDLK_LSHIFT || c == SDLK_RSHIFT) /*нажат правый или левый шифт*/
			W.press_primitive->press_shift();
	}
}

void Init::key_up(Window& W, SDL_Keycode c)
{
	if (W.press_primitive && (c == SDLK_LSHIFT || c == SDLK_RSHIFT) )
		W.press_primitive->unpress_shift();
}

#pragma once
#include "windows.h"

bool Init::winapi_return_language() /*вернёт язык потока, с которым работает пользователь*/
{
	HKL hk = GetKeyboardLayout(0);
	int lang = LOWORD(hk);
	if (lang == 0x0419)
		return true;
	else
		return false;
}

string Init::covert_to_russian(char c, char reg) /*вернёт два байта!*/
{
	switch (c)
	{
	case 'a':
		return (reg == 'u') ? (string)"Ф" : (string)"ф";
	case 'b':
		return (reg == 'u') ? (string)"И" : (string)"и";
	case 'c':
		return (reg == 'u') ? (string)"С" : (string)"с";
	case 'd':
		return (reg == 'u') ? (string)"В" : (string)"в";
	case 'e':
		return (reg == 'u') ? (string)"У" : (string)"у";
	case 'f':
		return (reg == 'u') ? (string)"А" : (string)"а";
	case 'g':
		return (reg == 'u') ? (string)"П" : (string)"п";
	case 'h':
		return (reg == 'u') ? (string)"Р" : (string)"р";
	case 'i':
		return (reg == 'u') ? (string)"Ш" : (string)"ш";
	case 'j':
		return (reg == 'u') ? (string)"О" : (string)"о";
	case 'k':
		return (reg == 'u') ? (string)"Л" : (string)"л";
	case 'l':
		return (reg == 'u') ? (string)"Д" : (string)"д";
	case 'm':
		return (reg == 'u') ? (string)"Ь" : (string)"ь";
	case 'n':
		return (reg == 'u') ? (string)"Т" : (string)"т";
	case 'o':
		return (reg == 'u') ? (string)"Щ" : (string)"щ";
	case 'p':
		return (reg == 'u') ? (string)"З" : (string)"з";
	case 'q':
		return (reg == 'u') ? (string)"Й" : (string)"й";
	case 'r':
		return (reg == 'u') ? (string)"К" : (string)"к";
	case 's':
		return (reg == 'u') ? (string)"Ы" : (string)"ы";
	case 't':
		return (reg == 'u') ? (string)"Е" : (string)"е";
	case 'u':
		return (reg == 'u') ? (string)"Г" : (string)"г";
	case 'v':
		return (reg == 'u') ? (string)"М" : (string)"м";
	case 'w':
		return (reg == 'u') ? (string)"Ц" : (string)"ц";
	case 'x':
		return (reg == 'u') ? (string)"Ч" : (string)"ч";
	case 'y':
		return (reg == 'u') ? (string)"Н" : (string)"н";
	case 'z':
		return (reg == 'u') ? (string)"Я" : (string)"я";
	case 'E':
		return (reg == 'u') ? (string)"Х" : (string)"х";
	case 'J':
		return (reg == 'u') ? (string)"Ъ" : (string)"ъ";
	case '6':
		return (reg == 'u') ? (string)"Ж" : (string)"ж";
	case 'M':
		return (reg == 'u') ? (string)"Э" : (string)"э";
	case '1':
		return (reg == 'u') ? (string)"Б" : (string)"б";
	case 'N':
		return (reg == 'u') ? (string)"Ю" : (string)"ю";
	case 'Q':
		return (reg == 'u') ? (string)"Ё" : (string)"ё";
	}
}

char Init::convert_symbol(char c, char lang)
{
	switch (c)
	{
	case '`':
		return '`';
	case '-':
		return '-';
	case '=':
		return '=';
	case '[':
		return '[';
	case ']':
		return ']';
	case '\\':
		return '\\';
	case ';':
		return ';';
	case '\'':
		return '\'';
	case ',':
		return ',';
	case '.':
		return '.';
	case '/':
		return (lang != 'r') ? '/' : '.';
	case '0':
		return '0';
	case '1':
		return '1';
	case '2':
		return '2';
	case '3':
		return '3';
	case '4':
		return '4';
	case '5':
		return '5'; 
	case '6':
		return '6';
	case '7':
		return '7';
	case '8':
		return '8';
	case '9':
		return '9';
	case ' ':
		return ' ';
	}
}

char Init::convert_shift_symbol(char c, char lang)
{
	switch (c)
	{
	case '`':
		return '~';
	case '1':
		return '!';
	case '2':
		return (lang != 'r') ? '@' : '\"';
	case '3':
		return '#';
	case '4':
		return (lang != 'r') ? '$' : ';';
	case '5':
		return '%';
	case '6':
		return (lang != 'r') ? '^' : ':';
	case '7':
		return (lang != 'r') ? '&' : '?';
	case '8':
		return '*';
	case '9':
		return '(';
	case '0':
		return ')';
	case '-':
		return '_';
	case '=':
		return '+';
	case '[':
		return '{';
	case ']':
		return '}';
	case ';':
		return ':';
	case '\'':
		return '"';
	case ',':
		return '<';
	case '/':
		return (lang != 'r') ? '?' : ',';
	case '.':
		return (lang != 'r') ? '>' : ',';
	case '\\':
		return (lang != 'r') ? '|' : '/';
	}
}

void Init::main_cycle()
{
	Window W;
	SDL_Event event;
	bool quit = false;

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type) 
			{
				case SDL_QUIT:
					quit = true;
				break;

				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
						quit = true;
					key_down(W, event.key.keysym.sym);
				break;

				case SDL_KEYUP:
					key_up(W, event.key.keysym.sym);
					break;

				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
						click_L(W, event.motion.x, event.motion.y);
					else
						click_R(W, event.motion.x, event.motion.y);
				break;

				case SDL_MOUSEBUTTONUP:
					up(W);
				break;

				case SDL_MOUSEMOTION:
					mothion(W, event.motion.xrel, event.motion.yrel);
				break;

				case SDL_MOUSEWHEEL:
					wheel(W, event.wheel.y);
				break;
			}
		}
		W.show();
		SDL_Delay(fps);
	}
}
