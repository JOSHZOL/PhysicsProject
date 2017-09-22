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

	void MouseInput(int _x, int _y);

	void init();
	void render(float _deltatime);

	void update(float _deltatime);

private:
	CCamera* cam;
	b2World* world;

	CObject* bird;
	CObject* ground;

	std::vector<CObject*> boxes;
};