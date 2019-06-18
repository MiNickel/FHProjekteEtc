#version 330 core

in vec3 position;
in vec3 normal;
in vec3 color;  // could be used for diffuse reflectivity

uniform mat4 modelviewMatrix;   // model-view matrix
uniform mat4 projectionMatrix;  // projection matrix
uniform mat3 normalMatrix;      // normal matrix

uniform vec4  light;            // Light position or direction
uniform float lightI;           // Light intensity 
uniform float  surfKa;           // Ambient reflectivity
uniform float  surfKd;           // Diffuse reflectivity
uniform float  surfKs;           // Specular reflectivity
uniform float surfShininess;    // Specular shininess factor
uniform vec3 eyePos;
uniform mat4 modelMatrix;
uniform mat4 projection;
uniform mat4 view;
uniform vec3 lightColor;

uniform mat4 mvp;


flat          out vec4 fragmentColor;
//noperspective out vec3 fragmentColor;
//smooth        out vec3 fragmentColor;


void main()
{

	vec3 pos = vec3(modelMatrix * vec4(position, 1));
	gl_Position = projection * view * vec4(pos, 1.0);

	vec3 ambient = lightColor * surfKa;
	vec3 n = normalize(normal);
	vec3 s = light.xyz;
	if (light.w == 1.0) { // positional light
       s = normalize(s - pos);
    } else { // directional light
       s = normalize(s);
    }

	float diff = max(dot(n, s), 0.0);

	vec3 diffuse = diff * lightColor;
	
	vec3 result = (ambient + diffuse) * color;
    fragmentColor = vec4(result, 1.0);

	
}