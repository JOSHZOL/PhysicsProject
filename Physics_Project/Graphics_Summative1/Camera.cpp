#include "camera.h"

CCamera::CCamera()
{
	xPos = cameraPos.x;
	yPos = cameraPos.y;
	zPos = cameraPos.z;

	view = glm::lookAt(cameraPos, cameraFront, cameraUp);
	projection = glm::ortho(0.0f, float(Width), 0.0f, float(Height), 0.1f, 100.0f); 
}

CCamera::~CCamera()
{

}

glm::mat4 CCamera::getViewMatrix()
{
	view = glm::lookAt(cameraPos, glm::vec3(cameraPos.x + cameraFront.x, cameraPos.y + cameraFront.y, 1.0f), cameraUp);
	return (view);
}

glm::mat4 CCamera::getProjectionMatrix()
{
	cameraPos = glm::vec3(xPos, yPos, zPos);

	return (projection);
}

glm::vec3 CCamera::getCameraPos()
{
	return (cameraPos);
}

void CCamera::setCameraPos(glm::vec3 _NewPos)
{
	xPos = _NewPos.x;
	yPos = _NewPos.y;
	zPos = _NewPos.z;
}

void CCamera::setCameraFront(glm::vec3 _newFront)
{
	cameraFront = _newFront;
}

void CCamera::setXpos(float _x)
{
	xPos = _x;
}

void CCamera::setYpos(float _y)
{
	yPos = _y;
}

void CCamera::setZpos(float _z)
{
	zPos = _z;
}

float CCamera::getXpos()
{
	return (xPos);
}

float CCamera::getYpos()
{
	return (yPos);
}

float CCamera::getZpos()
{
	return (zPos);
}

void CCamera::MouseInput(int _x, int _y)
{
	
}

void CCamera::keyboard(unsigned char key)
{
	keyState[key] = BUTTON_DOWN;
}

void CCamera::keyboard_up(unsigned char key)
{
	keyState[key] = BUTTON_UP;
}

void CCamera::mouse(int button, int button_state)
{
	/*#define state ((button_state == GLUT_DOWN) ? BUTTON_DOWN : BUTTON_UP) 
	
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
	}*/
}

void CCamera::update()
{
	if (keyState[(unsigned char)'w'] == BUTTON_DOWN)
	{
		yPos += 0.5 * cameraSpeed;
	}

	if (keyState[(unsigned char)'s'] == BUTTON_DOWN)
	{
		yPos -= 0.5 * cameraSpeed;
	}

	if (keyState[(unsigned char)'d'] == BUTTON_DOWN)
	{
		xPos += 0.5 * cameraSpeed;
	}

	if (keyState[(unsigned char)'a'] == BUTTON_DOWN)
	{
		xPos -= 0.5 * cameraSpeed;
	}
}