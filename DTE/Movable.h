#pragma once
#include <cmath>

#include "Drawer.h";
#include "Game.h";
#include "ColisionBox.h"

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

// TODO: move base logic for Movable and Shootable to base class
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
	void Kill(ColisionBox* box) {
		for (size_t i = 0; i < boxes.size(); i++)
		{
			if (boxes[i] == box)
				boxes.erase(boxes.begin() + i);
		}
		if (boxes.size() == 0)
			Kill();
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

	std::vector<ColisionBox*>& GetColisionBoxes() { return boxes; }

	ColisionBox* InRangeOf(Movable& mov);
protected:
	Size size = { 0, 0 };
	size_t color = 0;
	MovableContainer* items;
	Game::RenderInfo* renderInfo;
	Drawer* draw;

	std::vector<ColisionBox*> boxes;
	Point point = { 50, 20 };
	double mass = 100, speed = 0, frictionCoeff = 1;
	Force2D acceleration;

	virtual void CalculateVelocity();
	virtual Force2D CalculateFriction(Force2D force);
	virtual bool InRangeOf(ColisionBox& box);

	virtual void Resize() = 0;
private:
	bool SameSigns(double x, double y);
};
