#pragma once

#include "Camera.h"
#include "Object.h"

#include "Box2D\Box2D.h"

#include <vector>

class CGame
{
public:
	CGame();
	~CGame();

	void keyboard(unsigned char key);
	void keyboard_up(unsigned char key);

	void MouseInput(int button, int button_state, int _x, int _y);

	void controls();

	void init();
	void render(float _deltatime);

	void update(float _deltatime);

private:
	CCamera* cam;
	b2World* world;

	CObject* bird;
	CObject* ground;

	std::vector<CObject*> boxes;

	int mouseX;
	int mouseY;

	#define BUTTON_UP 0 
	#define BUTTON_DOWN 1

	#define MOUSE_LEFT 0 
	#define MOUSE_MIDDLE 1
	#define MOUSE_RIGHT 2

	unsigned char keyState[255];
	unsigned char mouseState[3];
};