#pragma once
#include "Game.h";
#include "Drawer.h";
#include "Movable.h";
#include "MovableContainer.h";
#include "Bitmap.h";
#include "Shootable.h";

class Invader : public Shootable {
public:

	Invader() = default;

	Invader(MovableContainer* items, Game::RenderInfo* renderInfo, Drawer* draw, Point startPoint) :
		Shootable(-0.5),
		Movable(items, renderInfo, draw, { 5, 15 }, startPoint, 0xff00ff, 100) {
		boxes = *ColisionBox::Create(draw->GetTexture(Invader::type), size, point);
	}

	void Draw() override;
	void Play();
private:
	static const char* type;

	// Inherited via Movable
	virtual void Resize() override;
};

