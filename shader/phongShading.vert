#version 330 core

in vec3 position;
in vec3 color;
in vec3 normal;

uniform mat4 mvp;  // model-view-projection
uniform mat3 nm;   // normal matrix
uniform mat4 modelMatrix; 


out vec3 vPosition;
out vec3 vNormal;
out vec3 vColor;

void main()
{
	vPosition = vec3(modelMatrix * vec4(position, 1));
	vNormal = normalize(nm * color);
	vColor = color;
	
	gl_Position   = mvp * vec4(position,  1.0);
}