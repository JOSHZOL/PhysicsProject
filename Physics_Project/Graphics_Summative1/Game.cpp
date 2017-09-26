#include "Game.h"

CGame::CGame()
{	
	b2Vec2 gravity = b2Vec2(0.0, -9.0);
	world = new b2World(gravity);

	cam = new CCamera();
}

CGame::~CGame()
{
	delete world;
	delete cam;

	boxes.clear();

	delete ground;
	delete bird;
}

void CGame::keyboard(unsigned char key)
{
	cam->keyboard(key);
}

void CGame::keyboard_up(unsigned char key)
{
	cam->keyboard_up(key);
}

void CGame::MouseInput(int _x, int _y)
{
	cam->MouseInput(_x, _y);
}

void CGame::update(float _deltatime)
{
	static float delta = 0;
	delta += _deltatime;

	if (delta > (1.0f / 250.0))
	{
		delta = 0;
		world->Step(1.0f / 60.0f, 8, 3);
	}
	
	cam->update();
	
	for (int i = 0; i < boxes.size(); i++)
	{
		boxes[i]->update(_deltatime);

		if (boxes[i]->getBody()->GetPosition().y < 0.0f)
		{
			world->DestroyBody(boxes[i]->getBody());
			boxes[i] = boxes.back();
			boxes.pop_back();
		}
	}

	bird->update(_deltatime);
}

void CGame::init()
{
	float boxSize = 64;
	float groundWidth = 1600;
	float groundHeight = 64;

	float birdRadius = 32;

	for (int i = 0; i < 10; i++)
	{
		boxes.push_back(new CObject("Assets/textures/box.png", world, 1300.0f, (65 * (i + 1.6f)), boxSize, boxSize, true, 0.6f, 0.3f, 0.7f));
	}

	ground = new CObject("Assets/textures/ground.png", world, 800, 32, groundWidth, groundHeight, false);

	// use player class for this instead
	bird = new CObject("Assets/textures/circle.png", world, 100, 300, birdRadius, true, 0.6f, 0.5f, 0.7f);

	// example of adding force
	float force = 1000;
	bird->getBody()->ApplyForce(b2Vec2(15.0 * force, 6.5 * force), bird->getBody()->GetWorldCenter(), true);
}

void CGame::render(float _deltatime)
{
	bird->getSprite()->render(cam->getViewMatrix(), cam->getProjectionMatrix(), cam->getCameraPos(), _deltatime);
	
	for (int i = 0; i < boxes.size(); i++)
	{
		boxes[i]->getSprite()->render(cam->getViewMatrix(), cam->getProjectionMatrix(), cam->getCameraPos(), _deltatime);
	}

	ground->getSprite()->render(cam->getViewMatrix(), cam->getProjectionMatrix(), cam->getCameraPos(), _deltatime);
}

