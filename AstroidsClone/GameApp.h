#pragma once
#include <vector>
#include <string>
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

	void startGame();

protected:
	const int SCREEN_WIDTH = 1000;
	const int SCREEN_HIGHT = 600;

	bool isPaused = false;
	std::string scoreText;

	Shader shader;
	RenderTexture2D target;
};