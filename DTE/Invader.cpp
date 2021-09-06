#include "Invader.h"

void Invader::Draw() {
	CalculateVelocity();

	Size s1 = { size.w / 3, size.h / 2 };
	Point p1 = { point.x, point.y };
	draw->Rectangle(s1, p1, color);
	//draw->Texture(point, texture);

	Size s2 = { size.w - size.w / 5, size.h / 2 };
	Point p2 = { point.x, point.y - size.h / 2 };
	draw->Rectangle(s2, p2, color);
}
