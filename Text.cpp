#include "Text.h"

Text::Text(int x0, int y0) :x(x0),y(y0)
{
    TTF_Init();
    inscription = 's';
    name_font = "fonts/CharisSILR.ttf";
    size = 20;
    font = TTF_OpenFont(name_font.c_str(), size);
    w = 100;
    h = 100;
    _focus = false;
};

Text::~Text()
{
    TTF_CloseFont(font);
    TTF_Quit();
};

void Text::print(SDL_Renderer* renderer, const char text[512])
{
    font = TTF_OpenFont(name_font.c_str(), size);
    SDL_Color color = { 0, 0, 0 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Surface* surface;
    if (inscription == 's')
        surface = TTF_RenderUTF8_Solid(font, text, color);
    else
        if (inscription == 'h')
        {
            SDL_Color fg = { 0, 0, 0 };
            SDL_Color bg = { 255, 255, 255 };
            surface = TTF_RenderUTF8_Shaded(font, text, fg, bg);
        }
        else
            surface = TTF_RenderUTF8_Blended(font, text, color);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &ttf_w, &ttf_h);
    SDL_Rect dstrect = { x, y, ttf_w, ttf_h };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Text::refont(string new_font)
{
    name_font = new_font;
}

void Text::resize(int new_size)
{
    size = new_size;
}

void Text::reins(char c)
{
    inscription = c;
}

void Text::focus()
{
    _focus = true;
}

void Text::unfocus()
{
    _focus = false;
}

bool Text::return_focus()
{
    return _focus;
}

int Text::return_ttf_w()
{
    return ttf_w;
}

int Text::return_ttf_h()
{
    return ttf_h;
}

bool Text::in(int x, int y)
{
    if (x >= this->x && x <= this->x + w)
        if (y >= this->y && y <= this->y + h)
            return true;
    return false;
}

void Text::draw_border(SDL_Renderer* renderer, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, x - 5, y, x + w + 5, y);
    SDL_RenderDrawLine(renderer, x - 5, y, x - 5, y + h);
    SDL_RenderDrawLine(renderer, x + w + 5, y, x + w + 5, y + h);
    SDL_RenderDrawLine(renderer, x - 5, y + h, x + w + 5, y + h);
}

void Text::resize(int new_w, int new_h)
{
    w = new_w;
    h = new_h;
}

void Text::move(int dx, int dy)
{
    x += dx;
    y += dy;
}

string Text::return_font()
{
    return name_font;
}

int Text::return_size()
{
    return size;
}

char Text::return_inscription()
{
    return inscription;
}