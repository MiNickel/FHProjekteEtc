//PHONG.FRAG
#version 330 core

in vec3	vertPos;
in vec3	vertNormal;
//in vec3 vertColor;

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

out vec3 fragColor;

void main()
{
	vec3 lightVector;
	if(lightDirection.w==0)// Richtungslichtquelle
		lightVector = normalize(lightDirection.xyz);
	else// Punktlichtquelle
		lightVector = normalize(lightDirection.xyz-vertPos);

	vec3 r = reflect(lightVector, vertNormal);
	vec3 v = normalize(vertPos-eyePos);

	vec3 diffuse = light.ld * material.kd * max(0.0, dot(vertNormal, lightVector));
	vec3 specular = light.ls * material.ks * pow(max(0.0, dot(r, v)), material.shinyness);
	vec3 ambient = light.la * material.ka;

	fragColor = diffuse + specular + ambient;
}