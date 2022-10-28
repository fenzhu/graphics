#version 420 core
layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aNormal;
layout (location = 1) in vec2 aTexCoords;

layout (std140, binding = 0) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

//shared layout
//packed layout
// layout (std140) uniform ExampleBlock
// {
//                      // base alignment  // aligned offset
//     float value;     // 4               // 0 
//     vec3 vector;     // 16              // 16  (offset must be multiple of 16 so 4->16)
//     mat4 matrix;     // 16              // 32  (column 0)
//                      // 16              // 48  (column 1)
//                      // 16              // 64  (column 2)
//                      // 16              // 80  (column 3)
//     float values[3]; // 16              // 96  (values[0])
//                      // 16              // 112 (values[1])
//                      // 16              // 128 (values[2])
//     bool boolean;    // 4               // 144
//     int integer;     // 4               // 148
// }; 

uniform mat4 model;
// uniform mat4 view;
// uniform mat4 projection;

out VS_OUT
{
    vec2 TexCoords;
} vs_out;

void main()
{
    //gl_VertexID
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vs_out.TexCoords = aTexCoords;

    gl_PointSize = gl_Position.z;
}


