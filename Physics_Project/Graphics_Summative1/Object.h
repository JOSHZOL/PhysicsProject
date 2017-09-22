#pragma once

#include "ObjectSprite.h"

#include "Box2D\Box2D.h"

class CObject
{
public:
	CObject();
	CObject(std::string _texture, b2World * _world, float _posX, float _posY, float _width, float _height, bool _isDynamic);

	CObject(std::string _texture, b2World * _world, float _posX, float _posY, float _width, float _height, bool _isDynamic, float _friction, float _bounce, float _angularDamping);
	CObject(std::string _texture, b2World * _world, float _posX, float _posY, float _radius, bool _isDynamic, float _friction, float _bounce, float _rotationDamping);
	~CObject();

	CObjectSprite* getSprite();
	b2Body* getBody();

	void init();
	void update(float _deltatime);

	b2Body* CreateRec(b2World* _world, float posX, float posY, bool isDynamic, float width, float height, float friction, float bounce);

	b2Body * CreateCircle(b2World * _world, float posX, float posY, bool isDynamic, float radius, float friction, float bounce);

private:
	CObjectSprite* sprite;
	b2Body* body;

	const float meterToPixel = 20.0f;
	const float pixelToMeter = 1.0f / (float)meterToPixel;
};