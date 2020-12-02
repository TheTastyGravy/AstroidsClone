#include "Projectile.h"


Projectile::Projectile(Vector2 position, float rotation, float speed) :
	GameObject(position, rotation),
	timer(0)
{
	// Velocity is speed in the forward direction
	velocity = { 0, speed };
	velocity = Vector2Rotate(velocity, rotation - 90);


	addTag(Tag::Projectile);
}

Projectile::~Projectile()
{
}


void Projectile::update(float deltaTime)
{
	// Move projectile
	Vector2 scaledVel = Vector2Scale(velocity, deltaTime);
	position = Vector2Add(position, scaledVel);


	// If the projectile has been alive for over 5 seconds, destroy it
	timer += deltaTime;
	if (timer > 5)
	{
		delete(this);
	}
}

void Projectile::draw()
{
	Vector2 offset = { 7, 0 };
	offset = Vector2Rotate(offset, rotation);

	// Start and end point are offset
	DrawLineEx(Vector2Add(position, offset), Vector2Subtract(position, offset), 1, RED);
}