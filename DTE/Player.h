#pragma once
#include <vector>

#include "Game.h";
#include "Drawer.h";
#include "Bullet.h";
#include "Movable.h";
#include "MovableContainer.h";

class Player : public Movable
{
public:
	Player(MovableContainer* items, Game::RenderInfo* renderInfo, Drawer* draw) : 
		Movable(items, renderInfo, draw, { 5, 5 }, { 50, 20 }, 0x00FDFF, 300) {
		this->items = items;
	}

	void Draw() override;
	void Shoot();
private:
	MovableContainer* items;
};

