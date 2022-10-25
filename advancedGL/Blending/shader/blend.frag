#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D texture1;

void main () 
{
    vec4 color = texture(texture1, TexCoords);
    // if (color.a < 0.1) {
    //     discard;
    // }
    FragColor = color;
}   