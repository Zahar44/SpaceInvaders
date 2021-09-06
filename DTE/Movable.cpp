#include "Movable.h"
#include "MovableContainer.h";

Movable::Movable(
	MovableContainer* items,
	Game::RenderInfo* renderInfo,
	Drawer* draw,
	Size size,
	Point startPosition,
	size_t color,
	double mass,
	double frictionCoeff
) {
	this->items = items;
	this->size = size;
	this->color = color;
	this->renderInfo = renderInfo;
	this->draw = draw;
	this->point = startPosition;
	this->mass = mass;
	this->frictionCoeff = frictionCoeff;

	(*items).Add(*this);
}

Movable::~Movable() {
	items->Remove(*this);
}

