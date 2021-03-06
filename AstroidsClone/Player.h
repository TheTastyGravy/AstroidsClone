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
	void addScore(int score) { this->score += score; }

	//checked by gameapp
	bool isGameOver;
	int score;

private:
	Vector2 velocity;

	float acceleration;
	float rotSpeed;

	float maxSpeed;
	float friction;

	bool isInvulnerable;
	float timer;


	Vector2 screenSize;

	int lives;
};