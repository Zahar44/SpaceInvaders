#include "Bullet.h"

void Bullet::Draw() {
	draw->Rectangle(size, point, color);
	CalculateVelocity();
	CheckColision();
}

bool Bullet::CheckColision() {
	bool killed = false;
	int i = 0;

	while (!killed && i < items->Count()) {
		killed = CheckColision((*items)[i++]);
	}

	return killed;
}

bool Bullet::CheckColision(Movable& item) {
	ColisionBox* box = InRangeOf(item);
	if (box) {
		item.Kill(box);
		(*this).Kill();
		return true;
	}

	return false;
}

void Bullet::Resize()
{
}
