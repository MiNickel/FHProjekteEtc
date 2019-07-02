//FLAT.VERT
#version 330 core

in vec3 position;
in vec3 normal;

uniform mat4 mvp;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

struct Light {
	vec3 ld;
	vec3 ls;
	vec3 la;
};
struct Material {
	float kd;
	float ks;
	float ka;
	float shinyness;
};

uniform vec3 eyePos;
uniform vec4 lightDirection;
uniform Light light;
uniform Material material;

flat out vec3 fragmentColor;

void main()
{
	vec3 pos = vec3(modelMatrix * vec4(position, 1));
	vec3 nNormal = normalize(normalMatrix * normal);
	vec3 lightVector;

	if(lightDirection.w==0)// Richtungslichtquelle
		lightVector = normalize(lightDirection.xyz);
	else// Punktlichtquelle
		lightVector = normalize(lightDirection.xyz-pos);

	vec3 r = reflect(lightVector, nNormal);
	vec3 v = normalize(pos-eyePos);

	vec3 diffuse = light.ld * material.kd * max(0.0, dot(nNormal, lightVector));
	vec3 specular = light.ls * material.ks * pow(max(0.0, dot(r, v)), material.shinyness);
	vec3 ambient = light.la * material.ka;

	fragmentColor = diffuse + specular + ambient;
	gl_Position   = mvp * vec4(position,  1.0);
}