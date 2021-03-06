#include "Game.h"

CGame::CGame()
{	
	b2Vec2 gravity = b2Vec2(0.0, -9.8);
	world = new b2World(gravity);

	listener = new CCollisionListener();

	world->SetContactListener(listener);

	cam = new CCamera();

	catapult = new CObjectSprite("Assets/textures/box.png");
	catapult->scaleMat(glm::vec3(30.0f, 300.0f, 1.0f));
	catapult->move(glm::vec3(300, 150, 1));

	slider = new CObjectSprite("Assets/textures/box.png");
	slider->scaleMat(glm::vec3(430.0f, 10.0f, 1.0f));
	slider->move(glm::vec3(690, 600, 1));
}

CGame::~CGame()
{
	delete world;
	delete cam;

	boxes.clear();

	delete ground;
	delete bird;
}

void CGame::keyboard(unsigned char key)
{
	keyState[key] = BUTTON_DOWN;
}

void CGame::keyboard_up(unsigned char key)
{
	keyState[key] = BUTTON_UP;
}

void CGame::MouseInput(int button, int button_state)
{
	#define state ((button_state == GLUT_DOWN) ? BUTTON_DOWN : BUTTON_UP) 
	
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		mouseState[MOUSE_LEFT] = state;
		break;
	case GLUT_MIDDLE_BUTTON:
		mouseState[MOUSE_MIDDLE] = state;
		break;
	case GLUT_RIGHT_BUTTON: mouseState[MOUSE_RIGHT] = state;
		break;
	}
}

void CGame::MousePosition(int _x, int _y)
{
	mouseX = _x;
	mouseY = -_y + 900;
}

void CGame::controls()
{
	glm::vec2 origin = glm::vec2(300, 300);
	glm::vec2 release;
	glm::vec2 direction;

	if (mouseState[MOUSE_LEFT] == BUTTON_DOWN)
	{
		mousePressed = true;

		glm::vec2 position = glm::vec2(mouseX, mouseY);
		
		if (glm::distance(origin, glm::vec2(mouseX, mouseY)) < 200)
		{
			bird->getBody()->SetTransform(b2Vec2(mouseX * pixelToMeter, mouseY * pixelToMeter), bird->getBody()->GetAngle());
		}
		else
		{
			direction = position - origin;
			direction = glm::normalize(direction);

			direction *= 200;
			
			bird->getBody()->SetTransform(b2Vec2((origin.x + direction.x) * pixelToMeter, (origin.y + direction.y) * pixelToMeter), bird->getBody()->GetAngle());
		}
	}

	if (mouseState[MOUSE_LEFT] == BUTTON_UP && mousePressed)
	{
		mousePressed = false;

		// example of adding force
		release = glm::vec2(bird->getBody()->GetPosition().x * meterToPixel, bird->getBody()->GetPosition().y * meterToPixel);
		direction = origin - release;

		direction = glm::normalize(direction);

		bird->getBody()->SetActive(true);

		float force = 80 * glm::distance(origin, release) * pixelToMeter;

		bird->getBody()->ApplyForce(b2Vec2(direction.x * force, direction.y * force), bird->getBody()->GetWorldCenter(), true);
	}
	
	if (keyState[(unsigned char)'w'] == BUTTON_DOWN)
	{
		cam->setYpos(cam->getYpos() + 2.5f);
	}

	if (keyState[(unsigned char)'s'] == BUTTON_DOWN)
	{
		cam->setYpos(cam->getYpos() - 2.5f);
	}

	if (keyState[(unsigned char)'d'] == BUTTON_DOWN)
	{
		cam->setXpos(cam->getXpos() + 2.5f);
	}

	if (keyState[(unsigned char)'a'] == BUTTON_DOWN)
	{
		cam->setXpos(cam->getXpos() - 2.5f);
	}
}

void CGame::update(float _deltatime)
{
	static float delta = 0;
	delta += _deltatime;

	if (delta > (1.0f / 70.0))
	{
		delta = 0;
		world->Step(1.0f / 70.0f, 8, 3);
	}

	controls();
	
	for (int i = 0; i < boxes.size(); i++)
	{
		boxes[i]->update(_deltatime);

		if (boxes[i]->getBody()->GetPosition().y < 0.0f)
		{
			world->DestroyBody(boxes[i]->getBody());
			boxes[i] = boxes.back();
			boxes.pop_back();
		}
	}

	bird->update(_deltatime);
	
	for (int i = 0; i < boxes.size(); i++)
	{
		if (boxes[i]->getBody() == listener->getDestroy())
		{
			boxes[i] = boxes.back();
			boxes.pop_back();
			world->DestroyBody(listener->getDestroy());
		}
	}
}

void CGame::init()
{
	float boxSize = 64;
	float groundWidth = 1600;
	float groundHeight = 64;

	float birdRadius = 32;

	boxes.push_back(new CObject("Assets/textures/circle.png", world, 800.0f, 400.0f, 32, false, 0.6f, 0.5f, 0.7f));
	boxes.push_back(new CObject("Assets/textures/circle.png", world, 800.0f + boxSize, 400.0f, 32, true, 0.6f, 0.3f, 0.7f));
	boxes.push_back(new CObject("Assets/textures/circle.png", world, 800.0f + (boxSize * 2), 400.0f, 32, true, 0.6f, 0.3f, 0.7f));
	boxes.push_back(new CObject("Assets/textures/circle.png", world, 800.0f + (boxSize * 3), 400.0f, 32, true, 0.6f, 0.3f, 0.7f));
	boxes.push_back(new CObject("Assets/textures/circle.png", world, 800.0f + (boxSize * 4), 400.0f, 32, true, 0.6f, 0.3f, 0.7f));
	boxes.push_back(new CObject("Assets/textures/circle.png", world, 800.0f + (boxSize * 5), 400.0f, 32, true, 0.6f, 0.3f, 0.7f));
	boxes.push_back(new CObject("Assets/textures/circle.png", world, 800.0f + (boxSize * 6), 400.0f, 32, false, 0.6f, 0.3f, 0.7f));

	createRevoluteJoint(boxes[0]->getBody(), boxes[1]->getBody(), 32 * pixelToMeter);
	createRevoluteJoint(boxes[1]->getBody(), boxes[2]->getBody(), 32 * pixelToMeter);
	createRevoluteJoint(boxes[2]->getBody(), boxes[3]->getBody(), 32 * pixelToMeter);
	createRevoluteJoint(boxes[3]->getBody(), boxes[4]->getBody(), 32 * pixelToMeter);
	createRevoluteJoint(boxes[4]->getBody(), boxes[5]->getBody(), 32 * pixelToMeter);
	createRevoluteJoint(boxes[6]->getBody(), boxes[5]->getBody(), -32 * pixelToMeter);

	boxes.push_back(new CObject("Assets/textures/circle.png", world, 500.0f, 600.0f, 32, false, 0.6f, 0.5f, 0.7f));
	boxes.push_back(new CObject("Assets/textures/circle.png", world, 500.0f + (boxSize * 1), 600.0f, 32, true, 0.6f, 0.3f, 0.7f));
	boxes.push_back(new CObject("Assets/textures/circle.png", world, 500.0f + (boxSize * 6), 600.0f, 32, false, 0.6f, 0.5f, 0.7f));

	createPrismaticJoint(boxes[7]->getBody(), boxes[8]->getBody());

	boxes.push_back(new CObject("Assets/textures/box.png", world, 1300.0f - (boxSize / 2), 800.0f, boxSize, boxSize, true, 0.6f, 0.3f, 0.7f));
	boxes.push_back(new CObject("Assets/textures/box.png", world, 1300.0f + (boxSize / 2), 800.0f, boxSize, boxSize, true, 0.6f, 0.3f, 0.7f));

	createWeldJoint(boxes[10]->getBody(), boxes[11]->getBody(), 32 * pixelToMeter);

	boxes[8]->getBody()->ApplyForce(b2Vec2(100, 0), boxes[8]->getBody()->GetWorldCenter(), true);

	for (int i = 0; i < 10; i++)
	{
		boxes.push_back(new CObject("Assets/textures/box.png", world, 1300.0f, (65 * (i + 1.6f)), boxSize, boxSize, true, 0.6f, 0.3f, 0.7f));
		boxes.back()->getBody()->SetUserData(&typeBox);
	}

	ground = new CObject("Assets/textures/ground.png", world, 800, 32, groundWidth, groundHeight, false);

	// use player class for this instead
	bird = new CObject("Assets/textures/circle.png", world, 300, 300, birdRadius, true, 0.6f, 0.5f, 0.7f);

	bird->getBody()->SetActive(false);
	bird->getBody()->SetUserData(&typeBird);

	catapult->init();
	slider->init();
}

void CGame::render(float _deltatime)
{
	bird->getSprite()->render(cam->getViewMatrix(), cam->getProjectionMatrix(), cam->getCameraPos(), _deltatime);
	
	catapult->render(cam->getViewMatrix(), cam->getProjectionMatrix(), cam->getCameraPos(), _deltatime);
	slider->render(cam->getViewMatrix(), cam->getProjectionMatrix(), cam->getCameraPos(), _deltatime);

	for (int i = 0; i < boxes.size(); i++)
	{
		boxes[i]->getSprite()->render(cam->getViewMatrix(), cam->getProjectionMatrix(), cam->getCameraPos(), _deltatime);
	}

	ground->getSprite()->render(cam->getViewMatrix(), cam->getProjectionMatrix(), cam->getCameraPos(), _deltatime);
}

void CGame::createRevoluteJoint(b2Body* _body1, b2Body* _body2, float _width)
{
	b2RevoluteJointDef joint;

	b2Vec2 anchor(_body1->GetPosition().x + _width, _body1->GetPosition().y);
	joint.Initialize(_body1, _body2, anchor);
	world->CreateJoint(&joint);
}

void CGame::createPrismaticJoint(b2Body * _body1, b2Body * _body2)
{
	b2PrismaticJointDef joint;

	b2Vec2 anchor(_body1->GetPosition().x , _body1->GetPosition().y);
	joint.Initialize(_body1, _body2, anchor, b2Vec2(1, 0));
	joint.collideConnected = true;
	world->CreateJoint(&joint);
}

void CGame::createWeldJoint(b2Body * _body1, b2Body * _body2, float _width)
{
	b2WeldJointDef joint;

	b2Vec2 anchor(_body1->GetPosition().x + _width, _body1->GetPosition().y);
	joint.Initialize(_body1, _body2, anchor);
	world->CreateJoint(&joint);
}
