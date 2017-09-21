#include "ObjectSprite.h"

CObjectSprite::CObjectSprite()
{
}

CObjectSprite::CObjectSprite(std::string _texture)
{
	textureFile = _texture;
}

CObjectSprite::~CObjectSprite()
{
}

void CObjectSprite::init()
{
	ShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram("Assets/shaders/VertShader.vs", "Assets/shaders/FragShader.fs");

	GLfloat vertices[] = {
		-0.5f, 0.5f, 0.0f,  0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,   1.0f, 0.0f,
		0.5f, -0.5f, 0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f

	};

	GLuint indices[] = {
		0, 1, 2, // First Triangle
		0, 2, 3 // Second Triangle
	};

	glGenBuffers(1, &vao);
	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		5 * sizeof(GLfloat),
		(GLvoid*)0);

	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		5 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	int width, height;

	unsigned char* image = SOIL_load_image(textureFile.c_str(), // file name
		&width, //width of the image
		&height, // height of the image
		0, // number of channels
		SOIL_LOAD_RGBA);

	glTexImage2D(
		GL_TEXTURE_2D, // type of texture
		0, //mipmaplevel
		GL_RGBA,// format of RGB values to be stored
		width, // width of resulting texture
		height, //height of resulting texture
		0, //value must be 0
		GL_RGBA,// format of the pixel data
		GL_UNSIGNED_BYTE,// type of data passed in
		image);//

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CObjectSprite::move(glm::vec3 _move)
{
	glm::vec3 newPosition = _move;
	translation = glm::translate(glm::mat4(), newPosition);
}

void CObjectSprite::rotate(GLfloat _rotate)
{
	rotation = glm::rotate(glm::mat4(), _rotate, glm::vec3(0.0f, 0.0f, 1.0f));
}

void CObjectSprite::scaleMat(glm::vec3 _scale)
{
	scaleAmount = _scale;
	scale = glm::scale(glm::mat4(), scaleAmount);
}

glm::vec3 CObjectSprite::getScale()
{
	return (scaleAmount);
}

void CObjectSprite::render(glm::mat4 _view, glm::mat4 _proj, glm::vec3 _camPos, float _deltatime)
{
	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		5 * sizeof(GLfloat),
		(GLvoid*)0);

	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		5 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));

	glUseProgram(program);

	static float currentTime = 0;
	currentTime += _deltatime;

	model = translation * rotation;

	GLint modelLoc = glGetUniformLocation(program, "model");
	GLint viewLoc = glGetUniformLocation(program, "view");
	GLint projLoc = glGetUniformLocation(program, "projection");
	GLint scaleLoc = glGetUniformLocation(program, "scale");
	GLint cameraLoc = glGetUniformLocation(program, "cameraPos");
	GLint currentTimeLoc = glGetUniformLocation(program, "currentTime");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(_proj));
	glUniformMatrix4fv(scaleLoc, 1, GL_FALSE, glm::value_ptr(scale));
	glUniform3fv(cameraLoc, 1, glm::value_ptr(_camPos));
	glUniform1f(currentTimeLoc, currentTime);

	//glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, texture);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//glBindVertexArray(0);
}