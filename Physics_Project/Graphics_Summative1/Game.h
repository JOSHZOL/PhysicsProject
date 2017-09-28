#pragma once

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "Camera.h"
#include "Object.h"
#include "CollisionListener.h"

#include "Box2D\Box2D.h"

#include <vector>

class CGame
{
public:
	CGame();
	~CGame();

	void keyboard(unsigned char key);
	void keyboard_up(unsigned char key);

	void MouseInput(int button, int button_state);
	void MousePosition(int _x, int _y);

	void controls();

	void init();
	void render(float _deltatime);

	void createRevoluteJoint(b2Body * _body1, b2Body * _body2, float _width);
	void createPrismaticJoint(b2Body * _body1, b2Body * _body2);
	void createWeldJoint(b2Body * _body1, b2Body * _body2, float _width);

	void update(float _deltatime);

private:
	CCamera* cam;
	b2World* world;

	CObjectSprite* catapult;
	CObjectSprite* slider;

	CObject* bird;
	CObject* ground;

	std::vector<CObject*> boxes;

	CCollisionListener* listener;

	int typeBox = 2;
	int typeBird = 1;

	int mouseX;
	int mouseY;

	bool mousePressed;

	#define BUTTON_UP 0 
	#define BUTTON_DOWN 1

	#define MOUSE_LEFT 0 
	#define MOUSE_MIDDLE 1
	#define MOUSE_RIGHT 2

	unsigned char keyState[255];
	unsigned char mouseState[3];

	float meterToPixel = 160.0f;
	float pixelToMeter = 1.0f / (float)meterToPixel;
};