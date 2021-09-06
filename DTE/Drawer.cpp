#include "Drawer.h"
#include "Game.h"

void Drawer::Rectangle(Size size, Point point, size_t color) {
	if (!target->renderInfo.buffer) return;
	auto render = target->renderInfo;

	int wStart = render.wigth * point.x / 100;
	int wEnd = wStart + render.wigth * size.w / 100;
	int w = wEnd - wStart;
	wStart -= w / 2;
	wEnd -= w / 2;

	int hStart = render.heigth * point.y / 100;
	int hEnd = hStart + render.heigth * size.h / 100;
	int h = hEnd - hStart;
	hStart -= h / 2;
	hEnd -= h / 2;

	for (size_t i = hStart; i < hEnd && i < render.heigth; i++)
	{
		size_t* pixel = (size_t*)render.buffer + wStart + i * render.wigth;
		for (size_t j = wStart; j < wEnd && j < render.wigth; j++)
		{
			*pixel++ = color;
		}
	}
}

void Drawer::Background(size_t color) {
	if (!target->renderInfo.buffer) return;
	auto render = target->renderInfo;
	size_t* pixel = (size_t*)render.buffer;

	for (size_t i = 0; i < render.heigth; i++)
	{
		for (size_t j = 0; j < render.wigth; j++)
		{
			*pixel++ = color;
		}
	}
}

void Drawer::Texture(Point point, Bitmap& bmp) {
	if (!target->renderInfo.buffer) return;
	auto render = target->renderInfo;
	
	int size = sqrt(bmp.Size());
	int wStart = render.wigth * point.x / 100;
	int wEnd = wStart + size;
	int hStart = render.heigth * point.y / 100;
	int hEnd = hStart + size;

	int k = 0;

	for (size_t i = 0; i < 100; i++)
	{
		size_t* pixel = (size_t*)render.buffer + 100 + i * render.wigth;
		for (size_t j = 0; j < 100; j++)
		{
			*pixel++ = bmp[i * j];
		}
	}

	/*for (size_t i = hStart; i < hEnd && i < render.heigth; i++)
	{
		size_t* pixel = (size_t*)render.buffer + wStart + i * render.wigth;
		for (size_t j = wStart; j < wEnd && j < render.wigth; j++)
		{
			*pixel++ = bmp[k++];
		}
	}*/
}
