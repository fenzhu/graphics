#version 420 core

out vec4 FragColor;
//avaiable from OpenGL4.2
//Today most GPUs support a hardware feature called early depth testing. Early depth testing allows the depth test to run before the fragment shader runs.
layout(depth_less) out float gl_FragDepth;

in VS_OUT
{
    vec2 TexCoords;
} fs_in;

uniform sampler2D skybox;

void main()
{
    //built-in variable: gl_FragCoord, gl_FrontFacing
    float z = gl_FragCoord.z;
    if (gl_FragCoord.x <= 400) {
        FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
    else {
        FragColor = vec4(0.0, 1.0, 0.0, 1.0);
    }

    // if (gl_FrontFacing) {
    //     FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    // }
    // else {
    //     FragColor = vec4(0.0, 1.0, 0.0, 1.0);
    // }
    // gl_FragDepth = gl_FragCoord.z - 0.1;


    // FragColor = texture(skybox, fs_in.TexCoords);
}