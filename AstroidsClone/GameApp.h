#pragma once
#include <vector>
#include "GameObject.h"


class GameApp
{
public:
	GameApp() {}
	virtual ~GameApp() {}

	void run();

	void update(std::vector<GameObject*>& objects);
	void draw(std::vector<GameObject*>& objects);

	void startup(Vector2 screenSize);
	void shutdown();

protected:
	const int SCREEN_WIDTH = 1000;
	const int SCREEN_HIGHT = 600;

	Shader shader;
	RenderTexture2D target;
	Camera2D cam;
};