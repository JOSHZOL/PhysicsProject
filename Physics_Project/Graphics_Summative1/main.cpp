#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\soil.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include "Dependencies\FMOD\fmod.hpp"

#include <iostream>
#include <ctime>

#include "SceneManager.h"

CSceneManager* sceneManager = new CSceneManager();

float currentTime = 0;
float previousTime = 0;
float deltaTime = 0;

void init()
{
	srand(unsigned int(time(0)));
	
	sceneManager->init();
}

void update()
{
	currentTime = float(glutGet(GLUT_ELAPSED_TIME));
	currentTime = currentTime / 1000;

	deltaTime = currentTime - previousTime;
	previousTime = currentTime;

	if (deltaTime > 0.15f)
	{
		deltaTime = 0.15f;
	}
	
	sceneManager->update(deltaTime);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.50f, 0.70f, 1.0f, 1.0f);

	sceneManager->render(deltaTime);

	glutSwapBuffers();
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	sceneManager->keyboard(key);
}

void keyboard_up(unsigned char key, int x, int y)
{
	sceneManager->keyboard_up(key);
}

void mouse(int button, int button_state, int x, int y)
{
	sceneManager->MouseInput(button, button_state, x, y);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(150, 50);
	glutInitWindowSize(1600, 900);
	glutCreateWindow("AngryBirds_Summative");

	glewInit();
	init();

	glutMouseFunc(mouse);

	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);

	glutDisplayFunc(render);
	glutIdleFunc(update);

	glutMainLoop();

	return (0);
}