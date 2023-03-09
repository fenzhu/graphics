#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D hdrBuffer;
uniform bool hdr;
uniform float exposure;

void main()
{
    const float gamma = 2.2;
    vec3 hdrColor = texture(hdrBuffer, TexCoords).rgb;

    if (hdr)
    {
        /*
            allow color values to temporarily exceed 1.0 and transform them back to the original 
            range of 0.0 and 1.0 as a final step, but without losing detail.
           
            can be really bright, or really dark.

            converting HDR values to LDR values is called tone mapping.

            If we have a scene that features a day and night cycle it makes sense to use a lower exposure 
            at daylight and a higher exposure at night time, similar to how the human eye adapts
        */      
        vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
        result = pow(result, vec3(1.0 / gamma));

        FragColor = vec4(result, 1.0);
    }
    else
    {
        vec3 result = pow(hdrColor, vec3(1.0 / gamma));
        
        FragColor = vec4(result, 1.0);
    }
}