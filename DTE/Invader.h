#pragma once
#include "Game.h";
#include "Drawer.h";
#include "Movable.h";
#include "MovableContainer.h";
#include "Bitmap.h";

class Invader : public Movable {
public:

	Invader() = default;

	Invader(MovableContainer* items, Game::RenderInfo* renderInfo, Drawer* draw, Point startPoint) :
		Movable(items, renderInfo, draw, { 5, 5 }, startPoint, 0xff00ff, 100) {
		texture.LoadFile("D:\\projects\\DTE\\DTE\\ship_1.bmp");
	}

	void Draw() override;

private:
	Bitmap texture;
};

