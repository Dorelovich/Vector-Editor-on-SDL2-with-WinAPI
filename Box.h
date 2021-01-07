#pragma once

#include "SDL.h"

class Box
{
	double x0, y0, x1, y1, x2, y2, x3, y3;
	int angle;
	int circle;
	bool _press;
	bool _focus;

	void rot_point(double& x, double& y, double x_c, double y_c, int angle);
	void DrawLine(SDL_Renderer* renderer, double x0, double y0, double x1, double y1);
	void DrawCircle(SDL_Renderer* renderer, double x0, double y0, double r);
	int sign(double x);
public:
	Box(double x, double y, double w, double h);
	Box(int angle, double x, double y, double w, double h);
	Box(int angle, double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3);
	void rotation(int angle);
	void draw(SDL_Renderer* renderer);
	void move(double x, double y);
	bool in(int x, int y);
	void resize(double x, double y);
	double return_point(int index, char axis);

	void press();
	void unpress();
	void unfocus();
	bool retrun_press();
	bool retrun_focus();
	int return_circle();
};

