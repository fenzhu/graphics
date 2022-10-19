#version 330 core

in vec3 Normal;
in vec3 WorldPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 FragColor;

//when implement phong lighting in vertex shader, it's called Gouraud Shading
//pros: color calculating is done in vertex only
//cons: fragment color is got by interpolating, unrealistic
void main() 
{
    float ambientStrength = 0.2;
    vec3 ambient  = ambientStrength * lightColor;
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - WorldPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - WorldPos);
    float spec = pow(max(dot(normalize(viewDir + lightDir), norm), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result =  (diffuse + ambient + specular) * objectColor;
    FragColor = vec4(result, 0.0);
}