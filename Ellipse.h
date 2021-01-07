#pragma once

#include "Point.h"
#include <fstream>

class Ellipse :public Point
{
	double a, b;

	void draw_fill(SDL_Renderer* renderer);
	void draw_unfill(SDL_Renderer* renderer);
public:
	Ellipse(double x0, double y0, double a, double b);
	Ellipse(int angle, int x0, int y0, int a, int b, bool _fill, bool _broken, SDL_Color fon, SDL_Color border);
	~Ellipse();
	void draw(SDL_Renderer* renderer);
	void move(double x0, double y0);
	void rotation(int angle);
	void rot_point(double& x, double& y, double x_c, double y_c, int angle);
	int half_space(double x1, double y1, double x2, double y2, double xt, double yt, double xp, double yp);
	bool in(int x, int y);
	void resize(double x, double y);
	int sign(double x);
	void fwrite(std::ofstream& out);
};
/*
          ^|
        b ||      a
          V| <--------->
-----------0------------
           |(x0, y0) 
		   |
*/