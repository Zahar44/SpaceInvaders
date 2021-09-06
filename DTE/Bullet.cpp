#include "Bullet.h"

void Bullet::Draw() {
	if (!CheckColision()) {
		draw->Rectangle(size, point, color);
		CalculateVelocity();
	}
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
	if (InRangeOf(item)) {
		item.Kill();
		(*this).Kill();
		return true;
	}

	return false;
}
