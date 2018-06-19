#version 330 core

in vec3 position;
in vec3 color;
in vec3 normal;

uniform mat4 mvp;  // model-view-projection
uniform mat3 nm;   // normal matrix
uniform vec4 lightDirection;
uniform float shine;
uniform mat4 modelMatrix;
uniform vec3 camera;
uniform vec3 material;
uniform vec3 ambientLight;



smooth out vec3 fragmentColor;


void main()
{
	
	vec3 pos = vec3(modelMatrix * vec4(position, 1));
	vec3  n     = normalize(nm * color);
	vec3 light;

	if(lightDirection.w==0)// Richtungslichtquelle
		light = lightDirection.xyz;
	else// Punktlichtquelle
		light = lightDirection.xyz-pos;
	
	vec3 reflectionVec = reflect(light, n); //ReflexionsVektor
	vec3 viewVector = normalize(pos-camera);	//Vektor zwischen Kamera und aktuellem Punkt

	vec3 diffuse = vec3(1.0, 0.0, 0.0) * material.x * max(0.0, dot(n, light)); //Diffus-Reflexion
	vec3 specular = vec3(1.0, 0.0, 0.0) * material.y * pow(max(0.0, dot(reflectionVec, viewVector)), shine);	//Spiegelnde Reflexion
	vec3 ambient = vec3(1.0, 0.0, 0.0) * material.z * ambientLight;	//Umgebungslicht
	

	//fragmentColor = diffuse + specular + ambient;
	//gl_Position   = mvp * vec4(position,  1.0);

	float fDiff = max(0.0, dot(n, light)) ;
	fragmentColor = fDiff * vec3(1.0,0.0,0.0);
	gl_Position   = mvp * vec4(position,  1.0);
	
}