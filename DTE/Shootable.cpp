#include "Shootable.h"

Shootable::Shootable(double shootPower) {
	this->shootPower = shootPower;
	delayMax = 100;
}

void Shootable::Shoot(Size bulletSize) {
	Point location = { point.x, point.y };
	location.y = shootPower > 0 ? location.y + size.h / 2 : location.y - size.h + bulletSize.h;
	location.x = location.x + size.w / 2 - bulletSize.w;
	auto bullet = new Bullet(items, renderInfo, draw, location, bulletSize);
	bullet->ApplyForce({ acceleration.horizontal / 2, shootPower });
}
