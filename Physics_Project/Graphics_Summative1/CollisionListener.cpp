#include "CollisionListener.h"

CCollisionListener::CCollisionListener()
{
}

CCollisionListener::~CCollisionListener()
{
}

void CCollisionListener::BeginContact(b2Contact * _contact)
{
	b2Body* one = _contact->GetFixtureA()->GetBody();
	b2Body* two = _contact->GetFixtureB()->GetBody();

	int a = 0;
	int b = 0;

	if (one->GetUserData() != nullptr)
	{
		a = *((int*)one->GetUserData());
	}
	
	if (two->GetUserData() != nullptr)
	{
		b = *((int*)two->GetUserData());
	}

	if ((a == 1 && b == 2) || (a == 2 && b == 1))
	{
		if (a == 2)
		{
			destroy = one;
		}

		if (b == 2)
		{
			destroy = two;
		}
	}
}

void CCollisionListener::EndContact(b2Contact * _contact)
{
}

b2Body * CCollisionListener::getDestroy()
{
	return destroy;
}
