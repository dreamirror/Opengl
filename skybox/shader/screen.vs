#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextCoords;

out vec2 TexCoords;
out vec3 Normal;

void main()
{	
	TexCoords = aTextCoords;
    gl_Position =  vec4(aPos.x, aPos.y, 0.0, 1.0);
}