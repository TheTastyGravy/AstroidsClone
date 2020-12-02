#include "Astroid.h"
#include "Player.h"
#include "GameObjectPool.h"


Astroid::Astroid(Vector2 position, float rotation,Vector2 screenSize, float size, float speed) :
	GameObject(position, rotation),
	screenSize(screenSize),
	size(size)
{
	// Velocity is speed in the forward direction
	velocity = { 0, speed };
	velocity = Vector2Rotate(velocity, rotation - 90);

	//the player should always exist, so get on instansiation
	player = GameObjectPool::searchForTag(Tag::Player)[0];


	addTag(Tag::Astroid);
}

Astroid::~Astroid()
{
}


void Astroid::update(float deltaTime)
{
	// Find new position
	Vector2 scaledVel = Vector2Scale(velocity, deltaTime);
	Vector2 newPos = Vector2Add(position, scaledVel);

	// Wrap around edges of screen
	if (newPos.x < 0)
	{
		newPos.x += screenSize.x;
	}
	if (newPos.x > screenSize.x)
	{
		newPos.x -= screenSize.x;
	}
	if (newPos.y < 0)
	{
		newPos.y += screenSize.y;
	}
	if (newPos.y > screenSize.y)
	{
		newPos.y -= screenSize.y;
	}

	// Update position
	position = newPos;



	//get player rect
	Vector2 pos = player->getPos();
	Rectangle playerRect = { pos.x - 6, pos.y - 6, 12, 12 };
	
	if (CheckCollisionCircleRec(position, size, playerRect))
	{
		//damage player
		static_cast<Player*>(player)->damage();
	}


	//check for collision with projectiles
	std::vector<GameObject*> projs = GameObjectPool::searchForTag(Tag::Projectile);
	for (int i = 0; i < projs.size(); i++)
	{
		if (CheckCollisionPointCircle(projs[i]->getPos(), position, size))
		{
			//create new small astroids if not too small
			if (size > 2)
			{
				new Astroid(position, std::rand() % 360, screenSize, size - 2, Vector2Length(velocity) + 20);
				new Astroid(position, std::rand() % 360, screenSize, size - 2, Vector2Length(velocity) + 20);
			}
			
			delete(projs[i]);
			delete(this);
		}
	}
}

void Astroid::draw()
{
	DrawCircleLines(position.x, position.y, size, WHITE);
}