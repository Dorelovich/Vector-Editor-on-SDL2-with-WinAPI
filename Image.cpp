#include "Image.h"

Image::Image(SDL_Renderer* renderer, int x, int y, const std::string& file)
{
	img = loadTexture(file, renderer);
	renderTexture(img, renderer, x, y);
}

Image::Image(SDL_Renderer* renderer, int x, int y, int w, int h, const std::string& file)
{
	img = loadTexture(file, renderer);
	renderTexture(img, renderer, x, y, w, h);
}

Image::~Image()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(img);
}

SDL_Texture* Image::loadTexture(const std::string& file, SDL_Renderer* ren)
{
	texture = IMG_LoadTexture(ren, file.c_str());
	return texture;
}

/*отображение изображения в координатах x и y, привести к размеру w, h*/
void Image::renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

/*отображение изображения в координатах x и y без масштабирования*/
void Image::renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y)
{
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
}