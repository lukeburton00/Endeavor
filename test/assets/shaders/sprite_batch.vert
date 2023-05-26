#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec4 color;

uniform mat4 view_projection;

out vec4 vTexCoord;
out vec4 vColor;

void main()
{
    gl_Position = view_projection * vec4(position, 0.0f, 1.0f);

    vTexCoord = vec4(texCoord, 1.0f, 1.0f);
    
    vColor = color;
}
