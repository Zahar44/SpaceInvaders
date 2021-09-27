#pragma once
#include "Drawer.h";
#include "Bullet.h";

class Shootable abstract : public virtual Movable {
public:
	Shootable(double shootPower);
	Shootable() {
		shootPower = 0;
		delayMax = 100;
	};

	virtual void Shoot(Size bulletSize);
protected:
	int delay = 0;
	int delayMax;
private:
	double shootPower;
};

