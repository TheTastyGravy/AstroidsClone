#pragma once
#include "GameObject.h"


class Astroid : public GameObject
{
public:
	Astroid(Vector2 position, float rotation, Vector2 screenSize, float size, float speed);
	~Astroid();

	void update(float deltaTime) override;
	void draw() override;


private:
	Vector2 screenSize;

	Vector2 velocity;
	float size;

	GameObject* player;
};