#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <string>

class Image
{
	SDL_Texture* texture;
	SDL_Texture* img;

	SDL_Texture* loadTexture(const std::string& file, SDL_Renderer* ren);
	void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h);
	void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y);
public:
	Image(SDL_Renderer* renderer, int x, int y, const std::string& file); /*картинка без масштабирования*/
	Image(SDL_Renderer* renderer, int x, int y, int w, int h, const std::string& file); /*картинка с масштабированием*/
	~Image();
};