#pragma once

#include "Camera.h"
#include "ObjectSprite.h"

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

	b2Body* CreateRec(float width, float height, bool isDynamic, float posX, float posY);

private:
	CCamera* cam;
	b2World* world;

	CObjectSprite* ground;
	b2Body* groundCollider;

	std::vector<CObjectSprite*> sprites;
	std::vector<b2Body*> boxColliders;

	const float meterToPixel = 20.0f;
	const float pixelToMeter = 1.0f / (float)meterToPixel;
};