#include "Object.h"

CObject::CObject()
{
}

CObject::CObject(std::string _texture, b2World* _world, float _posX, float _posY, bool _isDynamic, float _width, float _height)
{
	sprite = new CObjectSprite(_texture);
	body = CreateRec(_world, _posX * pixelToMeter, _posY * pixelToMeter, _isDynamic, (_width - 0.5f) * pixelToMeter, (_height - 0.5f) * pixelToMeter);
	
	sprite->scaleMat(glm::vec3(_width, _height, 1.0f));
	sprite->move(glm::vec3(_posX, _posY, 1.0f));

	init();
}

CObject::~CObject()
{
}

CObjectSprite* CObject::getSprite()
{
	return sprite;
}

b2Body* CObject::getBody()
{
	return body;
}

void CObject::init()
{
	sprite->init();
}

void CObject::update(float _deltatime)
{
	b2Vec2 boxPosition = body->GetPosition();
	boxPosition.x *= meterToPixel;
	boxPosition.y *= meterToPixel;

	sprite->move(glm::vec3(boxPosition.x, boxPosition.y, 1.0f));
	sprite->rotate(body->GetAngle());
}

b2Body* CObject::CreateRec(b2World* _world, float posX, float posY, bool isDynamic, float width, float height)
{
	b2BodyDef bodyDef;

	if (isDynamic)
	{
		bodyDef.type = b2_dynamicBody;
	}

	bodyDef.position.Set(posX, posY);

	b2Body* TempBody = _world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(width * 0.5, height * 0.5);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;

	TempBody->CreateFixture(&fixtureDef);

	return TempBody;
}