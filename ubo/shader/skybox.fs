#version 330 core

out vec4 FragColor;


in VS_OUT{
	vec3 TexCoords;  //�������Ĳ����ķ�������ǲ�����ֱ�ӵ�λ�á���Ϊ���� �����ߵĳ��������������Զ������Ƭ�ε�λ�þ��ǲ����ķ���
}vs_in;
uniform  samplerCube  skybox;
void main()
{    

    FragColor = texture(skybox, vs_in.TexCoords);

}