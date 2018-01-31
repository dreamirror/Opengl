#version 330 core
layout (location = 0) in vec3 aPos;

layout(std140) uniform Matrices{
	mat4 projection;
	mat4 view;
};

out VS_OUT{
	vec3 TexCoords;
} vs_out;
void main()
{	
	vs_out.TexCoords = aPos;
	vec4 pos = projection * view* vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}