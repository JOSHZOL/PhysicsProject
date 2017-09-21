#pragma once

#include "Game.h"

class CSceneManager
{
public:
	CSceneManager();
	~CSceneManager();

	void keyboard(unsigned char key);
	void keyboard_up(unsigned char key);

	void MouseInput(int _x, int _y);

	void init();
	void render(float _deltatime);

	void update(float _deltatime);

private:
	CGame* Game;

	#define BUTTON_UP 0 
	#define BUTTON_DOWN 1

	unsigned char keyState[255];
};