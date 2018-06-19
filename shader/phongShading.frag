#version 330 core

in vec3	vPosition;
in vec3	vNormal;
in vec3 vColor;

uniform vec4 lightDirection;
uniform vec3 material;
uniform float shine;
uniform vec3 ambientLight;
uniform vec3 camera;

out vec3 fragColor;

void main()
{
	vec3 light;
	if(lightDirection.w==0)// Richtungslichtquelle
		light = normalize(lightDirection.xyz);
	else// Punktlichtquelle
		light = normalize(lightDirection.xyz-vPosition);

	vec3 reflectionVec = reflect(light, vNormal); //ReflexionsVektor
	vec3 viewVec = normalize(vPosition-camera);	//Vektor zwischen Kamera und aktuellem Punkt

	vec3 diffuse = vec3(0.0,0.0,1.0) * material.x * max(0.0, dot(vNormal, light));	//Diffus-Reflexion
	vec3 specular = vec3(0.0,0.0,1.0) * material.y * pow(max(0.0, dot(reflectionVec, viewVec)), shine);	//Spiegelnde Reflexion
	vec3 ambient = vec3(0.0,0.0,1.0) * material.z * ambientLight;	//Umgebungslicht

	fragColor = diffuse + specular + ambient;

	
}

