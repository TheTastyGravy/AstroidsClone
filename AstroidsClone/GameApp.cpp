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
	UpdateCamera((Camera*)&cam);

	BeginDrawing();
	ClearBackground(BLACK);

	BeginTextureMode(target);
	ClearBackground(BLACK);

	// Draw objects
	for (auto object : objects)
	{ object->draw(); }

	EndTextureMode();


	BeginShaderMode(shader);

	DrawTextureRec(target.texture, { 0, 0, (float)target.texture.width, -(float)target.texture.height }, { 0, 0 }, WHITE);

	EndShaderMode();


	EndDrawing();
}


void GameApp::startup(Vector2 screenSize)
{
	// Setup window
	InitWindow(SCREEN_WIDTH, SCREEN_HIGHT, "Astroids");
	SetTargetFPS(60);

	//load shader
	shader = LoadShader(0, "scanlines.fs");
	target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HIGHT);

	cam = { { 0, 0 }, { 0, 0 }, 0, 0 };


	// Create player
	new Player({ SCREEN_WIDTH * 0.5f, SCREEN_HIGHT * 0.5f }, 0, { (float)SCREEN_WIDTH, (float)SCREEN_HIGHT }, 200, 250, 200, 0.3f);

	// Create some random astroids
	for (int i = 0; i < 3; i++)
	{
		new Astroid({ (float)(rand() % SCREEN_WIDTH), (float)(rand() % SCREEN_HIGHT) }, rand() % 360, { (float)SCREEN_WIDTH, (float)SCREEN_HIGHT }, 16, 100);
	}
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