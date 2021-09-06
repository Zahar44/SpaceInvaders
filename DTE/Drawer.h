#pragma once
#include "Bitmap.h";

class Game;
struct Size {
	double w = 0, h = 0;
};
struct Point {
	double x = 0, y = 0;
};

class Drawer
{
public:
	Drawer(Game* target) {
		this->target = target;
	}

	void Rectangle(Size size, Point point, size_t color);
	void Background(size_t color);
	void Texture(Point point, Bitmap& bmp);

private:
	Game* target;
};

