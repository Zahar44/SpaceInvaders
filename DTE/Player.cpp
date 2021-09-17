#include "Player.h"

void Player::Draw() {
	CalculateVelocity();

	draw->WithTexture(boxes);
	//Size s1 = { size.w / 3, size.h / 2 };
	//Point p1 = { point.x, point.y - point.y / 100 };
	//draw->Rectangle(s1, p1, color);

	//Size s2 = { size.w - size.w / 5, size.h / 2 };
	//Point p2 = { point.x, point.y - size.h / 2 };
	//draw->Rectangle(s2, p2, color);
}



void Player::CalculateVelocity() {
	if (point.x < 3 && acceleration.horizontal < 0) {
		acceleration.horizontal = 0;
	}
	if (point.x > 97 && acceleration.horizontal > 0) {
		acceleration.horizontal = 0;
	}

	Force2D da = CalculateFriction(acceleration) / renderInfo->delta;

	point.x += acceleration.horizontal;
	point.y += acceleration.vertical;
	for (size_t i = 0; i < boxes.size(); i++)
	{
		Point p = boxes[i]->GetPoint();
		p.x += acceleration.horizontal;
		p.y += acceleration.vertical;
		boxes[i]->SetPoint(p);
	}
	acceleration = (acceleration - da).RoundOff(3);
}

void Player::Resize()
{
}

const char* Player::type = typeid(Player).name();