#version 330 core

out vec4 FragColor;


in VS_OUT{
	vec3 TexCoords;  //这个代表的采样的方向而不是采样的直接的位置。因为采样 的射线的出发点是正方体的远点所以片段的位置就是采样的方向
}vs_in;
uniform  samplerCube  skybox;
void main()
{    

    FragColor = texture(skybox, vs_in.TexCoords);

}