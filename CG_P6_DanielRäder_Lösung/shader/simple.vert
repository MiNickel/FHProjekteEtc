//SIMPLE.VERT
#version 330 core

in vec3 position;

uniform mat4 mvp;
uniform vec3 color;

out vec3 fragmentColor;

void main()
{
	fragmentColor = color;
	gl_Position   = mvp * vec4(position,  1.0);
}