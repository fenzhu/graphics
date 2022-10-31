#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT
{
    vec2 texCoords;
}
gs_in[];

out vec2 TexCoords;

uniform float time;

// void build_house(vec4 position)
// {
//     fColor = gs_in[0].color;
//     gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0); // 1:bottom-left
//     EmitVertex();
//     gl_Position = position + vec4(0.2, -0.2, 0.0, 0.0); // 2:bottom-right
//     EmitVertex();
//     gl_Position = position + vec4(-0.2, 0.2, 0.0, 0.0); // 3:top-left
//     EmitVertex();
//     gl_Position = position + vec4(0.2, 0.2, 0.0, 0.0); // 4:top-right
//     EmitVertex();
//     gl_Position = position + vec4(0.0, 0.4, 0.0, 0.0); // 5:top
//     fColor = vec3(1.0, 1.0, 1.0);
//     EmitVertex();
//     EndPrimitive();
// }

vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

vec4 explode(vec4 position, vec3 normal)
{
    float magnitude = 2.0;
    vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude;
    return position + vec4(direction, 0.0);
}


void main()
{
    // gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.0, 0.0, 0.0);
    // EmitVertex();

    // gl_Position = gl_in[0].gl_Position + vec4( 0.1, 0.0, 0.0, 0.0);
    // EmitVertex();

    // EndPrimitive();

    // gl_Position = gl_in[0].gl_Position;
    // EmitVertex();
    // EndPrimitive();

    // build_house(gl_in[0].gl_Position);

    vec3 normal = GetNormal();

    gl_Position = explode(gl_in[0].gl_Position, normal);
    TexCoords = gs_in[0].texCoords;
    EmitVertex();

    gl_Position = explode(gl_in[1].gl_Position, normal);
    TexCoords = gs_in[1].texCoords;
    EmitVertex();

    gl_Position = explode(gl_in[2].gl_Position, normal);
    TexCoords = gs_in[2].texCoords;
    EmitVertex();

    EndPrimitive();
}