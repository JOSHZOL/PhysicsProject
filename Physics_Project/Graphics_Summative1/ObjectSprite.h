#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\soil.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "ShaderLoader.h"
#include <string>

class CObjectSprite
{
public:
	CObjectSprite();
	CObjectSprite(std::string _texture);
	~CObjectSprite();

	void init();

	void move(glm::vec3 _move);
	void rotate(GLfloat _rotate);
	void scaleMat(glm::vec3 _scale);

	glm::vec3 getScale();

	void render(glm::mat4 _view, glm::mat4 _proj, glm::vec3 _camPos, float _deltatime);

private:
	int width, height;

	std::string textureFile;

	glm::vec3 scaleAmount;

	glm::mat4 model;
	glm::mat4 scale;
	glm::mat4 translation;
	glm::mat4 rotation;

	GLuint program;

	GLuint vao;
	GLuint vbo;
	GLuint ebo;

	GLuint texture;
};