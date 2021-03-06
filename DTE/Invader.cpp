#include "Invader.h"
#include "Texture.h"

void Invader::Draw() {
	CalculateVelocity();

	draw->WithTexture(boxes);
}

void Invader::Play() {
	static bool rigth = true;
	if (point.x > 95)
		rigth = false;
	if (point.x < 5)
		rigth = true;

	Force2D force;
	if (rigth)
		force = { 5, 0 };
	else
		force = { -5, 0 };
	if (delay++ > delayMax) {
		Shoot({ 1, 2 });
		delay = 0;
	}
	(*this).ApplyForce(force);
}

void Invader::Resize() {
	Texture texture = draw->GetTexture(Invader::type);
	Size blockSize = { size.w / texture.Size(), size.h / texture.Size() };
}

const char* Invader::type = typeid(Invader).name();