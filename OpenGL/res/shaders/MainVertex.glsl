#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 aProj;

void main()
{
	gl_Position = aProj * vec4(aPos, 1.0f, 1.0f);
	TexCoord = aTexCoord;
}