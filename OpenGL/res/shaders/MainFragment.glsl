#version 330 core

layout(location = 0) out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D sampler;

void main()
{
	FragColor = texture(sampler, TexCoord);
}