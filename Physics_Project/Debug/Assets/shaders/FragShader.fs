#version 430 core

in vec3 outColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 WorldPos; 

out vec4 color;

uniform sampler2D Texture;

uniform vec3 cameraPos;
uniform vec3 lightPos;

void main() 
{
	vec3 objectColor = outColor;
	vec3 lightColor = vec3(0.8f, 0.8f, 0.8f);

	float ambientStrength = 0.5;
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(Normal); 
	vec3 lightDir = normalize(lightPos - FragPos); 
	float diff = max(dot(norm, lightDir), 0.0); 
	vec3 diffuse = diff * lightColor;

	float specularStrength = 0.01;
	vec3 viewDir = normalize(cameraPos - FragPos); 
	vec3 reflectionDir = reflect(-lightDir, norm); 
	float spec = pow(max(dot(viewDir, reflectionDir),0.0), 32); 
	vec3 specular = spec * lightColor * specularStrength;

	vec3 totalColor = (ambient + diffuse + specular) * objectColor;
	
	float d = distance(WorldPos.xyz, cameraPos); 
	float lerp = (d - 10.0f) / 30.f;
	lerp = clamp(lerp, 0.0, 1.0);
	
	vec4 vFogColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);

	color = vec4(totalColor, 1.0f) * texture(Texture, TexCoord);
	color = mix(color, vFogColor, lerp);
}