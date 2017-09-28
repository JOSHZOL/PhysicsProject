#include "Object.h"

CObject::CObject()
{
}

// Simple rectangle
CObject::CObject(std::string _texture, b2World* _world, float _posX, float _posY, float _width, float _height,
	bool _isDynamic)
{
	sprite = new CObjectSprite(_texture);
	body = CreateRec(_world, _posX * pixelToMeter, _posY * pixelToMeter, _isDynamic, 
		(_width - 2.4f) * pixelToMeter, (_height - 2.4f) * pixelToMeter, 0.2f, 0.0f);

	sprite->scaleMat(glm::vec3(_width, _height, 1.0f));
	sprite->move(glm::vec3(_posX, _posY, 1.0f));

	init();
}

// Rectangle
CObject::CObject(std::string _texture, b2World* _world, float _posX, float _posY, float _width, float _height, 
	bool _isDynamic, float _friction = 0.2f, float _bounce = 0.0f, float _angularDamping = 0.0f)
{
	sprite = new CObjectSprite(_texture);
	body = CreateRec(_world, _posX * pixelToMeter, _posY * pixelToMeter, _isDynamic, 
		(_width - 2.4f) * pixelToMeter, (_height - 2.4f) * pixelToMeter, _friction, _bounce);

	body->SetAngularDamping(_angularDamping);

	sprite->scaleMat(glm::vec3(_width, _height, 1.0f));
	sprite->move(glm::vec3(_posX, _posY, 1.0f));

	init();
}

// Circle
CObject::CObject(std::string _texture, b2World* _world, float _posX, float _posY, float _radius, 
	bool _isDynamic, float _friction = 0.2f, float _bounce = 0.0f, float _rotationDamping = 0.0f)
{
	sprite = new CObjectSprite(_texture);
	body = CreateCircle(_world, _posX * pixelToMeter, _posY * pixelToMeter, _isDynamic, 
		(_radius - 0.5f) * pixelToMeter, _friction, _bounce);

	body->SetAngularDamping(_rotationDamping);

	sprite->scaleMat(glm::vec3(_radius * 2, _radius * 2, 1.0f));
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

b2Body* CObject::CreateRec(b2World* _world, float posX, float posY, bool isDynamic, float width, float height, float friction, float bounce)
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
	fixtureDef.friction = friction;
	fixtureDef.restitution = bounce;

	TempBody->CreateFixture(&fixtureDef);

	return TempBody;
}

b2Body* CObject::CreateCircle(b2World* _world, float posX, float posY, bool isDynamic, float radius, float friction, float bounce)
{
	b2BodyDef bodyDef;

	if (isDynamic)
	{
		bodyDef.type = b2_dynamicBody;
	}

	bodyDef.position.Set(posX, posY);

	b2Body* TempBody = _world->CreateBody(&bodyDef);

	b2CircleShape shape;
	shape.m_radius = radius;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = friction;
	fixtureDef.restitution = bounce;

	TempBody->CreateFixture(&fixtureDef);

	return TempBody;
}