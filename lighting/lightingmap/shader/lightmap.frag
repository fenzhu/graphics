#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;

struct Light {
    vec3 Position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

in vec3 Normal;
in vec3 WorldPos;
in vec2 TexCoords;

uniform vec3 viewPos;

out vec4 FragColor;

//when implement phong lighting in vertex shader, it's called Gouraud Shading
//pros: color calculating is done in vertex only
//cons: fragment color is got by interpolating, unrealistic
void main() 
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.Position - WorldPos);
    float diff = max(dot(norm, lightDir), 0.0);
    
    vec3 viewDir = normalize(viewPos - WorldPos);
    float spec = pow(max(dot(normalize(viewDir + lightDir), norm), 0.0), material.shininess);

    vec3 ambient  = light.ambient * texture(material.diffuse, TexCoords).rgb;   
    vec3 diffuse = light.diffuse * texture(material.diffuse, TexCoords).rgb * diff;
    vec3 specular = light.specular * texture(material.specular, TexCoords).rgb * spec;

    vec3 result =  diffuse + ambient + specular;
    // FragColor = texture(material.specular, TexCoords);
    FragColor = vec4(result, 1.0);
}