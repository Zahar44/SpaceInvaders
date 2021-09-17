#pragma once
#include "Texture.h";

#include <vector>

class ColisionBox {
public:
	ColisionBox();
	ColisionBox(Size size, Point point, double color);

	static std::vector<ColisionBox*>* Create(Texture& texture, Size size, Point point);

	Size GetSize() { return size; }
	Point GetPoint() { return point; }
	void SetPoint(Point point) { this->point = point; }
	double GetColor() { return color; }
private:
	Size size;
	Point point;
	double color;
};

