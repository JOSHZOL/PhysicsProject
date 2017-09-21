#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec3 outColor; 
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec4 WorldPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 scale;

uniform float currentTime;

void main()
{
	WorldPos = model * vec4(position, 1.0); 
	gl_Position = projection * view * model * scale * vec4(vec3(position.x, position.y * sin((currentTime * 2) + (position.x * 20)) / 20, position.z) , 1.0);

	FragPos = vec3(model * vec4(position, 1.0f)); 
	Normal = mat3(transpose(inverse(model))) * normal;

	outColor = vec3(1.0f, 1.0f, 1.0f);
	TexCoord = vec2(texCoord.x + (int(currentTime * 30) * 0.015625f), texCoord.y);
}