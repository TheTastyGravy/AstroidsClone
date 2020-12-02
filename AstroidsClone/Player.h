#pragma once
#include "GameObject.h"


class Player : public GameObject
{
public:
	Player(Vector2 position, float rotation, Vector2 screenSize, float acceleration, float rotationSpeed, float maxSpeed, float friction);
	~Player();

	void update(float deltaTime) override;
	void draw() override;

	void damage();

private:
	Vector2 velocity;

	float acceleration;
	float rotSpeed;

	float maxSpeed;
	float friction;


	Vector2 screenSize;
};