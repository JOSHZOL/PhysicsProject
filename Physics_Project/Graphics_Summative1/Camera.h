#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"


class CCamera
{
public:
	CCamera();
	~CCamera();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	glm::vec3 getCameraPos();
	void setCameraPos(glm::vec3 _NewPos);

	void setXpos(float _x);
	void setYpos(float _y);
	void setZpos(float _z);
	void setCameraFront(glm::vec3);

	float getXpos();
	float getYpos();
	float getZpos();

	void keyboard(unsigned char key);
	void keyboard_up(unsigned char key);
	void mouse(int button, int button_state);

	void MouseInput(int _x, int _y);

	void update();

private:
	float xPos;
	float yPos;
	float zPos;

	float Width = 1600.0f;
	float Height = 900.0f;

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 view;
	glm::mat4 projection;

	GLfloat cameraSpeed = 5.0f;

	GLfloat centerX = 1280 / 2;
	GLfloat centerY = 720 / 2;

	GLfloat yaw = -90.0f;
	GLfloat pitch = 0.0f;
	GLfloat lastX = centerX;
	GLfloat lastY = centerY;
	bool firstMouse = true;

	#define BUTTON_UP 0 
	#define BUTTON_DOWN 1

	unsigned char keyState[255];
};