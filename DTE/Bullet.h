#pragma once
#include "Game.h";
#include "Drawer.h";
#include "Movable.h"
#include "MovableContainer.h";

class Bullet : public Movable
{
public:
	Bullet(MovableContainer* items, Game::RenderInfo* renderInfo, Drawer* draw, Point point, Size size) :
		Movable(items, renderInfo, draw, size, point, 0x00FDFF, 1, 0) {}
	
	void Draw() override;
private:
	bool CheckColision();
	bool CheckColision(Movable& item);

	// Inherited via Movable
	virtual void Resize() override;
};

