#include "Shootable.h"

Shootable::Shootable(double shootPower) {
	this->shootPower = shootPower;
}

void Shootable::Shoot(Size bulletSize) {
	Point p = { point.x, point.y };
	p.y = shootPower > 0 ? p.y + size.h / 2 : p.y - size.h + bulletSize.h;
	p.x = p.x + size.w / 2 - bulletSize.w;
	auto bullet = new Bullet(items, renderInfo, draw, p, bulletSize);
	bullet->ApplyForce({ acceleration.horizontal / 2, shootPower });
}
