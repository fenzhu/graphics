#version 420 core

out vec4 FragColor;
//avaiable from OpenGL4.2
//Today most GPUs support a hardware feature called early depth testing. Early depth testing allows the depth test to run before the fragment shader runs.
layout(depth_less) out float gl_FragDepth;

in VS_OUT
{
    vec2 TexCoords;
} fs_in;

void main()
{
     if (gl_FragCoord.x <= 400) {
        FragColor = vec4(0.0, 0.0, 1.0, 1.0);
    }
    else {
        FragColor = vec4(1.0, 1.0, 0.0, 1.0);
    }
}