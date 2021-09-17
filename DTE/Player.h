#pragma once
#include <vector>

#include "Game.h";
#include "Drawer.h";
#include "Bullet.h";
#include "Movable.h";
#include "MovableContainer.h";
#include "Shootable.h";

class Player : public Shootable
{
public:
	Player(MovableContainer* items, Game::RenderInfo* renderInfo, Drawer* draw) :
		Shootable(0.5), 
		Movable(items, renderInfo, draw, { 5, 5 }, { 50, 10 }, 0x00FDFF, 300) {
		this->items = items;
		boxes = *ColisionBox::Create(draw->GetTexture(Player::type), size, point);
	}

	void Draw() override;
private:
	static const char* type;
	MovableContainer* items;

	// Inherited via Movable
	virtual void CalculateVelocity() override;
	virtual void Resize() override;
};

