#include "Player.h"
#include "Projectile.h"


Player::Player(Vector2 position, float rotation, Vector2 screenSize, float acceleration, float rotationSpeed, float maxSpeed, float friction) :
	GameObject(position, rotation),
	velocity(Vector2()),
	acceleration(acceleration),
	rotSpeed(rotationSpeed),
	maxSpeed(maxSpeed),
	friction(friction),
	screenSize(screenSize)
{
	addTag(Tag::Player);
}

Player::~Player()
{
}



void Player::draw()
{
	// Find the corners for an isosceles triangle pointing in the direction of movement
	//if (velocity.x != 0.0f || velocity.y != 0.0f)
		//rotation = (float)atan2(velocity.y, velocity.x) * (180 / PI);

	Vector2 v1 = { 6, 0 };
	v1 = Vector2Rotate(v1, rotation);
	v1 = Vector2Add(v1, position);

	Vector2 v2 = { -7, -4.5f };
	v2 = Vector2Rotate(v2, rotation);
	v2 = Vector2Add(v2, position);

	Vector2 v3 = { -7, +4.5f };
	v3 = Vector2Rotate(v3, rotation);
	v3 = Vector2Add(v3, position);

	DrawTriangle(v1, v2, v3, RED);
}

void Player::update(float deltaTime)
{
	Vector2 force{ 0, 0 };
	// Get movement input
	if (IsKeyDown(KEY_W))
		force.y = -1;
	

	// Normalise so diagnals arnt faster, and multiply by the speed
	if (force.x != 0.0f && force.y != 0.0f)
	{ force = Vector2Normalize(force); }
	force = Vector2Scale(force, acceleration);

	// Scale force by delta time and rotate it to be in the direction the player is facing
	force = Vector2Scale(force, deltaTime);
	force = Vector2Rotate(force, rotation + 90);

	// Apply force and clamp to max speed
	velocity = Vector2Add(velocity, force);
	if (Vector2Length(velocity) > maxSpeed)
	{
		velocity = Vector2Normalize(velocity);
		velocity = Vector2Scale(velocity, maxSpeed);
	}

	// Apply friction when not getting input
	if ((force.x == 0.0f && force.y == 0.0f) &&
		(velocity.x != 0.0f || velocity.y != 0.0f))
	{
		velocity = Vector2Scale(velocity, 1 - (friction * deltaTime));
	}

	// Find the new position and the change in rotation
	Vector2 newPos = Vector2Add(position, Vector2Scale(velocity, deltaTime));


	// Get rotation input
	float rot = 0;
	if (IsKeyDown(KEY_A))
		rot = -1;
	if (IsKeyDown(KEY_D))
		rot = 1;

	// Scale by rotation speed and delta time, and apply to rotation
	rot *= rotSpeed * deltaTime;
	rotation += rot;
	// Clamp rotation to 360
	if (rotation < 0)
	{ rotation += 360; }
	if (rotation > 360)
	{ rotation -= 360; }


	// Wrap around edges of screen
	if (newPos.x < 0)
	{ newPos.x += screenSize.x; }
	if (newPos.x > screenSize.x)
	{ newPos.x -= screenSize.x; }
	if (newPos.y < 0)
	{ newPos.y += screenSize.y; }
	if (newPos.y > screenSize.y)
	{ newPos.y -= screenSize.y; }


	//check colision with astroids


	// Update the agents position
	position = newPos;


	//shooting
	if (IsKeyPressed(KEY_SPACE))
	{
		Projectile* proj = new Projectile(position, rotation, 400);
	}
}