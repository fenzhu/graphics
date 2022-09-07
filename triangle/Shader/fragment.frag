#version 330 core

out vec4 FragColor;

//in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

void main()
{
   //FragColor =  texture(ourTexture2, TexCoord * 2);
   FragColor =  mix(texture(ourTexture, TexCoord), texture(ourTexture2, TexCoord), 0.2);
}