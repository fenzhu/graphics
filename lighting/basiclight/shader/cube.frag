#version 330 core

in vec3 Normal;
in vec3 WorldPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

out vec4 FragColor;

void main() 
{
    float ambientStrength = 0.5;
    vec3 ambient  = ambientStrength * lightColor;
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - WorldPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result =  (diffuse + ambient) * objectColor;
    FragColor = vec4(result, 0.0);
}