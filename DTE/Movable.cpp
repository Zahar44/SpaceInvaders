#include "Movable.h";
#include "MovableContainer.h";
#include "Texture.h";

Movable::Movable(
	MovableContainer* items,
	Game::RenderInfo* renderInfo,
	Drawer* draw,
	Size size,
	Point startPosition,
	size_t color,
	double mass,
	double frictionCoeff
) {
	this->items = items;
	this->size = size;
	this->color = color;
	this->renderInfo = renderInfo;
	this->draw = draw;
	this->point = startPosition;
	this->mass = mass;
	this->frictionCoeff = frictionCoeff;

	(*items).Add(*this);
}

Movable::~Movable() {
	//items->Remove(*this);
}

void Movable::Kill() {
	(*items).Remove(*this);
}

void Movable::Kill(ColisionBox* box) {
	for (size_t i = 0; i < boxes.size(); i++)
	{
		if (boxes[i] == box)
			boxes.erase(boxes.begin() + i);
	}
	if (boxes.size() == 0)
		Kill();
}

void Movable::ChangeColor(size_t color) {
	(*this).color = color;
}

void Movable::ApplyForce(Force2D force) {
	acceleration = acceleration + force / mass;
}

Point Movable::GetPoint() {
	return point;
}

ColisionBox* Movable::InRangeOf(Movable& mov) {
	bool inRange = false;
	for (size_t i = 0; i < mov.boxes.size(); i++)
	{
		inRange = InRangeOf(*mov.boxes[i]);

		if (inRange)
			return mov.boxes[i];
	}
	return nullptr;
}

void Movable::CalculateVelocity() {
	if (point.x < 3 && acceleration.horizontal < 0 
     || point.x > 97 && acceleration.horizontal > 0) {
		acceleration.horizontal = -acceleration.horizontal;
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

Force2D Movable::CalculateFriction(Force2D force) {
	Force2D friction =
	{
		mass * 9.8 * frictionCoeff,
		mass * 9.8 * frictionCoeff
	};

	friction.horizontal = min(fabs(friction.horizontal), fabs(force.horizontal));
	friction.vertical = min(fabs(friction.vertical), fabs(force.vertical));

	if (force.horizontal < 0)
		friction.horizontal = -friction.horizontal;
	if (force.vertical < 0)
		friction.vertical = -friction.vertical;

	return friction;
}

bool Movable::InRangeOf(ColisionBox& box) {
	double left = box.GetPoint().x - box.GetSize().w / 2;
	double right = box.GetPoint().x + box.GetSize().w / 2;
	double top = box.GetPoint().y + box.GetSize().h / 2;
	double bottom = box.GetPoint().y - box.GetSize().h / 2;

	return (point.x - size.w / 2 < right && point.x + size.w / 2 > left)
		&& (point.y - size.h / 2 < top && point.y + size.h / 2 > bottom);
}

bool Movable::SameSigns(double x, double y) {
	return x > 0 && y > 0 || x < 0 && y < 0;
}

