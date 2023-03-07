#version 330 core

in vec4 vTexCoord;
in vec4 vColor;

uniform sampler2D textureSampler;

out vec4 outColor;

void main()
{
  outColor = texture(textureSampler, vec2(vTexCoord.x, vTexCoord.y)) * vColor;
}