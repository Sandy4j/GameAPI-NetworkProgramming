#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;

void main()
{
    vec4 texColor = texture(tex0, texCoord);
    
    if (texColor.a < 0.1)
        discard;

   FragColor = vec4(color, 1.0f) * texColor;
   //FragColor = vec4(color, 1.0f) * texture(tex0, texCoord);
}