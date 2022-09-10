#include <algorithm>

#include "Drawer.h";
#include "Game.h";
#include "Invader.h";
#include "Bitmap.h";
#include "Texture.h";
#include "ColisionBox.h";
#include "Player.h";

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
		int* pixel = (int*)render.buffer + wStart + i * render.wigth;
		for (size_t j = wStart; j < wEnd && j < render.wigth; j++)
		{
			*pixel++ = (int)color;
		}
	}
}

void Drawer::Background(size_t color) {
	if (!target->renderInfo.buffer) return;
	auto render = target->renderInfo;
	int* pixel = (int*)render.buffer;

	for (size_t i = 0; i < render.heigth; i++)
	{
		for (size_t j = 0; j < render.wigth; j++)
		{
			*pixel++ = color;
		}
	}
}

void Drawer::WithTexture(std::vector<ColisionBox*>& boxes) {
	for (size_t i = 0; i < boxes.size(); i++)
	{
		Rectangle(boxes[i]->GetSize(), boxes[i]->GetPoint(), boxes[i]->GetColor());
	}
}

void Drawer::LoadTextures() {
	Texture* player = new Texture("player_1.txt");
	Texture* invader = new Texture("ship_1.txt");
	textures.insert({ typeid(Invader).name(), invader });
	textures.insert({ typeid(Player).name(), player   });
}

Texture& Drawer::GetTexture(const char* key) {
	return *textures[key];
}

void Drawer::Resize() {
	//std::for_each(textures.begin(), textures.end(), [&](std::pair<const char*, Bitmap*> keyValue) {
	//	Size newSize = {
	//		target->renderInfo.wigth * 20 / 100,
	//		target->renderInfo.heigth * 20 / 100,
	//	};

	//	keyValue.second->Resize(newSize);
	//});
}
