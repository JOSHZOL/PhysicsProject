#include "Game.h"

CGame::CGame()
{	
	b2Vec2 gravity = b2Vec2(0.0, -1.0);
	world = new b2World(gravity);

	cam = new CCamera();

	for (int i = 0; i < 10; i++)
	{
		sprites.push_back(new CObjectSprite("Assets/textures/box.png"));
	}

	ground = new CObjectSprite("Assets/textures/ground.png");
}

CGame::~CGame()
{
	delete world;
	delete cam;
}

void CGame::keyboard(unsigned char key)
{
	cam->keyboard(key);
}

void CGame::keyboard_up(unsigned char key)
{
	cam->keyboard_up(key);
}

void CGame::MouseInput(int _x, int _y)
{
	cam->MouseInput(_x, _y);
}

void CGame::update(float _deltatime)
{
	world->Step(1.0f/60.0f, 8, 3);
	cam->update();
	
	for (int i = 0; i < sprites.size(); i++)
	{
		b2Vec2 boxPosition = boxColliders[i]->GetPosition();
		boxPosition.x *= meterToPixel;
		boxPosition.y *= meterToPixel;

		sprites[i]->move(glm::vec3(boxPosition.x, boxPosition.y, 1.0f));
		sprites[i]->rotate(boxColliders[i]->GetAngle());
	}
}

b2Body* CGame::CreateRec(float posX, float posY, bool isDynamic, float width, float height)
{
	b2BodyDef bodyDef;

	if (isDynamic)
	{
		bodyDef.type = b2_dynamicBody;
	}
	
	bodyDef.position.Set(posX, posY);

	b2Body* dynamicBody = world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(width * 0.5, height * 0.5);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;

	dynamicBody->CreateFixture(&fixtureDef);
	
	return dynamicBody;
}

void CGame::init()
{
	float boxSize = 64;
	float groundWidth = 1600;
	float groundHeight = 64;
	
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i]->init();
		sprites[i]->scaleMat(glm::vec3(boxSize, boxSize, 1.0f));
		
		boxColliders.push_back(CreateRec(1300 * pixelToMeter, (65 * (i + 1.6f) ) * pixelToMeter, true, (boxSize - 1) * pixelToMeter, (boxSize - 1) * pixelToMeter));
	}
	
	groundCollider = CreateRec(800 * pixelToMeter, 32 * pixelToMeter, false, groundWidth * pixelToMeter, groundHeight * pixelToMeter);

	ground->init();
	ground->scaleMat(glm::vec3(groundWidth, groundHeight, 1.0f));

	b2Vec2 boxPosition = groundCollider->GetPosition();
	boxPosition.x *= meterToPixel;
	boxPosition.y *= meterToPixel;

	ground->move(glm::vec3(boxPosition.x, boxPosition.y, 1.0f));
}

void CGame::render(float _deltatime)
{
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i]->render(cam->getViewMatrix(), cam->getProjectionMatrix(), cam->getCameraPos(), _deltatime);
	}

	ground->render(cam->getViewMatrix(), cam->getProjectionMatrix(), cam->getCameraPos(), _deltatime);
}

