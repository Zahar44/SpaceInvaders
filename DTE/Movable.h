#pragma once
#include <cmath>

#include "Drawer.h";
#include "Game.h";

struct Force2D {
	double horizontal, vertical;

	Force2D operator+ (const Force2D& other) const noexcept {
		Force2D out = { 0, 0 };
		out.horizontal = this->horizontal + other.horizontal;
		out.vertical = this->vertical + other.vertical;
		return out;
	}

	Force2D operator- (const Force2D& other) const noexcept {
		Force2D out = { 0, 0 };
		out.horizontal = this->horizontal - other.horizontal;
		out.vertical = this->vertical - other.vertical;
		return out;
	}
	Force2D operator- (const double value) const noexcept {
		Force2D out = { 0, 0 };
		out.horizontal = this->horizontal - value;
		out.vertical = this->vertical - value;
		return out;
	}

	Force2D operator/ (const double value) const noexcept {
		Force2D out = { 0, 0 };
		out.horizontal = this->horizontal / value;
		out.vertical = this->vertical / value;
		return out;
	}

	Force2D operator/ (const Force2D& other) const noexcept {
		Force2D out = { 0, 0 };
		out.horizontal = this->horizontal / other.horizontal;
		out.vertical = this->vertical / other.vertical;
		return out;
	}

	Force2D operator* (const double value) const noexcept {
		Force2D out = { 0, 0 };
		out.horizontal = this->horizontal * value;
		out.vertical = this->vertical * value;
		return out;
	}

	Force2D& RoundOff(int decimals) {
		float pow_10 = pow(10.0f, (float)decimals);
		this->horizontal = double(int(this->horizontal * pow_10) / pow_10);
		this->vertical = double(int(this->vertical * pow_10) / pow_10);
		return *this;
	}
};

class MovableContainer;

class Movable abstract
{
public:

	Movable() = default;

	Movable(
		MovableContainer* items,
		Game::RenderInfo* renderInfo,
		Drawer* draw,
		Size size,
		Point startPosition,
		size_t color,
		double mass,
		double frictionCoeff = 1
	);

	~Movable();

	void Kill() {
		delete this;
	}

	void ChangeColor(size_t color) {
		(*this).color = color;
	}

	virtual void Draw() = 0;
	
	void ApplyForce(Force2D force) {
		acceleration = acceleration + force / mass;
	}

	Point GetPoint() {
		return point;
	}

	bool InRangeOf(Movable& mov) {
		double left = mov.point.x - mov.size.w / 2;
		double right = mov.point.x + mov.size.w / 2;
		double top = mov.point.y + mov.size.h / 2;
		double bottom = mov.point.y - mov.size.h / 2;

		return ((*this).point.x - (*this).size.w / 2 > left && (*this).point.x + (*this).size.w / 2 < right)
			&& ((*this).point.y - (*this).size.h / 2 > bottom && (*this).point.y + (*this).size.h / 2 < top);
	}

protected:
	Size size = { 0, 0 };
	size_t color = 0;
	MovableContainer* items;
	Game::RenderInfo* renderInfo;
	Drawer* draw;

	Point point = { 50, 20 };
	double mass = 100, speed = 0, frictionCoeff = 1;
	Force2D acceleration;

	virtual void CalculateVelocity() {
		if (point.x < 2 || point.x > 98) {
			acceleration.horizontal = -acceleration.horizontal;
		}

		Force2D da = CalculateFriction(acceleration) / renderInfo->delta;

		point.x += acceleration.horizontal;
		point.y += acceleration.vertical;
		acceleration = (acceleration - da).RoundOff(3);
	}

	virtual Force2D CalculateFriction(Force2D force) {
		Force2D friction = 
		{ 
			mass * 9.8 * frictionCoeff,
			mass * 9.8 * frictionCoeff
		};

		friction.horizontal = min(fabs(friction.horizontal), fabs(force.horizontal));
		friction.vertical = min(fabs(friction.vertical), fabs(force.vertical));

		if(force.horizontal < 0)
			friction.horizontal = -friction.horizontal;
		if(force.vertical < 0)
			friction.vertical = -friction.vertical;

		return friction;
	}

private:
	bool sameSigns(double x, double y)
	{
		return x > 0 && y > 0 || x < 0 && y < 0;
	}
};
