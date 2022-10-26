#version 330 core 
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

const float offset = 1.0 / 300.0;  

void main() {
    // FragColor = texture(screenTexture, TexCoords);
    
    // float average = (FragColor.r + FragColor.g + FragColor.b) / 3.0;
    
    //weighted average, human more sensitive to green
    // float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
    //remove all colors except the white, gray, black colors
    // FragColor = vec4(average, average, average, 1.0);

    //inverse
    // FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);

    //kernel
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );

    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );

    //blur
    //vary the blur amount over time to create the effect of someone being drunk, or increase the blur whenever the main character is not wearing glasses. 
    float blurKernel[9] = float[](
    1.0 / 16, 2.0 / 16, 1.0 / 16,
    2.0 / 16, 4.0 / 16, 2.0 / 16,
    1.0 / 16, 2.0 / 16, 1.0 / 16  
    );

    float edgeDetectionKernel[9] = float[](
        1, 1, 1,
        1, -8, 1,
        1, 1, 1
    );

    vec3 sampleTex[9];
    for (int i = 0; i < 9; i++) {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    }

    vec3 color = vec3(0.0);
    for (int i = 0; i < 9; i++) {
        color += sampleTex[i] * blurKernel[i];
    }

    FragColor = vec4(color, 1.0);
}