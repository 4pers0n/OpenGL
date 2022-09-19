#version 330 core

layout(location = 0) out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D sampler0;
uniform sampler2D sampler1;

void main()
{
	FragColor = mix(texture(sampler0, TexCoord), texture(sampler1, TexCoord), 0.2f);
}