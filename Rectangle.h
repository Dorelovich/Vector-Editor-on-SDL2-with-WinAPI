#pragma once

#include "Point.h"
#include <fstream>

class Rectangle: public Point
{
	double x1, y1, x2, y2, x3, y3;

	void rot_point(double& x, double& y, double w, double h, int angle);
	int half_space(double x1, double y1, double x2, double y2, double xt, double yt, double xp, double yp);
	void draw_fill(SDL_Renderer* renderer);
	void draw_unfill(SDL_Renderer* renderer);
public:
	Rectangle(double x, double y, double w, double h);
	Rectangle(int angle, double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, bool _fill, bool _broken, SDL_Color fon, SDL_Color border,
		double b_x0, double b_y0, double b_x1, double b_y1, double b_x2, double b_y2, double b_x3, double b_y3);
	~Rectangle();
	void draw(SDL_Renderer* renderer);
	void move(double x, double y);
	void rotation(int angle);
	bool in(int x, int y);
	void resize(double x, double y);
	void fwrite(std::ofstream& out);
};

/*x0y0             x1y1
_______________________
|					  |
|                     |
|	                  |
_______________________
x2y2              x3y3*/

