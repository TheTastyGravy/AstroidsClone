#include "GameApp.h"
#include <memory>
#include <time.h>
#include "raylib.h"
#include "GameObjectPool.h"

#include "Player.h"
#include "Astroid.h"


void GameApp::run()
{
	// Fill vector with objects and thier behaviours(using shared_ptr)
	startup({ (const float)SCREEN_WIDTH, (const float)SCREEN_HIGHT });

	// Game loop
	while (!WindowShouldClose())
	{
		update(GameObjectPool::getPool());
		draw(GameObjectPool::getPool());
	}

	shutdown();
}


void GameApp::update(std::vector<GameObject*>& objects)
{
	float deltaTime = GetFrameTime();

	// Update objects
	for (int i = 0; i < objects.size(); i++)
	{ objects[i]->update(deltaTime); }
}

void GameApp::draw(std::vector<GameObject*>& objects)
{
	BeginDrawing();
	ClearBackground(BLACK);

	// Draw objects
	for (auto object : objects)
	{ object->draw(); }

	DrawFPS(5, 5);
	EndDrawing();
}


void GameApp::startup(Vector2 screenSize)
{
	// Setup window
	InitWindow(SCREEN_WIDTH, SCREEN_HIGHT, "AI Project");
	SetTargetFPS(60);

	// Create player
	new Player({ SCREEN_WIDTH * 0.5f, SCREEN_HIGHT * 0.5f }, 0, { (float)SCREEN_WIDTH, (float)SCREEN_HIGHT }, 200, 250, 200, 0.3f);

	new Astroid({ 100, 100 }, 0, { (float)SCREEN_WIDTH, (float)SCREEN_HIGHT }, 10, 100);
}

void GameApp::shutdown()
{
	std::vector<GameObject*> objects = GameObjectPool::getPool();

	// Delete all objects
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}

	CloseWindow();
}