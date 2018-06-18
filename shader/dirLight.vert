#version 330 core

in vec3 position;
in vec3 color;
in vec3 normal;

uniform mat4 mvp;  // model-view-projection
uniform mat3 nm;   // normal matrix
uniform vec3 lightDirection;


//flat          out vec3 fragmentColor;
//noperspective out vec3 fragmentColor;
smooth        out vec3 fragmentColor;

void main()
{
	vec3 lightDirection = vec3(0.0, -1.0, 0.0);
	vec3  n     = normalize(nm * normal);
	float fDiff = max(dot(n, lightDirection), 0.0);
    fragmentColor =color * fDiff;
	gl_Position   = mvp * vec4(position,  1.0);
	
}