#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

uniform sampler2D floorTexture;
uniform vec3 viewPos;
uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];
uniform bool gamma;

vec3 blinnPhong(vec3 normal, vec3 fragPos, vec3 lightPos, vec3 LightColor)
{
    vec3 color = LightColor;

    // diffuse
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    
    // specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = color * spec; 
    
    float maxDistance = 1.5;
    float curDistance = length(lightPos  - fragPos);
    /*
        physical: 1/(distance*distance)
        without gamma-correction : should be pow(1/distance, 2.2)
        with gamma-correction: should be pow(1/(distance*distance), (1.0/2.2)*2.2)
        why: gammae-correction+quadratic, the scene looks too dark
    */
    float attenuation = 1.0 / (gamma ? curDistance * curDistance: curDistance);
    
    diffuse *= attenuation;
    specular *= attenuation;


    return diffuse + specular;
}


void main()
{           

    vec3 color = texture(floorTexture, fs_in.TexCoords).rgb;
    vec3 lighting = vec3(0.0);
    for (int i = 0; i < 4; i++)
    {
        lighting += blinnPhong(normalize(fs_in.Normal), fs_in.FragPos, lightPositions[i], lightColors[i]);
    }
    color *= lighting;
    /*
    color: 0 ~ 1
    after fragment shader, monitor apply pow(FragColor, 2.2) as the final pixel color
    why do they apply this operation? To make pixel looks better in user's eye.
    
    which makes colors darker. and the scene looks weired.
    ***if we work in linear space, we want to apply pow(FragColor, 1.0/2.2) to correction the monitor's operation, so-called gamma-correction.***

    usually the texture is produced in monitor space, which is not linear.To make the texture looks right, the artist already did the gamma-correction by their hands.***So we should revert artist's texture to linear space when we load the texture.***
    */
    if (gamma) 
    {
        color = pow(color, vec3(1.0/2.2));
    }
    FragColor = vec4(color, 1.0);
}