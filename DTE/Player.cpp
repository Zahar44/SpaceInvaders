#include "Player.h"

void Player::Draw() {
	CalculateVelocity();

	Size s1 = { size.w / 3, size.h / 2 };
	Point p1 = { point.x, point.y - point.y / 100 };
	draw->Rectangle(s1, p1, color);

	Size s2 = { size.w - size.w / 5, size.h / 2 };
	Point p2 = { point.x, point.y - size.h / 2 };
	draw->Rectangle(s2, p2, color);
}

void Player::Shoot() {
	Point p = { point.x, point.y + size.h / 2 };
	auto bullet = new Bullet(items, renderInfo, draw, p);
	bullet->ApplyForce({ acceleration.horizontal / 2, 1.5f });
}
