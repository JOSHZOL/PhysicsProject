#pragma once

#include <iostream>
#include "Box2D\Box2D.h"

class CCollisionListener : public b2ContactListener
{
public:
	CCollisionListener();
	~CCollisionListener();

	void BeginContact(b2Contact* _contact);
	void EndContact(b2Contact* _contact);

	b2Body* getDestroy();

private:
	b2Body* destroy;
};