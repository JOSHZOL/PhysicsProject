#pragma once

#include "ObjectSprite.h"

#include "Box2D\Box2D.h"

class CObject
{
public:
	CObject();
	CObject(std::string _texture, b2World * _world, float _posX, float _posY, bool _isDynamic, float _width, float _height);
	~CObject();

	CObjectSprite* getSprite();
	b2Body* getBody();

	void update(float _deltatime);

	b2Body* CreateRec(b2World* _world, float posX, float posY, bool isDynamic, float width, float height);

private:
	CObjectSprite* sprite;
	b2Body* body;

	const float meterToPixel = 20.0f;
	const float pixelToMeter = 1.0f / (float)meterToPixel;
};