//PHONG.VERT
#version 330 core

in vec3 position;
in vec3 normal;

//uniform vec3 color;
uniform mat4 mvp;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

out vec3 vertPos;
out vec3 vertNormal;
//out vec3 vertColor;

void main()
{
	vertPos = vec3(modelMatrix * vec4(position, 1));
	vertNormal = normalize(normalMatrix * normal);
	//vertColor = color;

	gl_Position   = mvp * vec4(position,  1.0);
}