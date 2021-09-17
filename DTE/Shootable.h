#pragma once
#include "Drawer.h";
#include "Bullet.h";

class Shootable abstract : public virtual Movable {
public:
	Shootable(double shootPower);
	Shootable() {
		shootPower = 0;
	};

	virtual void Shoot(Size bulletSize);
private:
	double shootPower;
};

