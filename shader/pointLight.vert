#version 330 core

in vec3 position;
in vec3 color;
in vec3 normal;

uniform mat4 mvp;  // model-view-projection
uniform mat3 nm;   // normal matrix
uniform vec3 lightPosition;


//flat          out vec3 fragmentColor;
//noperspective out vec3 fragmentColor;
smooth        out vec3 fragmentColor;

void main()
{
	vec3 lightDirection = lightPosition - position;
	vec3  n     = normalize(nm * color);
	float fDiff = max(dot(color, lightDirection), 0.0);
    //fragmentColor =color * fDiff * vec3(1.0, 0.0, 0.0);
	fragmentColor = fDiff * color;
	gl_Position   = mvp * vec4(position,  1.0);
	
}