#version 330 core

out vec4 FragColor;
in vec3 TexCoords;  //�������Ĳ����ķ�������ǲ�����ֱ�ӵ�λ�á���Ϊ���� �����ߵĳ��������������Զ������Ƭ�ε�λ�þ��ǲ����ķ���
uniform  samplerCube  skybox;
void main()
{    

    FragColor = texture(skybox, TexCoords);

}