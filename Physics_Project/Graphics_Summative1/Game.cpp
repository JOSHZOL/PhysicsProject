#include "Game.h"

CGame::CGame()
{	
	b2Vec2 gravity = b2Vec2(0.0, -1.0);
	world = new b2World(gravity);

	cam = new CCamera();
}

CGame::~CGame()
{
	delete world;
	delete cam;
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
	world->Step(1.0f/60.0f, 8, 3);
	cam->update();
	
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->update(_deltatime);
	}
}

void CGame::init()
{
	float boxSize = 64;
	float groundWidth = 1600;
	float groundHeight = 64;

	for (int i = 0; i < 10; i++)
	{
		objects.push_back(new CObject("Assets/textures/box.png", world, 1300, (65 * (i + 1.6f)), true, boxSize - 1, boxSize- 1));
		
		objects.back()->getSprite()->init();
	}

	ground = new CObject("Assets/textures/ground.png", world, 800, 32, false, groundWidth, groundHeight);
	ground->getSprite()->init();
}

void CGame::render(float _deltatime)
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->getSprite()->render(cam->getViewMatrix(), cam->getProjectionMatrix(), cam->getCameraPos(), _deltatime);
	}

	ground->getSprite()->render(cam->getViewMatrix(), cam->getProjectionMatrix(), cam->getCameraPos(), _deltatime);
}

