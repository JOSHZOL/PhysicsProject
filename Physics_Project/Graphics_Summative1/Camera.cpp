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