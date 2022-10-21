#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D texture1;

float near = 0.1; 
float far  = 100.0; 


float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main () 
{
    // float depth = LinearizeDepth(gl_FragCoord.z) / far;

    // In the previous section we described that depth values in screen space are non-linear e.g. they have a very high precision for small z-values and a low precision for large z-values. 
    //The depth value of the fragment increases rapidly over distance so almost all the vertices have values close to 1.0. If we were to carefully move really close to an object you may eventually see the colors getting darker, their z-values becoming smaller:
    // FragColor = vec4(vec3(gl_FragCoord.z), 1.0);

    FragColor = texture(texture1, TexCoords);
}   