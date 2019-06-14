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

vec3 ads (vec4 Light, float LightI,
          float Ka, float Kd, float Ks, float Shininess,
	  vec3 Position )

{
    vec3 n = normalize(normal);
    vec3 s = light.xyz;
    if (light.w == 1.0) { // positional light
       s = normalize(s - position);
    } else { // directional light
       s = normalize(s);
    }
    vec3 v = normalize(vec3(-position));
    vec3 r = reflect( s, n );

    return lightI * (
           color * Kd * max( dot(s, n), 0.0 ) +
          color* Ks * pow( max( dot(r,v), 0.0 ), Shininess )) + color * Ka;
}

void main()
{
    vec3 eyePosition = (modelviewMatrix * vec4(position, 1.0)).xyz; // eye-space position
    //vec3 eyeNormal   = normalize(normalMatrix * normal);      // eye-space normal 
    gl_Position = (projectionMatrix*modelviewMatrix)* vec4(position, 1.0); // transformed position

    fragmentColor = ads(light, lightI,surfKa, surfKd, surfKs, surfShininess,eyePos);

	
}
