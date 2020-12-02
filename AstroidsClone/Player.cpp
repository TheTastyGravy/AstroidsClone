#include "Player.h"
#include "Projectile.h"
#include <string>
#include "GameApp.h"


Player::Player(Vector2 position, float rotation, Vector2 screenSize, float acceleration, float rotationSpeed, float maxSpeed, float friction) :
	GameObject(position, rotation),
	isGameOver(false),
	velocity(Vector2()),
	acceleration(acceleration),
	rotSpeed(rotationSpeed),
	maxSpeed(maxSpeed),
	friction(friction),
	isInvulnerable(false),
	timer(0),
	screenSize(screenSize),
	score(0),
	lives(1)
{
	addTag(Tag::Player);
}

Player::~Player()
{
}



void Player::draw()
{
	// Display player as a triangle
	Vector2 v1 = { 6, 0 };
	v1 = Vector2Rotate(v1, rotation);
	v1 = Vector2Add(v1, position);

	Vector2 v2 = { -7, -4.5f };
	v2 = Vector2Rotate(v2, rotation);
	v2 = Vector2Add(v2, position);

	Vector2 v3 = { -7, +4.5f };
	v3 = Vector2Rotate(v3, rotation);
	v3 = Vector2Add(v3, position);

	// Blink while invulnerable
	if (isInvulnerable)
	{
		int val = floor(timer);
		DrawTriangleLines(v1, v2, v3, (timer - val < 0.5f) ? WHITE : DARKGRAY);
	}
	else
	{
		DrawTriangleLines(v1, v2, v3, WHITE);
	}


	// Display score in top left corner
	DrawText(("score: " + std::to_string(score)).c_str(), 10, 10, 25, WHITE);
	// Display lives in top right corner
	DrawText(("lives: " + std::to_string(lives)).c_str(), screenSize.x - 100, 10, 25, WHITE);
}

void Player::update(float deltaTime)
{
	if (isInvulnerable)
	{
		timer += deltaTime;
		if (timer > 3.0f)
		{
			isInvulnerable = false;
		}
	}


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


	// Update the agents position
	position = newPos;


	// Shoot on space
	if (IsKeyPressed(KEY_SPACE) && !isInvulnerable)
	{
		new Projectile(position, rotation, 400);
	}
}


void Player::damage()
{
	//cant be hit
	if (isInvulnerable)
	{ return; }

	//score -= 1000;
	position = Vector2Scale(screenSize, 0.5f);
	velocity = Vector2Zero();
	rotation = 0;

	isInvulnerable = true;
	timer = 0;
	lives--;


	if (lives == 0)
	{
		isGameOver = true;
	}
}