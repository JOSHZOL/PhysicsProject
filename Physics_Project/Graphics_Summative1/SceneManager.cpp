#include "SceneManager.h"
#include "Game.h"

CSceneManager::CSceneManager()
{
	Game = new CGame();
}

CSceneManager::~CSceneManager()
{
	
}

void CSceneManager::keyboard(unsigned char key)
{
	Game->keyboard(key);

	keyState[key] = BUTTON_DOWN;
}

void CSceneManager::keyboard_up(unsigned char key)
{
	Game->keyboard_up(key);

	keyState[key] = BUTTON_UP;
}

void CSceneManager::MouseInput(int _x, int _y)
{
	Game->MouseInput(_x, _y);
}

void CSceneManager::update(float _deltatime)
{
	Game->update(_deltatime);

	if (keyState[(unsigned char)'r'] == BUTTON_DOWN)
	{
		delete Game;
		Game = new CGame();

		Game->init();
	}
}

void CSceneManager::init()
{
	Game->init();
}

void CSceneManager::render(float _deltatime)
{
	Game->render(_deltatime);
}
