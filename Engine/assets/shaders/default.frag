#version 330 core

in vec4 textureCoord;

uniform vec4 color;
uniform sampler2D textureSampler;

out vec4 outColor;

void main(){
  outColor = texture(textureSampler, vec2(textureCoord.x, textureCoord.y)) * color;
}