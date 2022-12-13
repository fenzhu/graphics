#version 420 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;

    vec3 normal;
    vec3 aTangent;
    vec3 aBitangent;
} fs_in;

uniform sampler2D floorTexture;
uniform sampler2D normalMap;
//layout(binding = 1) 

/*
TBN:
1 in frag shader, transform tangent-space normal to world-space normal.
2 in vert shader, transform light,model to tangent-space.avoid matrix in frag shader.
*/
void main()
{           
    vec3 normal = texture(normalMap, fs_in.TexCoords).rgb;
    //range [-1,1], in tangent space
    normal = normalize(normal * 2.0 - 1.0);  
    
    // normal = fs_in.normal;
    // vec3 normal = fs_in.normal;

    vec3 color = texture(floorTexture, fs_in.TexCoords).rgb;
    // ambient
    vec3 ambient = 0.1 * color;

    // diffuse
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;

    // specular
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = vec3(0.2) * spec;

    FragColor = vec4(ambient + diffuse + specular, 1.0);
    // FragColor = vec4(fs_in.aBitangent, 1.0);
}