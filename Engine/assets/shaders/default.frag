#version 330 core

in vec4 vTexCoord;

uniform vec4 color;
uniform sampler2D textureSampler;

out vec4 outColor;

void main(){
  outColor = texture(textureSampler, vec2(vTexCoord.x, vTexCoord.y)) * color;
}