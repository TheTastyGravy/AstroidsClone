#include "GameApp.h"
#include <memory>
#include <time.h>
#include <string>
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

	Player* player = static_cast<Player*>(GameObjectPool::searchForTag(Tag::Player)[0]);
	//if the player's bool is triggered
	if (player->isGameOver)
	{
		isPaused = true;
		scoreText = std::to_string(player->score);
	}


	if (isPaused)
	{
		//replay when space key is pressed
		if (IsKeyPressed(KEY_SPACE))
		{
			startGame();
		}
	}
	else
	{
		// Update objects
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->update(deltaTime);
		}
	}
}

void GameApp::draw(std::vector<GameObject*>& objects)
{
	BeginDrawing();
	ClearBackground(BLACK);

	//draw to texture so shader can be aplied to it
	BeginTextureMode(target);
	ClearBackground(BLACK);

	if (isPaused)
	{
		//show menu text
		DrawText("Game Over", SCREEN_WIDTH/2 - MeasureText("Game Over", 40) / 2, SCREEN_HIGHT/4 - 40/2, 40, WHITE);

		//show score
		DrawText("Score", SCREEN_WIDTH / 2 - MeasureText("Score", 30) / 2, SCREEN_HIGHT / 2 - 30 / 2 - 40, 30, WHITE);
		DrawText(scoreText.c_str(), SCREEN_WIDTH / 2 - MeasureText(scoreText.c_str(), 25) / 2, SCREEN_HIGHT / 2 - 25 / 2, 25, WHITE);

		//prompt to replay
		DrawText("Press space to replay", SCREEN_WIDTH / 2 - MeasureText("Press space to replay", 25) / 2, SCREEN_HIGHT/1.4f - 25 / 2, 25, WHITE);
	}
	else
	{
		// Draw objects
		for (auto object : objects)
		{
			object->draw();
		}
	}


	EndTextureMode();


	//shader
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


	startGame();
}

void GameApp::shutdown()
{
	UnloadShader(shader);

	std::vector<GameObject*> objects = GameObjectPool::getPool();

	// Delete all objects
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}

	CloseWindow();
}


void GameApp::startGame()
{
	isPaused = false;

	//clean object pool
	std::vector<GameObject*> objs = GameObjectPool::getPool();
	for (auto& thing : objs)
	{
		delete(thing);
	}


	// Create player
	new Player({ SCREEN_WIDTH * 0.5f, SCREEN_HIGHT * 0.5f }, 0, { (float)SCREEN_WIDTH, (float)SCREEN_HIGHT }, 200, 250, 200, 0.3f);

	// Create some random astroids
	for (int i = 0; i < 3; i++)
	{
		new Astroid({ (float)(rand() % SCREEN_WIDTH), (float)(rand() % SCREEN_HIGHT) }, rand() % 360, { (float)SCREEN_WIDTH, (float)SCREEN_HIGHT }, 16, 100);
	}
}