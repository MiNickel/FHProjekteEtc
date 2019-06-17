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

uniform mat4 mvp;


//flat          out vec3 fragmentColor;
noperspective out vec3 fragmentColor;
//smooth        out vec3 fragmentColor;



void main()
{
   

	vec3 pos = vec3(modelMatrix * vec4(position, 1));
	vec3 n = normalize(normal);
	vec3 s = light.xyz;
	if (light.w == 1.0) { // positional light
       s = normalize(s - pos);
    } else { // directional light
       s = normalize(s);
    }

	vec3 r = reflect( s, n );
	vec3 v = normalize(-pos-eyePos);

	vec3 diffuse = color * surfKd * max(0.0, dot(n, s));
	vec3 specular = color * surfKs * pow( max(0.0, dot(r,v) ), surfShininess );
	vec3 ambient = color * surfKa;

	fragmentColor = lightI * (diffuse + specular + ambient);
	gl_Position = mvp * vec4(position, 1.0);
}
