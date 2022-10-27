#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main() {
    TexCoords = aPos;
    //perspective division performed after vertex shader has run, set z = 1.0
    gl_Position = (projection * view * vec4(aPos, 1.0)).xyww;
}